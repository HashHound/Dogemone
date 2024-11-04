// Copyright (c) 2012-2016, The CryptoNote developers, The Bytecoin developers
// Copyright (c) 2016-2024, The Karbo developers
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

#pragma once

#include <cstddef>
#include <initializer_list>

namespace CryptoNote {

struct CheckpointData {
  uint32_t height;
  const char* blockId;
};

const std::initializer_list<CheckpointData> CHECKPOINTS = {
    {100000, "ace904eec86e2428018bba4bbb5f9a0201a653e86051e5f0b654dcbcedbe920f"},
    {101000, "b99fa7cdf12f7bd97cc4a56192eb9a0c1fb4280d0d5164174a0c77eece739b1a"},
    {102000, "3764f64625dcafd0c59907c787b3958324a9e47f07d18ed49461366ea3eee3a8"},
    {102500, "50eec5f43981c2a47f6aff6495b44769c05aad56b0e78315cfcf66e9e2dde13d"},
    {102600, "7e11ff7232c36f71d169b0ffa4043cf13825521b898436269a76167665355890"},
    {102709, "b3dea355b7d13732e04dc518905704bc5571e5591ead637995ee763123e1243a"}
};

}
