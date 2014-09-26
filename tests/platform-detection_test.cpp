/*
    This file is part of the MiLi Minimalistic Library.

    Copyright (C) Daniel Muñoz, FuDePAN 2012
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
#include "mili/mili.h"

TEST(PlatformDetectionTest, OperatingSystem)
{
    ASSERT_EQ(MILI_OS_LINUX,	1);
    ASSERT_EQ(MILI_OS_WINDOWS,	2);
    ASSERT_EQ(MILI_OS_MAC,	3);
    ASSERT_EQ(MILI_OS_UNKNOWN,	4);

    ASSERT_TRUE( (MILI_OS == MILI_OS_LINUX)	\
               ^ (MILI_OS == MILI_OS_WINDOWS)	\
               ^ (MILI_OS == MILI_OS_MAC)	\
               ^ (MILI_OS == MILI_OS_UNKNOWN) );
}

TEST(PlatformDetectionTest, Compiler)
{
    ASSERT_EQ(MILI_COMPILER_VS,		1);
    ASSERT_EQ(MILI_COMPILER_GCC,	2);
    ASSERT_EQ(MILI_COMPILER_ICC,	3);
    ASSERT_EQ(MILI_COMPILER_UNKNOWN,	4);

    ASSERT_TRUE( (MILI_COMPILER == MILI_COMPILER_VS)	\
               ^ (MILI_COMPILER == MILI_COMPILER_GCC)	\
               ^ (MILI_COMPILER == MILI_COMPILER_ICC)	\
               ^ (MILI_COMPILER == MILI_COMPILER_UNKNOWN) );
}

