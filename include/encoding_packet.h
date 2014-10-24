/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2014 Matt Olan, Prajjwal Bhandari
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
        throw "Use a constructor";
    }

    static void new_repair_packet(int sbn, int esi,
                                  std::vector<uint8_t> symbols, int num_symbols)
    {
        throw "Use a constructor";
    }

    static void parse_packet(int do_not_use_this_function)
    {
        throw "Why would you use this function when I tell you not to";
    }

    static void read_packet_from(int do_not_use_this_function)
    {
        throw "Why would you use this function when I tell you not to";
    }

    int source_block_number()
    {
        throw "Look in fec_parameters";
    }
    int encoding_symbol_id()
    {
        throw "Look in fec_parameters";
    }
    std::vector<uint8_t> as_buffer();

    int get_fec_payload_id();
    int get_number_of_symbols();
    std::vector<uint8_t> get_symbols();
    int get_symbols_length();

    int fec_payload_id();
    int number_of_symbols();

    std::vector<uint8_t> symbols();
    int symbols_length();

    std::vector<uint8_t> as_array();

    void write_to(std::vector<uint8_t> array);
    void write_to(std::vector<uint8_t> array, int offset);
    /* virtual void writeTo(DataOutput out) throws IOException; */
    /* virtual void writeTo(WritableByteChannel ch) throws IOException; */

    virtual symbol symbol_type() = 0;

    virtual ~encoding_packet(void)
    {
        // TODO(pbhandari): delete the vector if needed
        /* delete m_symbols; */
    }
protected:
    encoding_packet(int sbn, int esi, std::vector<uint8_t> symbols, int num_symbols)
        : m_fec_payload_id(parameter_io::build_fec_payload_id(sbn, esi)),
          m_symbols(symbols),
          m_num_symbols(num_symbols)
    { }

private:
    const int m_fec_payload_id;
    const std::vector<uint8_t> m_symbols;
    const int m_num_symbols;
};



class source_packet : public encoding_packet
{
    source_packet(int sbn, int esi, std::vector<uint8_t> symbols, int num_symbols)
        : encoding_packet(sbn, esi, symbols, num_symbols)
    { }

    symbol symbol_type()
    {
        return symbol::SOURCE;
    }
};

class repair_packet : public encoding_packet
{
    repair_packet(int sbn, int esi, std::vector<uint8_t> symbols, int num_symbols)
        : encoding_packet(sbn, esi, symbols, num_symbols)
    { }

    symbol symbol_type()
    {
        return symbol::REPAIR;
    }
};

#endif  // INCLUDE_ENCODING_PACKET_H_
