/*
 * The MIT License (MIT)
 * p
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

/* import java.nio.channels.ReadableByteChannel; */
#include <data_utils.h>
#include <array_source_block_encoder.h>
#include <array_data_encoder.h>
#include <partition.h>
#include <parameters/fec_parameters.h>
#include <memory>
#include <vector>

/* static */ uint16_t
data_utils::get_K(fec_parameters params, uint8_t source_block_number)
{
    const uint16_t Kt = params.total_symbols();
    const uint16_t Z = params.num_source_blocks();

    const partition kz = partition(Kt, Z);

    return (source_block_number < kz.JL()) ? kz.IL() : kz.IS();
}
