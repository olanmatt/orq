/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2014 Matt Olan
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

#include <padded_byte_array.h>
#include <algorithm>
#include <vector>

padded_byte_array::padded_byte_array(std::vector<uint8_t> array, int off,
                                     int len, int paddedLen)
    : m_array(array),
      m_array_offset(off),
      m_array_length(std::min(len, paddedLen)),
      m_padded_length(paddedLen)
{
    check_array_bounds(off, len, m_array.size());
    if (paddedLen < 0) {
        throw "Negative padded length";
    }

    m_padding = std::vector<uint8_t>(get_length() - get_paddingless_length());
}

std::vector<uint8_t> padded_byte_array::get_array() const
{
    return m_array;
}

int padded_byte_array::get_array_offset() const
{
    return m_array_offset;
}

int padded_byte_array::get_paddingless_length() const
{
    return m_array_length;
}

int padded_byte_array::get_length() const
{
    return m_padded_length;
}

int padded_byte_array::get_index() const
{
    return m_index;
}


uint8_t padded_byte_array::safe_get(int index) const
{
    if (index >= m_array_length) {
        return m_padding[index - m_array_length];
    } else {
        return m_array[m_array_offset + index];
    }
}

void padded_byte_array::safe_set(int index, uint8_t value)
{
    if (index >= m_array_length) {
        m_padding[index - m_array_length] = value;
    } else {
        m_array[m_array_offset + index] = value;
    }
}

uint8_t padded_byte_array::get(int index) const
{
    check_index_range(index, get_length());
    return safe_get(index);
}

void padded_byte_array::set(int index, uint8_t value)
{
    check_index_range(index, get_length());
    safe_set(index, value);
}

std::vector<uint8_t> padded_byte_array::get_bytes(std::vector<uint8_t> dst) const
{
    return get_bytes(0, dst, 0, dst.size());
}

std::vector<uint8_t> padded_byte_array::get_bytes(std::vector<uint8_t> dst,
        int off, int len) const
{
    return get_bytes(0, dst, off, len);
}

std::vector<uint8_t> padded_byte_array::get_bytes(int index,
        std::vector<uint8_t> dst) const
{
    return get_bytes(index, dst, 0, dst.size());
}

std::vector<uint8_t> padded_byte_array::get_bytes(int index,
        std::vector<uint8_t> dst, int off, int len) const
{
    check_index_and_array(index, get_length(), dst, off, len);

    int end = off + len;
    for (int d = off, ii = index; d < end; d++, ii++) {
        dst[d] = safe_get(ii);
    }

    return dst;
}

void padded_byte_array::put_bytes(std::vector<uint8_t> src)
{
    put_bytes(0, src, 0, src.size());
}

void padded_byte_array::put_bytes(std::vector<uint8_t> src, int off, int len)
{
    put_bytes(0, src, off, len);
}

void padded_byte_array::put_bytes(int index, std::vector<uint8_t> src)
{
    put_bytes(index, src, 0, src.size());
}

void padded_byte_array::put_bytes(int index, std::vector<uint8_t> src, int off,
                                  int len)
{
    check_index_and_array(index, get_length(), src, off, len);

    int end = off + len;
    for (int s = off, ii = index; s < end; s++, ii++) {
        safe_set(ii, src[s]);
    }
}

void padded_byte_array::check_index_and_array(int index, int length,
        std::vector<uint8_t> dst, int off, int len)
{
    check_index_range(index, length);
    check_array_bounds(off, len, dst.size());

    int remaining = length - index;
    if (len > remaining) {
        throw "Buffer overflow";
    }
}

void padded_byte_array::check_index_range(int index, int length)
{
    if (index < 0 || index >= length) {
        throw "Index out of bounds";
    }
}

void padded_byte_array::check_array_bounds(int off, int len, int arrayFence)
{
    if ((off | len | (off + len) | (arrayFence - (off + len))) < 0) {
        throw "Index out of bounds exception";
    }
}
