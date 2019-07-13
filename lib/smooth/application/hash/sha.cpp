// Smooth - C++ framework for writing applications based on Espressif's ESP-IDF.
// Copyright (C) 2017 Per Malmberg (https://github.com/PerMalmberg)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.

#include <smooth/application/hash/sha.h>
#include <mbedtls/sha1.h>
#include <mbedtls/sha256.h>

namespace smooth::application::hash
{
    std::array<uint8_t, 20> sha1(const uint8_t* data, std::size_t len)
    {
        std::array<uint8_t,20> buff{};
        mbedtls_sha1_ret(data, len, buff.data());
        return buff;
    }

    std::array<uint8_t, 32> sha256(const uint8_t* data, std::size_t len)
    {
        std::array<uint8_t,32> buff{};
        mbedtls_sha256_ret(data, len, buff.data(), 0);
        return buff;
    }
}