/*
example_fast-list: An example that uses MiLi's fast lists.
    This file is part of the MiLi Minimalistic Library.

    Copyright (C) Daniel Gutson, FuDePAN 2010
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

    This is an example file.
*/

#include <iostream>
#include "mili/mili.h"

using namespace mili;
using namespace std;

typedef FastList<int, OptimizedShrinkOnRequestPolicy> IntList;

static void print_list(const IntList& list)
{
    IntList::ConstElementHandler h(list.first());

    cout << list.size() << ":" << endl;
    while (h.is_valid())
    {
        cout << *h << endl;
        ++h;
    }

    cout << endl;
}

int main()
{
    IntList list;
    list.new_node(1);
    IntList::RemovableElementHandler two = list.new_node(2);
    list.new_node(3);

    print_list(list);

    // remove 'two'
    two.destroy();
    list.shrink();

    print_list(list);

    two = list.new_node(2);
    print_list(list);

    for (int i = 10; i < 20; ++i)
        list.new_node(i);

    print_list(list);

    list.clear();
    list.shrink();

    for (int i = 10; i < 30; ++i)
        list.new_node(i);

    print_list(list);

    return 0;
}

