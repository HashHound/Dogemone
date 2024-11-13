// Copyright (c) 2012-2016, The CryptoNote developers, The Bytecoin developers
// Copyright (c) 2018, The TurtleCoin developers
// Copyright (c) 2016-2021, The Karbo developers
//
// This file is part of Dogemone.
//
// Dogemone is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Dogemone is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with Dogemone.  If not, see <http://www.gnu.org/licenses/>.

#include <cstdlib>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <string>
#include <string.h>
#include <sstream>
#include <vector>
#include <iterator>
#include <chrono>
#include <thread>
#include <future>

#include "Checkpoints.h"
#include "../CryptoNoteConfig.h"
#include "Common/StringTools.h"
#include "Common/DnsTools.h"

using namespace Logging;
#undef ERROR

namespace CryptoNote {
//---------------------------------------------------------------------------
Checkpoints::Checkpoints(Logging::ILogger &log, bool is_deep_reorg_allowed) : logger(log, "checkpoints"), m_is_deep_reorg_allowed(is_deep_reorg_allowed) {

}
//---------------------------------------------------------------------------
bool Checkpoints::add_checkpoint(uint32_t height, const std::string &hash_str) {
  Crypto::Hash h = NULL_HASH;

  if (!Common::podFromHex(hash_str, h)) {
    logger(WARNING) << "Wrong hash in checkpoint for height " << height;
    return false;
  }

  if (!m_points.insert({ height, h }).second) {
    logger(WARNING) << "Checkpoint already exists.";
    return false;
  }

  return true;
}
//---------------------------------------------------------------------------
bool Checkpoints::load_checkpoints_from_file(const std::string& fileName) {
	std::ifstream file(fileName);
	if (!file) {
		logger(Logging::ERROR, BRIGHT_RED) << "Could not load checkpoints file: " << fileName;
		return false;
	}
	std::string indexString;
	std::string hash;
	uint32_t height;
	while (std::getline(file, indexString, ','), std::getline(file, hash)) {
		try {
			height = std::stoi(indexString);
		} catch (const std::invalid_argument &) {
			logger(Logging::ERROR, BRIGHT_RED) << "Invalid checkpoint file format - "
				<< "could not parse height as a number";
			return false;
		}
		if (!add_checkpoint(height, hash)) {
			return false;
		}
	}
	logger(Logging::INFO) << "Loaded " << m_points.size() << " checkpoints from "	<< fileName;
	return true;
}

//---------------------------------------------------------------------------
bool Checkpoints::is_in_checkpoint_zone(uint32_t  height) const {
  return !m_points.empty() && (height <= (--m_points.end())->first);
}
//---------------------------------------------------------------------------
bool Checkpoints::check_block(uint32_t  height, const Crypto::Hash &h,
                              bool &is_a_checkpoint) const {
  auto it = m_points.find(height);
  is_a_checkpoint = it != m_points.end();
  if (!is_a_checkpoint)
    return true;

  if (it->second == h) {
    logger(Logging::DEBUGGING, Logging::GREEN)
      << "CHECKPOINT PASSED FOR HEIGHT " << height << " " << h;
    return true;
  } else {
    logger(Logging::ERROR) << "CHECKPOINT FAILED FOR HEIGHT " << height
                           << ". EXPECTED HASH: " << it->second
                           << ", FETCHED HASH: " << h;
    return false;
  }
}
//---------------------------------------------------------------------------
bool Checkpoints::check_block(uint32_t  height, const Crypto::Hash &h) const {
  bool ignored;
  return check_block(height, h, ignored);
}
//---------------------------------------------------------------------------
bool Checkpoints::is_alternative_block_allowed(uint32_t  blockchain_height,
                                               uint32_t  block_height) const {
  if (0 == block_height)
    return false;

  if (!m_is_deep_reorg_allowed && block_height < blockchain_height - CryptoNote::parameters::CRYPTONOTE_MINED_MONEY_UNLOCK_WINDOW
    && !is_in_checkpoint_zone(block_height)) {
    logger(Logging::WARNING, Logging::WHITE) << "An attempt of too deep reorganization: "
      << blockchain_height - block_height << ", BLOCK REJECTED";

    return false;
  }

  auto it = m_points.upper_bound(blockchain_height);
  // Is blockchain_height before the first checkpoint?
  if (it == m_points.begin())
    return true;

  --it;
  uint32_t  checkpoint_height = it->first;
  return checkpoint_height < block_height;
}

std::vector<uint32_t> Checkpoints::getCheckpointHeights() const {
  std::vector<uint32_t> checkpointHeights;
  checkpointHeights.reserve(m_points.size());
  for (const auto& it : m_points) {
    checkpointHeights.push_back(it.first);
  }

  return checkpointHeights;
}

#ifndef __ANDROID__
//---------------------------------------------------------------------------
// Re-enabled and modified DNS checkpoint loading function
bool Checkpoints::load_checkpoints_from_dns() {
  std::string domain(CryptoNote::parameters::DNS_CHECKPOINTS_HOST);
  if (domain.empty()) {
    logger(Logging::DEBUGGING) << "DNS checkpoints are not configured.";
    return true;
  }

  std::vector<std::string> records;
  bool res = true;
  auto start = std::chrono::steady_clock::now();
  logger(Logging::DEBUGGING) << "Fetching DNS checkpoint records from " << domain;

  try {
    auto future = std::async(std::launch::async, [this, &res, &domain, &records]() {
      res = Common::fetch_dns_txt(domain, records);  // Fetch TXT records
    });

    std::future_status status = future.wait_for(std::chrono::milliseconds(200));
    if (status == std::future_status::timeout) {
      logger(Logging::DEBUGGING) << "Timeout lookup DNS checkpoint records from " << domain;
      return false;
    } else if (status == std::future_status::ready) {
      future.get();
    }
  }
  catch (std::runtime_error& e) {
    logger(Logging::DEBUGGING) << e.what();
    return false;
  }

  auto dur = std::chrono::steady_clock::now() - start;
  logger(Logging::DEBUGGING) << "DNS query time: " << std::chrono::duration_cast<std::chrono::milliseconds>(dur).count() << " ms";

  if (!records.empty()) {
    std::string combined_record = records[0];
    std::stringstream ss(combined_record);
    std::string checkpoint_str;

    while (std::getline(ss, checkpoint_str, ';')) {
      size_t delimiter_pos = checkpoint_str.find(':');
      if (delimiter_pos == std::string::npos) {
        logger(Logging::ERROR) << "Invalid checkpoint format in DNS record: " << checkpoint_str;
        continue;
      }

      uint32_t height;
      std::string height_str = checkpoint_str.substr(0, delimiter_pos);
      std::string hash_str = checkpoint_str.substr(delimiter_pos + 1);

      std::stringstream height_ss(height_str);
      height_ss >> height;

      Crypto::Hash hash = NULL_HASH;
      if (!height_ss.fail() && Common::podFromHex(hash_str, hash)) {
        std::string hash_hex_str = Common::podToHex(hash);  // Convert Crypto::Hash to string
        if (m_points.count(height) == 0) {
          add_checkpoint(height, hash_hex_str);  // Add checkpoint
          logger(DEBUGGING) << "Added DNS checkpoint: " << height << ":" << hash_hex_str;
        } else {
          logger(DEBUGGING) << "Checkpoint already exists for height " << height << ", skipping.";
        }
      } else {
        logger(Logging::ERROR) << "Failed to parse DNS checkpoint: " << checkpoint_str;
      }
    }
    return true;
  } else {
    logger(Logging::ERROR) << "No DNS records found for checkpoints.";
    return false;
  }
}
#endif

}
