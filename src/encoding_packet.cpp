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

#include <encoding_packet.h>
#include <parsed.h>
#include <symbol.h>
#include <parameters/parameter_io.h>
#include <cstdint>
#include <vector>

int encoding_packet::source_block_number()
{
    return parameter_io::extract_source_block_number(m_fec_payload_id);
}

int encoding_packet::encoding_symbol_id()
{
    return parameter_io::extract_encoding_symbol_id(m_fec_payload_id);
}

uint32_t encoding_packet::fec_payload_id()
{
    return m_fec_payload_id;
}

uint64_t encoding_packet::number_of_symbols()
{
    return m_num_symbols;
}

std::vector<uint8_t> encoding_packet::symbols()
{
    return m_symbols;
}

uint64_t encoding_packet::symbols_length()
{
    return m_symbols.size();
}

symbol encoding_packet::symbol_type()
{
    return m_type;
}
