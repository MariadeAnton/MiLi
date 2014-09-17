/*
    This file is part of the MiLi Minimalistic Library.

    Copyright (C) Hugo Arregui and Adrian Remonda FuDePAN 2011
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

#include <iostream>
#include "google/gtest/gtest.h"
#include "google/gmock/gmock.h"
#include "mili/mili.h"

using namespace mili;
using std::cout;

enum MasksSet1
{
    kZero   = 0,
    kOne    = 1,
    kTwo    = 2,
    kThree  = 4,
    kFour   = 8
};

BITWISE_ENUM_ENABLE(MasksSet1)

enum MasksSet2
{
    kEight   = 8,
    kSixteen = 16
};

typedef bitwise_enum<MasksSet1> M1;

TEST(BitwiseEnumsTest, test)
{
    M1 b = kOne | kFour;

    ASSERT_FALSE(b.has_bits(kZero));
    ASSERT_TRUE(b.has_bits(kOne));
    ASSERT_FALSE(b.has_bits(kTwo));
    ASSERT_FALSE(b.has_bits(kThree));
    ASSERT_TRUE(b.has_bits(kFour));

    ASSERT_TRUE(kFour | kEight);
    ASSERT_TRUE(kSixteen | kEight);

    ASSERT_EQ(0x24u, b << 2);
}
