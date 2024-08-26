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
    {1, "510e63966e1cc275c89236b3987b5a5be4696c2daf4b12f146617c71437ee2ed"}, 
    {10, "8814c2802e068a917875a55b1579ba195c872ab50b8e22d335319a1b459996de"},
    {20, "58c21bd9c75d1ed0917da3400174cb933292b56192f26ca382e054e1617769a2"},
    {30, "881ab0929cc18c3846a76171a7dc3da8f1cef715878623bc3d2a9e3451b30329"},
    {40, "75f37ba6a24967611a9ab551a860c17c9f53849dd63c780ce70e25b095ff3662"},
    {50, "8398947625bed8210f6b3f0f8a2b6d2b27dbe6d38fad5e8207dcef6335b959d0"}
};

}
