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

#ifndef INTERNAL_FUNCTIONS_H
#define INTERNAL_FUNCTIONS_H

#include <algorithm>
#include <cstdint>
#include <parameters/internal_constants.h>
#include <util/extra_math.h>
#include <util/systematic_indices.h>

class internal_functions
{

public:
    static uint64_t get_possible_total_symbols(uint64_t F, uint16_t T);
    static uint64_t get_total_symbols(uint64_t F, uint16_t T);
    static uint16_t top_interleaver_length(uint16_t T);
    static uint16_t KL(uint64_t WS, uint16_t T, uint8_t Al, uint16_t n);
    static uint64_t min_WS(uint16_t Kprime, uint16_t T, uint8_t Al, uint16_t n);

private:
    static uint16_t sub_symbol_size(uint16_t T, uint8_t Al, uint16_t n);
};

#endif
