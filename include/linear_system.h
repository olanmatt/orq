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

#ifndef INCLUDE_LINEAR_SYSTEM_H_
#define INCLUDE_LINEAR_SYSTEM_H_

#include <tuple.h>

#include <vector>
#include <cstdint>

using std::vector;
class linear_system
{
public:
    static vector< vector<uint8_t> >
    generate_constraint_matrix(int Kprime);

    static vector<int>
    enc_indexes(int Kprime, tuple tpl);

    static vector<uint8_t>
    enc(int Kprime, vector< vector<uint8_t> > C, tuple tpl, int T);

    static vector< vector<uint8_t> >
    P_inactivation_decoding(vector< vector<uint8_t> > A,
                            vector< vector<uint8_t> > D, int Kprime);

private:
    static void
    initialize_G_LPDC1(vector< vector<uint8_t> > constraint_matrix, int B, int S);
    static void
    initialize_G_LPDC2(vector< vector<uint8_t> > constraint_matrix, int S, int P,
                       int W);
    static void
    initialize_Is(vector< vector<uint8_t> > constraint_matrix, int S, int B);
    static void
    initialize_Ih(vector< vector<uint8_t> > constraint_matrix, int W, int U, int H,
                  int S);

    static vector< vector<uint8_t> > generateMT(int H, int Kprime, int S);
    static vector< vector<uint8_t> > generateGAMMA(int Kprime, int S);

    static void
    initialize_G_ENC(vector< vector<uint8_t> > constraint_matrix, int S, int H,
                     int L, int Kprime);
};
#endif  // INCLUDE_LINEAR_SYSTEM_H_
