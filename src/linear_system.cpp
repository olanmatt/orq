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

#include <linear_system.h>
#include <tuple.h>

#include <vector>
#include <cstdint>

/* static */ vector< vector<uint8_t> >
linear_system::generate_constraint_matrix(int Kprime)
{
    throw "Unimplemented";
}

/* static */ vector<int>
linear_system::enc_indexes(int Kprime, tuple tpl)
{
    throw "Unimplemented";
}

/* static */ vector<uint8_t>
linear_system::enc(int Kprime, vector< vector<uint8_t> > C, tuple tpl, int T)
{
    throw "Unimplemented";
}

/* static */ vector< vector<uint8_t> >
linear_system::P_inactivation_decoding(vector< vector<uint8_t> > A,
                                       vector< vector<uint8_t> > D, int Kprime)
{
    throw "Unimplemented";
}

/* static */ void
linear_system::initialize_G_LPDC1(vector< vector<uint8_t> > constraint_matrix,
                                  int B, int S)
{
    throw "Unimplemented";
}
/* static */ void
linear_system::initialize_G_LPDC2(vector< vector<uint8_t> > constraint_matrix,
                                  int S, int P, int W)
{
    throw "Unimplemented";
}
/* static */ void
linear_system::initialize_Is(vector< vector<uint8_t> > constraint_matrix, int S,
                             int B)
{
    throw "Unimplemented";
}
/* static */ void
linear_system::initialize_Ih(vector< vector<uint8_t> > constraint_matrix, int W,
                             int U, int H, int S)
{
    throw "Unimplemented";
}

/* static */ vector< vector<uint8_t> > linear_system::generateMT(int H,
        int Kprime,
        int S)
{
    throw "Unimplemented";
}
/* static */ vector< vector<uint8_t> > linear_system::generateGAMMA(int Kprime,
        int S)
{
    throw "Unimplemented";
}

/* static */ void
linear_system::initialize_G_ENC(vector< vector<uint8_t> > constraint_matrix,
                                int S, int H, int L, int Kprime)
{
    throw "Unimplemented";
}
