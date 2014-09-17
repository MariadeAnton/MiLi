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

#ifndef __GXX_EXPERIMENTAL_CXX0X__

#define COMPILE_ASSERT_TEST
#include "mili/mili.h"

using namespace mili;

declare_static_assert(assert1);

TEST(CompileAssert, test_no_fail)
{
    compile_assert(sizeof(char) == 1, assert1);
    ASSERT_TRUE(bool(template_info<assert1__>::is_equal_to<int>::value));
}

declare_static_assert(assert2);
TEST(CompileAssert, test_fail)
{
    compile_assert(sizeof(char) == 2, assert2); // fails
    ASSERT_TRUE(bool(template_info<assert2__>::is_equal_to<float>::value));
}

#endif
