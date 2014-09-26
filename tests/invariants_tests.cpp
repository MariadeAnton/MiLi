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
#include <iostream>
#include "mili/mili.h"

using namespace mili;

invariant::NeverNull<const char> get_message(invariant::InRange < int, -1, 1 > /*number*/)
{
    return "Hello World\n";
}

TEST(InvariantsTest, function_invariant)
{
    ASSERT_EQ("Hello World\n", get_message(-1));
    ASSERT_THROW(get_message(2), InvariantNotMet);
}

struct AClass
{
    int x;
    int y;
    void setxy(int newx, int newy)
    {
        x = newx;
        y = newy;
    }
};

bool AClassInvariant(const AClass& aclass)
{
    return aclass.x + aclass.y > 0;
};

typedef InvariantClass<AClass, AClassInvariant> AClass_inv;

TEST(InvariantsTest, class_invariant)
{
    AClass aclass;
    AClass_inv inv(aclass);
    inv->setxy(3, 4);
    ASSERT_EQ(3, inv->x);
    ASSERT_THROW(inv->setxy(-9, 0), InvariantNotMet);
}
