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

#include <encoding_symbol.h>
#include <padded_byte_array.h>
#include <util/systematic_indices.h>
#include <cstdint>
#include <vector>

using std::vector;

uint32_t
encoding_symbol::esi(void) const
{
    return m_esi;
}

uint32_t
encoding_symbol::get_isi(int K) const
{
    return systematic_indices::ceil(K) - K + esi();
}

/*******************
 *  source_symbol  *
 *******************/
// TODO(olanmatt) constructor and destructor
source_symbol::~source_symbol(void)
{
    /* NO-OP */
}
vector<uint8_t>
source_symbol::data(void) const
{
    // copy m_data into new vector and return that
    vector<uint8_t> data = m_data.get_array();
    return data;
}
const vector<uint8_t>
source_symbol::transport_data(void) const
{
    return m_transport_buffer;
}

int
source_symbol::transport_size(void) const
{
    // m_transport_buffer.remaining();
    return 0;  // TODO(olanmatt):
}

/* static */ vector<uint8_t>
source_symbol::prepare_transport_buffer(padded_byte_array data)
{
    if (data.get_paddingless_length() == data.get_length()) {
        // need to return a slice of the wrapped buffer,
        // otherwise the buffer position will be equal to data.arrayOffset()...
        // return ByteBuffer.wrap(data.get_array(), data.get_array_offset(), data.get_length()).slice();
    } else {
        vector<uint8_t> padded = data.get_bytes(vector<uint8_t> (data.get_length()));
        // return ByteBuffer.wrap(paddedCopy);
    }
    return vector<uint8_t>();
}


/*******************
 *  repair_symbol  *
 *******************/
// TODO(olanmatt) constructor and destructor

repair_symbol::~repair_symbol(void)
{
    /* NO-OP */
}

vector<uint8_t>
repair_symbol::data(void) const
{
    vector<uint8_t> data = m_data;
    return data;
}

const vector<uint8_t>
repair_symbol::transport_data(void) const
{
    return m_transport_buffer;
}

int
repair_symbol::transport_size(void) const
{
    // m_transport_buffer.remaining();
    return 0;  // TODO(olanmatt):
}

/* static */ vector<uint8_t>
repair_symbol::prepare_transport_buffer(vector<uint8_t> data)
{
    // return ByteBuffer.wrap(data);
    return data;
}
