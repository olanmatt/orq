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

#include <tuple.h>

// 5.3.3.2 Source Symbol Tuples
tuple::tuple(int k_prime, long x)
{
    int Ki = systematic_indices::get_k_index(k_prime);
    int S = systematic_indices::S(Ki);
    int H = systematic_indices::H(Ki);
    int W = systematic_indices::W(Ki);
    int L = k_prime + S + H;
    int J = systematic_indices::J(Ki);
    int P = L - W;
    long P1 = matrix_utilities::ceil_prime(P);

    long A = 53591 + J * 997;
    if (A % 2 == 0) {
        A++;
    }

    long B = 10267 * (J + 1);

    long y = (B + x * A) % 4294967296L;  // 2^^32

    long v = rand::generate(y, 0, 1048576L);  // 2^^20

    m_d = deg::generate(v, W);
    m_a = 1 + rand::generate(y, 1, W - 1);
    m_b = rand::generate(y, 2, W);
    if (m_d < 4) {
        m_d1 = 2 + rand::generate(x, 3, 2L);
    } else {
        m_d1 = 2;
    }
    m_a1 = 1 + rand::generate(x, 4, P1 - 1);
    m_b1 = rand::generate(x, 5, P1);
}

long tuple::D()
{
    return m_d;
}

long tuple::A()
{
    return m_a;
}

long tuple::B()
{
    return m_b;
}

long tuple::D1()
{
    return m_d1;
}

long tuple::A1()
{
    return m_a1;
}

long tuple::B1()
{
    return m_b1;
}
