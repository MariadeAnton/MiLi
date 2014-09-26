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

TEST(AutoArrayTest, create)
{
    auto_array<int> p(new int[30]);
}

TEST(AutoArrayTest, get)
{
    auto_array<int> p(new int[30]);
    int* array = p.get();
    ASSERT_TRUE(array != NULL);
}

TEST(AutoArrayTest, subscript)
{
    auto_array<int> p(new int[30]);
    p[1] = 1;
    ASSERT_EQ(1, p[1]);
}

TEST(AutoArrayTest, release)
{
    auto_array<int> p(new int[30]);
    p.release();
    ASSERT_TRUE(p.get() == NULL);
}

TEST(AutoArrayTest, reset)
{
    int* other = new int[20];
    auto_array<int> p(new int[30]);
    p.reset(other);
    ASSERT_EQ(other, p.get());
}
