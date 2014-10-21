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

#include <util/deg.h>

// 5.3.5.2 Degree Generator
const unsigned int deg::m_table1[] = {
    0,
    5243,
    529531,
    704294,
    791675,
    844104,
    879057,
    904023,
    922747,
    937311,
    948962,
    958494,
    966438,
    973160,
    978921,
    983914,
    988283,
    992138,
    995565,
    998631,
    1001391,
    1003887,
    1006157,
    1008229,
    1010129,
    1011876,
    1013490,
    1014983,
    1016370,
    1017662,
    1048576
};

int deg::generate(unsigned int v, int W)
{
    for (int i = 0; i < 31; i++) {
        if (v < m_table1[i]) {
            return (std::min(i, W - 2));
        }
    }

    throw std::runtime_error("Inconsistent table state");
}
