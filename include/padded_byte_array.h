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


#ifndef INCLUDE_PADDED_BYTE_ARRAY_H_
#define INCLUDE_PADDED_BYTE_ARRAY_H_

#include <util/array_utils.h>
#include <cstdint>
#include <vector>

class padded_byte_array
{
public:
    static padded_byte_array newArray(std::vector<uint8_t> array,
                                      int paddedLen)
    {
        throw "Use the constructor";
    }

    static padded_byte_array newArray(std::vector<uint8_t> array, int off,
                                      int len, int paddedLen)
    {
        throw "Use the constructor";
    }


    padded_byte_array(std::vector<uint8_t> array, int off, int len,
                      int paddedLen);

    std::vector<uint8_t> get_array() const
    {
        return m_array;
    }

    int get_array_offset() const
    {
        return m_array_offset;
    }

    int get_paddingless_length() const
    {
        return m_array_length;
    }

    int get_length() const
    {
        return m_padded_length;
    }

    uint8_t get(int index);
    void set(int index, uint8_t value);

    std::vector<uint8_t> get_bytes(std::vector<uint8_t> dst);
    std::vector<uint8_t> get_bytes(std::vector<uint8_t> dst, int off,
                                   int len);
    std::vector<uint8_t> get_bytes(int index, std::vector<uint8_t> dst);
    std::vector<uint8_t> get_bytes(int index, std::vector<uint8_t> dst,
                                   int off, int len);

    void put_bytes(std::vector<uint8_t> src);
    void put_bytes(std::vector<uint8_t> src, int off, int len);
    void put_bytes(int index, std::vector<uint8_t> src);
    void put_bytes(int index, std::vector<uint8_t> src, int off, int len);

private:
    static void check_index_and_array(int index, int length,
                                      std::vector<uint8_t> dst, int off, int len);

    uint8_t safe_get(int index);
    void safe_set(int index, uint8_t value);

    std::vector<uint8_t> m_array;
    const int m_array_offset;
    const int m_array_length;

    const int m_padded_length;  // must always be > m_array_length
    std::vector<uint8_t> m_padding;
};

#endif  // INCLUDE_PADDED_BYTE_ARRAY_H_
