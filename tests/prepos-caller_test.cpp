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
#include "mili/prepos_printer.h"
#include "mili/prepos_mutex.h"

using namespace mili;

class PrePosMock
{
public:
    void operator()() const
    {
        mocked_operator();
    }
    MOCK_CONST_METHOD0(mocked_operator, void());

};

class Foo
{
public:
    MOCK_CONST_METHOD0(f, void());
};

TEST(PreposCallerTest, bchain)
{
    Foo t;
    PrePosMock pre, pos;
    PrePosCaller<Foo* const, PrePosMock, PrePosMock> ppc(&t, pre, pos);
    testing::Expectation pre_expectation = EXPECT_CALL(pre, mocked_operator()).Times(1);
    testing::Expectation f_expectation = EXPECT_CALL(t, f()).Times(1).After(pre_expectation);
    EXPECT_CALL(pos, mocked_operator()).Times(1).After(f_expectation);
    ppc->f();
}
