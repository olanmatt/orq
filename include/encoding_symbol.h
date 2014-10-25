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

#ifndef INCLUDE_ENCODING_SYMBOL_H_
#define INCLUDE_ENCODING_SYMBOL_H_

#include <padded_byte_array.h>
#include <cstdint>
#include <vector>

class encoding_symbol
{
public:
    static void new_source_symbol(int esi, padded_byte_array data)
    {
        throw "Use source_symbol(int, padded_byte_array)";
    }

    static void new_repair_symbol(int esi, std::vector<uint8_t> data)
    {
        throw "Use source_symbol(int, padded_byte_array)";
    }

    virtual std::vector<uint8_t> data() = 0;
    virtual std::vector<uint8_t> transport_data() = 0;
    virtual int transport_size() = 0;

    int esi(void);
    int get_isi(int source_symbols_per_block);

    explicit encoding_symbol(int esi): m_esi(esi) { }
    virtual ~encoding_symbol(void);

private:
    const int m_esi;
};


class source_symbol : public encoding_symbol
{
public:
    std::vector<uint8_t> data(void);  // Arrays.copyOf(m_data, m_data.length);
    std::vector<uint8_t> transport_data(void);  // m_transport_buffer as read-only
    int transport_size(void);  // m_transport_buffer.remaining();

    source_symbol(int esi, padded_byte_array data_array);
    ~source_symbol(void);

private:
    static std::vector<uint8_t> prepare_transport_buffer(padded_byte_array
            data_array);

    const padded_byte_array m_data;
    const std::vector<uint8_t> m_transport_buffer;
};


class repair_symbol : public encoding_symbol
{
public:
    std::vector<uint8_t> data(void);
    std::vector<uint8_t> transport_data(void);
    int transport_size(void);

    repair_symbol(int esi, std::vector<uint8_t> data_array);
private:
    static std::vector<uint8_t> prepare_transport_buffer(std::vector<uint8_t> data);

    const std::vector<uint8_t> m_data;
    const std::vector<uint8_t> m_transport_buffer;
};

#endif  // INCLUDE_ENCODING_SYMBOL_H_
