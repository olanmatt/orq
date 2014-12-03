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

#ifndef INCLUDE_SBD_INFO_H_
#define INCLUDE_SBD_INFO_H_

#include <source_block_state.h>
#include <parameters/fec_parameters.h>

#include <cstdint>
#include <map>
#include <set>
#include <vector>

class sbd_info
{
public:
    static sbd_info newInformation(
        int sbn,
        source_block_state state,
        std::set<int> missingSourceSymbols,
        std::set<int> availableRepairSymbols)
    {
        throw "Use the constructor.";
    }

    int sourceBlockNumber(void) const;

    source_block_state state(void);
    std::set<int> missing_source_symbols(void) const;
    std::set<int> available_repair_symbols(void) const;
    bool operator==(const sbd_info &other) const;

    std::vector<uint8_t> as_array(void) const;
    std::vector<uint8_t> as_buffer(void) const;
    void write_to(std::vector<uint8_t> array, int offset = 0);

    /*
     * Requires unmodifiable sets!
     */
    sbd_info(uint8_t sbn, source_block_state state,
             const std::set<uint8_t> missing_source_symbols,
             const std::set<uint8_t> available_repair_symbols);

private:
    int get_encoded_byte_size(void) const;

    const uint8_t m_sbn;
    const source_block_state m_state;
    const std::set<uint8_t> m_missing_source_symbols;
    const std::set<uint8_t> m_available_repair_symbols;

    /*********************************************************************
     *        TODO(pbhandari): MOVE TO CPP FILE LATER                    *
     *                      FIX PARAMETERS AS WELL                       *
     *********************************************************************/

    /*
     * -------------------------- state/byte methods --------------------------
     */
    // throws NullPointerException if an invalid state is passed as argument
    static uint8_t stateToByte(source_block_state state);

    // returns null if an invalid byte is passed as argument
    static source_block_state byteToState(uint8_t b);

    /*
     * -------------------------- Write/Read methods --------------------------
     */
    static void writeSBN(uint8_t sbn, std::vector<uint8_t> buf);

    static int readSBN(std::vector<uint8_t> buf, fec_parameters fecParams);

    static int checkSBN(uint8_t sbn, fec_parameters fecParams);

    static void writeState(source_block_state state, std::vector<uint8_t> buf);

    static source_block_state readState(std::vector<uint8_t> buf);

    static source_block_state checkState(source_block_state state);


    /* static const std::map<source_block_state, uint8_t> STATE_BYTE_VALUES; */
    /* static const std::map<uint8_t, source_block_state> BYTE_STATE_VALUES; */
    /* static { */
    /*     final byte incomplete = 1; */
    /*     final byte decoded = 2; */
    /*     final byte decodingFailure = 3; */

    /*     STATE_BYTE_VALUES.put(source_block_state.INCOMPLETE, incomplete); */
    /*     BYTE_STATE_VALUES.put(incomplete, source_block_state.INCOMPLETE); */

    /*     STATE_BYTE_VALUES.put(source_block_state.DECODED, decoded); */
    /*     BYTE_STATE_VALUES.put(decoded, source_block_state.DECODED); */

    /*     STATE_BYTE_VALUES.put(source_block_state.DECODING_FAILURE, decodingFailure); */
    /*     BYTE_STATE_VALUES.put(decodingFailure, source_block_state.DECODING_FAILURE); */
    /* } */

    // ========================== useful ESI bounds ==========================
    static void writeMissingSourceSymbols(std::set<int> missing,
                                          std::vector<uint8_t> buf);

    static int readNumMissingSourceSymbols(std::vector<uint8_t> buf, int K,
                                           source_block_state state);

    static int checkNumMissing(int numMiss, int K, source_block_state state);

    // requires valid numMiss
    static std::set<int> readMissingSourceSymbols(std::vector<uint8_t> buf,
            int numMiss, int K);

    static void addMissingSourceSymbolESI(int esi, std::set<int> missing, int K);

    static void writeAvailableRepairSymbols(std::set<int> available,
                                            std::vector<uint8_t> buf);

    static int readNumAvailableRepairSymbols(std::vector<uint8_t> buf, int K,
            source_block_state state);

    static int checkNumAvailable(int numAvail, int K, source_block_state state);
    // requires valid numAvail
    static std::set<int> readAvailableRepairSymbols(std::vector<uint8_t> buf,
            int numAvail, int K);

    static void addAvailableRepairSymbolESI(int esi, std::set<int> available,
                                            int K);
};
#endif  // INCLUDE_SBD_INFO_H_
