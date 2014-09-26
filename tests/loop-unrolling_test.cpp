/*
    This file is part of the MiLi Minimalistic Library.

    Copyright (C) Hugo Arregui, FuDePAN 2011
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt in the root directory or 
    copy at http://www.boost.org/LICENSE_1_0.txt)
    
    MiLi IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
    SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
    FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
    ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.

    This is a test file.
*/

#include "google/gtest/gtest.h"
#include "google/gmock/gmock.h"
#include "mili/mili.h"

using namespace mili;

template <class T>
struct BitCounter
{
    T value;
    size_t ret;

    BitCounter(T value)
        : value(value),
          ret(0)
    {}

    void operator()()
    {
        ret += value & 1;
        value >>= 1;
    }
};

template <class T>
inline size_t CountBits(T x)
{
    BitCounter<T> bc(x);
    FOR<sizeof(T) * 8, BitCounter<T> >::iterate(bc);
    return bc.ret;
}

TEST(LoopUnrollingTest, test)
{
    int i = -1;
    ASSERT_EQ(sizeof(int) * 8, CountBits(i));
}
