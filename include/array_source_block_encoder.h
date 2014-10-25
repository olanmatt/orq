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

#ifndef INCLUDE_ARRAY_SOURCE_BLOCK_ENCODER_H_
#define INCLUDE_ARRAY_SOURCE_BLOCK_ENCODER_H_

class array_data_encoder;

#include <encoding_symbol.h>
#include <encoding_packet.h>
#include <parameters/fec_parameters.h>
#include <memory>
#include <vector>

class array_source_block_encoder
{
public:
    // requires valid arguments
    static array_source_block_encoder new_encoder(array_data_encoder& data_encoder,
            std::vector< std::vector<uint8_t> > array, int array_offset,
            fec_parameters fec_params, int source_block_num, int K)
    {
        throw "Use the constructor";
    }

    static std::vector<encoding_symbol> prepare_source_symbols(
        std::vector<uint8_t> array, int array_offset, fec_parameters fec_params, int K);

    array_data_encoder get_data_encoder(void);

    int get_source_block_number(void);

    int get_number_source_symbols(void);

    encoding_packet get_encoding_packet(int esi);

    encoding_packet source_packet(int esi);
    encoding_packet source_packet(int esi, int num_symbols);

    encoding_packet repair_packet(int esi);
    encoding_packet repair_packet(int esi, int num_symbols);

    /* iterable_builder new_iterable_builder() { return new iter_builder(this); } */

    std::vector<encoding_packet> source_packets_iterable();
    std::vector<encoding_packet> repair_packets_iterable(int num_packets);

    array_source_block_encoder(array_data_encoder data_encoder,
                               std::vector<encoding_symbol> source_symbols,
                               int source_block_number, int K);

private:
    void check_generic_encoding_symbol_esi(int esi);

    // requires valid ESI
    void check_source_symbol_esi(int esi);

    // requires valid ESI
    void check_num_source_symbols(int esi, int num_symbols);

    // requires valid ESI
    void check_repair_symbol_esi(int esi);

    // requires valid ESI
    void check_num_repair_symbols(int esi, int num_symbols);

    // requires valid ESI
    source_symbol get_source_symbol(int esi);

    // requires valid ESI
    repair_symbol get_repair_symbol(int esi);

    // use only this method for access to the intermediate symbols
    std::vector< std::vector<uint8_t> > get_intermediate_symbols();

    fec_parameters get_fec_parameters();

    int m_source_block_number;
    int m_K;
    int m_Kprime;
    std::shared_ptr<array_data_encoder> m_data_encoder;
    std::vector< std::shared_ptr<encoding_symbol> > m_source_symbols;
    std::vector< std::vector<uint8_t> > m_intermediate_symbols;

    class encoding_packet_iterator;
    class iter_builder;
};


class array_source_block_encoder::encoding_packet_iterator
{
public:
    bool hasNext()
    {
        return m_next_esi < m_fence;
    }

    void remove()
    {
        throw "Unsupported Operation";
    }

    encoding_packet next();

    encoding_packet_iterator(array_source_block_encoder encoder,
                             int starting_esi, int ending_esi)
        : m_encoder(encoder), m_fence(ending_esi + 1), m_next_esi(starting_esi)
    {
        if (ending_esi < starting_esi) {
            throw "starting_esi > ending_esi";
        }
    }

private:
    const array_source_block_encoder m_encoder;
    const int m_fence;
    int m_next_esi;
};

class array_source_block_encoder::iter_builder
{
public:
    iter_builder start_at(int esi);
    iter_builder start_at_initial_source_symbol();
    iter_builder start_at_initial_repair_symbol();

    iter_builder end_at(int esi);
    iter_builder end_at_final_source_symbol();

    std::vector<encoding_packet> build();

    explicit iter_builder(array_source_block_encoder encoder)
        : m_encoder(encoder), m_starting_esi(0),
          m_ending_esi(internal_constants::ESI_max)
    { }

private:
    // requires valid ESI
    void set_starting_esi(int esi);

    // requires valid ESI
    void set_ending_esi(int esi);

    const array_source_block_encoder m_encoder;
    int m_starting_esi;
    int m_ending_esi;
};

#endif  // INCLUDE_ARRAY_SOURCE_BLOCK_ENCODER_H_
