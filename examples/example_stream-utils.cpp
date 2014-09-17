/*
stream_utils: A minimal library that provides CSV and other file/stream
    functionalities..
    This file is part of the MiLi Minimalistic Library.

    Copyright (C) Daniel Gutson, FuDePAN 2009
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

#include <vector>
#include <iostream>
#include <fstream>
#include "mili/mili.h"

using namespace mili;
using namespace std;

static void generate_file(const char* name)
{
    ofstream f(name);
    set<float> v;

    for (int i = 0; i < 10; i++)
    {
        v.clear();
        for (int j = 0; j <= i; j++)
            insert_into(v, i + j / 10.0f);

        f << v; /* PROVIDED BY MiLi */

        f << endl;
    }
}

static void load_file(const char* name)
{
    ifstream f(name);
    vector<float> v;

    while (f >> v)  /* PROVIDED BY MiLi */
    {
        cout << Separator(v, '\t');  /* PROVIDED BY MiLi */
        cout << endl;
        v.clear();
    }
}

int main()
{
    generate_file("stream-utils.test");
    load_file("stream-utils.test");

    return 0;
}

