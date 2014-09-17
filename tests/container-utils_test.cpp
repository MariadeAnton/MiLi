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
#include <string>
#include <vector>
#include <queue>
#include "mili/mili.h"

using namespace mili;

TEST(ContainerUtilsTest, vector)
{
    std::vector<int> v;
    v.push_back(1);
    ASSERT_EQ(1, find(v, 1));
    ASSERT_FALSE(contains(v, 2));
}

struct MapTest: public ::testing::Test
{
    void SetUp()
    {
        m["hello"] = "good bye";
        m["Bonjour"] = "au revoir";
        m["ハロー"] = "さようなら";
        m["hola"] = "adios";
        m["buenas"] = "adios";
    }
    std::map<std::string, std::string> m;
};

TEST_F(MapTest, contains)
{
    ASSERT_FALSE(contains(m, "nothing"));
}

TEST_F(MapTest, remove_first_from)
{
    ASSERT_TRUE(remove_first_from(m, "au revoir"));
}

TEST_F(MapTest, remove_all_from)
{
    ASSERT_TRUE(remove_all_from(m, "adios"));
}

TEST_F(MapTest, found)
{
    ASSERT_EQ("good bye", find(m, "hello"));
}

TEST_F(MapTest, not_found)
{
    ASSERT_THROW(find(m, "world"), ElementNotFound);
}

TEST(ContainerUtilsTest, queue)
{
    std::queue<int> myqueue;
    insert_into(myqueue, 100);
    insert_into(myqueue, 100);
}
