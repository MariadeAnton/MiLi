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

#include <vector>
#include "google/gtest/gtest.h"
#include "google/gmock/gmock.h"
#include "mili/mili.h"

using namespace mili;

struct MockObject
{
    int i;
    float f;
    MOCK_CONST_METHOD0(die, void());
    ~MockObject()
    {
        die();
    }
};

TEST(DeleteContainerTest, delete_container)
{
    std::vector<MockObject*> vec1;

    MockObject* o1 = new MockObject;
    MockObject* o2 = new MockObject;
    MockObject* o3 = new MockObject;
    vec1.push_back(o1);
    vec1.push_back(o2);
    vec1.push_back(o3);

    EXPECT_CALL(*o1, die()).Times(1);
    EXPECT_CALL(*o2, die()).Times(1);
    EXPECT_CALL(*o3, die()).Times(1);
    delete_container(vec1);
}
