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
#include <util/array_utils.h>

#include <cstdint>
#include <vector>

uint8_t
encoding_packet::source_block_number() const
{
    return parameter_io::extract_source_block_number(m_fec_payload_id);
}

uint32_t
encoding_packet::encoding_symbol_id() const
{
    return parameter_io::extract_encoding_symbol_id(m_fec_payload_id);
}

uint32_t
encoding_packet::fec_payload_id() const
{
    return m_fec_payload_id;
}

uint64_t
encoding_packet::number_of_symbols() const
{
    return m_num_symbols;
}

std::vector<uint8_t>
encoding_packet::symbols() const
{
    return m_symbols;
}

uint64_t
encoding_packet::symbols_length() const
{
    return m_symbols.size();
}

symbol
encoding_packet::symbol_type() const
{
    return m_type;
}

std::vector<uint8_t>
encoding_packet::payload() const
{
    std::vector<uint8_t> packet = {to_byte_array(m_fec_payload_id)};
    std::vector<uint8_t> symbol_length = to_byte_array(m_num_symbols);

    packet.insert(packet.end(), symbol_length.begin(), symbol_length.end());
    packet.insert(packet.end(), m_symbols.begin(), m_symbols.end());

    return packet;
}

std::vector<uint8_t>
encoding_packet::as_array() const
{
    return payload();
}

std::vector<uint8_t>
encoding_packet::as_buffer() const
{
    return payload();
}

void
encoding_packet::write_to(std::vector<uint8_t> *array,
                          unsigned int offset) const
{
    if (offset) {
        throw "Offset not supported";
    }

    std::vector<uint8_t> packet = payload();

    array->insert(array->end(), packet.begin(), packet.end());
}
