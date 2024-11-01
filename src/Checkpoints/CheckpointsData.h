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
    {91000, "89af7dac7b5c5524f0d8702df8be479a30633d45ec4654f2a1fa3bad8f5ae648"},
    {92000, "052342c158685e1822f8c9c835e8f9cef8ecc4ec98295070ae2b740df9526a91"},
    {93000, "a894f34f92a079be6ca0f91f2260ce98a4da0e1039b5500a066e45264723af22"},
    {94000, "b8022db2f285eae07bf6ade4123865c2bfd6de0c59dd4134bb9abb378106874e"},
    {95000, "941fc1887be99f21363fbab9ef6096a78f35f8e35cf292c54b1232c86dfd8724"},
    {96000, "5c81630b2d804db918d95a26de3634d466942484203f5290c1afee7be7af7aaa"}
};

}
