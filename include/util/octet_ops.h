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

#ifndef INCLUDE_UTIL_OCTET_OPS_H_
#define INCLUDE_UTIL_OCTET_OPS_H_

#include <cstdint>
#include <stdexcept>

class octet_ops
{
public:
    static uint8_t get_exp(int i);
    static uint8_t get_log(int i);
    static uint8_t addition(uint8_t u, uint8_t v);
    static uint8_t subtraction(uint8_t u, uint8_t v);
    static uint8_t product(uint8_t u, uint8_t v);
    static uint8_t division(uint8_t u, uint8_t v);
    static uint8_t alpha_power(int i);
    static void beta_product(uint8_t beta, uint8_t U[]);
    static void beta_division(uint8_t U[], uint8_t beta);
    static void beta_product(uint8_t beta, uint8_t U[], int pos, int length);
    static void beta_division(uint8_t U[], uint8_t beta, int pos, int length);

private:
    static const int m_OCT_EXP[];
    static const int m_OCT_LOG[];
};

#endif  // INCLUDE_UTIL_OCTET_OPS_H_
