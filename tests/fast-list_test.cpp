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
#include <list>
#include "mili/mili.h"

using namespace mili;

typedef FastList<int, OptimizedShrinkOnRequestPolicy> IntList;

static bool compare(const IntList& flist, const std::list<int>& l)
{
    if (flist.size() == l.size())
    {
        IntList::ConstElementHandler h(flist.first());
        std::list<int>::const_iterator it = l.begin();

        bool equals = true;
        while (h.is_valid() && equals)
        {
            equals = *h == *it;
            ++h;
            ++it;
        }
        return equals;
    }
    else
    {
        return false;
    }
}

TEST(FastListTest, test)
{
    IntList flist;
    flist.new_node(1);
    IntList::RemovableElementHandler two = flist.new_node(2);
    flist.new_node(3);

    std::list<int> rlist;
    rlist.push_back(1);
    rlist.push_back(2);
    rlist.push_back(3);
    ASSERT_TRUE(compare(flist, rlist));

    // remove 'two'
    two.destroy();
    flist.shrink();
    rlist.remove(2);
    ASSERT_TRUE(compare(flist, rlist));

    two = flist.new_node(2);
    rlist.push_back(2);
    ASSERT_TRUE(compare(flist, rlist));

    for (int i = 10; i < 20; ++i)
    {
        flist.new_node(i);
        rlist.push_back(i);
    }
    ASSERT_TRUE(compare(flist, rlist));

    flist.clear();
    flist.shrink();
    rlist.clear();
    ASSERT_TRUE(flist.empty());
    ASSERT_TRUE(compare(flist, rlist));

    for (int i = 10; i < 30; ++i)
    {
        flist.new_node(i);
        rlist.push_back(i);
    }
    ASSERT_TRUE(compare(flist, rlist));
}

