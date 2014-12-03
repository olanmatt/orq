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

#ifndef INCLUDE_SYMBOLS_STATE_H_
#define INCLUDE_SYMBOLS_STATE_H_

#include <encoding_symbol.h>
#include <source_block_state.h>

#include <vector>
#include <set>
#include <map>

class symbols_state
{
public:
    // Always call this method before accessing the symbols state!
    void lock(void);
    void unlock(void);

    source_block_state get_source_block_state(void);
    void set_source_block_decoding_failure(void);
    bool is_source_block_decoded(void);

    // requires valid esi
    bool contains_source_symbol(uint32_t esi);
    void add_source_symbol(uint32_t esi);

    // XXX(olanmatt): std::vector<uint8_t>?
    std::vector<int> missing_source_symbols(void);
    std::vector<int> received_source_symbols(void);

    // XXX(olanmatt):
    uint16_t num_missing_source_symbols(void);
    uint16_t num_repair_symbols(void);

    // requires valid esi
    bool contains_repair_symbol(uint32_t esi);
    void add_repair_symbol(repair_symbol repair);
    std::vector<repair_symbol> repair_symbols();

    std::set<uint32_t> repair_symbols_eSIs(void);
    bool have_enough_symbols_to_decode(void);

    symbols_state(uint16_t K, int symbol_overhead);

private:
    source_block_state sbState;

    const int/*BitSet*/ m_source_symbols_bit_set;
    // XXX(olanmatt): std::vector<uint8_t>?
    const std::vector<int> m_missing_source_symbols;
    const std::vector<int> m_received_source_symbols;

    const std::map<int, encoding_symbol> m_repair_symbols;

    const uint16_t m_K;
    const int m_symbol_overhead;

    const bool /*lock*/ m_symbols_state_lock;

    // TODO(pbhandari): we might not need it.
    class missing_source_symbols_iterable;
    class received_source_symbols_iterable;
};

#endif  // INCLUDE_SYMBOLS_STATE_H_
