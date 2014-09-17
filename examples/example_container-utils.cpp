/*
find_utils: A minimal library with generic find functions with exceptions.
    This file is part of the MiLi Minimalistic Library.

    Copyright (C) Daniel Gutson, Ezequiel S. Velez, FuDePAN 2009
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

#include <string>
#include <iostream>
#include <vector>
#include <string>
#include <queue>

#include "mili/mili.h"

using namespace std;
using namespace mili;

static void test_autonomous_iterators();
template<class T>
static void show_map_elements(CAutonomousIterator<T> it);
template <class T>
static void insert_elements(T& container);

int main()
{
    vector<int> v;
    v.push_back(1);

    map<string, string> m;
    m["hello"] = "good bye";
    m["Bonjour"] = "au revoir";
    m["ハロー"] = "さようなら";
    m["hola"] = "adios";
    m["buenas"] = "adios";

    CAutonomousIterator<map<string, string> > mi(m);
    try
    {
        cout << contains(v, 2) << endl;               /* will print 0 (false) */
        cout << contains(m, "nothing") << endl;       /* will print 0 (false) */

        cout << "map: " << endl;
        cout << remove_first_from(m, "au revoir") << endl; /* will print 1 (true) */
        cout << remove_all_from(m, "adios") << endl;      /* will print 1 (true) */

        CAutonomousIterator<map<string, string> > mi(m);
        show_map_elements(mi);

        test_autonomous_iterators();

        cout << find(v, 1) << endl;                   /* will print 1 */
        cout << find(m, "hello") << endl;             /* will print "goodbye" */
        cout << find(m, "world") << endl;             /* will throw ElementNotFound */
    }
    catch (ElementNotFound)
    {
        cerr << "Element not found!" << endl;
    }

    /* TEST - queue in container_utils::insert_into */
    queue<int> myqueue;
    insert_elements(myqueue);

    return 0;
}

template <class T>
static void insert_elements(T& container)
{
    insert_into(container, 100);
    insert_into(container, 100);
    insert_into(container, 100);
    insert_into(container, 200);
    insert_into(container, 300);
    insert_into(container, 400);
    insert_into(container, 400);
}

template <class T>
static void delete_elements(T& container)
{
    remove_first_from(container, 400);    /* amending iterators */
    remove_all_from(container, 100);      /* amending iterators */

}

template <class T>
static void show_elements(const T& container)
{
    CAutonomousIterator<T> it(container);
    while (!it.end())
        cout << *(it++) << endl;
}

template <class T>
static void show_map_elements(CAutonomousIterator<T> it)
{
    while (!it.end())
    {
        cout << it->first << " " << it->second << endl;
        ++it;
    }
}

template <class T>
static void inc_one(T& container)
{
    AutonomousIterator<T> it(container);
    while (!it.end())
    {
        ++(*it);
        ++it;
    }
}

struct S
{
    int x;
};

void test_autonomous_iterators()
{
    // Examples using containers of integers:
    vector<int> v;
    list<int> l;
    set<int> s;
    Ranker<int> r(5);

    insert_elements(v);
    insert_elements(l);
    insert_elements(s);
    insert_elements(r);

    delete_elements(v);
    delete_elements(l);
    delete_elements(s);
    delete_elements(r);

    inc_one(v);
    inc_one(l);


    CAutonomousIterator<vector<int> > vi(v);
    CAutonomousIterator<list<int> >   li(l);
    CAutonomousIterator<set<int> >    si(s);
    CAutonomousIterator<Ranker<int> > ri(r);

    cout << "vector: " << endl;
    show_elements(v);
    cout << "list: " << endl;
    show_elements(l);
    cout << "set: " << endl;
    show_elements(s);
    cout << "Ranker: " << endl;
    show_elements(r);

    // Example using a container of a structure:
    vector<S> vs;
    S ss;
    insert_into(vs, ss);
    AutonomousIterator<vector<S> > vsi(vs);
    vsi->x = 2;
    (*vsi).x++;
    CAutonomousIterator<vector<S> > cvsi(vs);
    cout << vsi->x << endl;
    cout << (*vsi).x << endl;
}
