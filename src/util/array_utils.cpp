/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2014 Matt Olan, Prajjwal Bhandari.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <util/array_utils.h>
#include <cstdint>
#include <string>
#include <vector>
#include <stdexcept>

template<>
std::vector<uint8_t> to_byte_array(const uint8_t &elem)
{
    return std::vector<uint8_t> {elem};
}

template<>
std::vector<uint8_t> to_byte_array(const uint16_t &elem)
{
    return std::vector<uint8_t> { (uint8_t)(elem >> 8), (uint8_t)(elem)};
}

template<>
std::vector<uint8_t> to_byte_array(const uint32_t &elem)
{
    std::vector<uint8_t> vec {};
    for (int i = 4; i > 0; --i) {
        vec.push_back(static_cast<uint8_t>(elem >> (8 * i)));
    }

    return vec;
}

template<>
std::vector<uint8_t> to_byte_array(const uint64_t &elem)
{
    std::vector<uint8_t> vec {};
    for (int i = 8; i > 0; --i) {
        vec.push_back(static_cast<uint8_t>(elem >> (8 * i)));
    }

    return vec;
}

template<>
std::vector<uint8_t> to_byte_array(const std::vector<uint8_t> &elem)
{
    std::vector<uint8_t> vec = elem;  // copy the vector
    return vec;
}
