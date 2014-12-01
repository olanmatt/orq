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

#ifndef INCLUDE_ENCODING_PACKET_H_
#define INCLUDE_ENCODING_PACKET_H_

#include <parsed.h>
#include <symbol.h>
#include <parameters/parameter_io.h>

#include <cstdint>
#include <vector>

class encoding_packet
{
public:
    static void new_source_packet(int sbn, int esi,
                                  std::vector<uint8_t> symbols, int num_symbols)
    {
        throw "Use a constructor, with type symbol::SOURCE";
    }

    static void new_repair_packet(int sbn, int esi,
                                  std::vector<uint8_t> symbols, int num_symbols)
    {
        throw "Use a constructor, with type symbol::REPAIR";
    }

    static void parse_packet(int do_not_use_this_function)
    {
        throw "Why would you use this function when I tell you not to";
    }

    static void read_packet_from(int do_not_use_this_function)
    {
        throw "Why would you use this function when I tell you not to";
    }

    uint8_t source_block_number() const;
    uint32_t encoding_symbol_id() const;
    uint32_t fec_payload_id() const;
    uint64_t number_of_symbols() const;
    uint64_t symbols_length() const;
    std::vector<uint8_t> symbols() const;
    symbol symbol_type() const;

    // NOTE:
    // Favour payload over as_array or as_buffer, as the name is clearer
    // and the other two simply call this method anyway.
    std::vector<uint8_t> payload() const;
    std::vector<uint8_t> as_array() const;
    std::vector<uint8_t> as_buffer() const;

    void write_to(std::vector<uint8_t> *array, unsigned int offset = 0) const;

    encoding_packet(int sbn, int esi, std::vector<uint8_t> symbols,
                    int num_symbols, symbol type)
        : m_fec_payload_id(parameter_io::build_fec_payload_id(sbn, esi)),
          m_symbols(symbols),
          m_num_symbols(num_symbols),
          m_type(type)
    { }

private:
    const uint32_t m_fec_payload_id;
    const std::vector<uint8_t> m_symbols;
    const uint64_t m_num_symbols;  // FIXME(pbhandari): I don't even .... WTF?
    const symbol m_type;
};

class source_packet : public encoding_packet
{
    source_packet(int sbn, int esi, std::vector<uint8_t> symbols, int num_symbols)
        : encoding_packet(sbn, esi, symbols, num_symbols, symbol::SOURCE)
    { }
};

class repair_packet : public encoding_packet
{
    repair_packet(int sbn, int esi, std::vector<uint8_t> symbols, int num_symbols)
        : encoding_packet(sbn, esi, symbols, num_symbols, symbol::REPAIR)
    { }
};

#endif  // INCLUDE_ENCODING_PACKET_H_
