/*
example_coroutines: An example that uses coroutines.
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

class CoRo1 : public Coroutine
{
    int x;
    int y;
    int z;
public:
    int operator()()
    {
        BEGIN_COROUTINE
        {
            for (x = 0; x < 10; ++x)
            {
                for (y = 0; y < 10; ++y)
                {
                    for (z = 0; z < 10; ++z)
                        mili_yield(x + y + z);
                }
                mili_yield(-x);
            }
        }
        END_COROUTINE(-1000);
    }
};

int main()
{
    CoRo1 cr1;
    int ret;
    do
    {
        ret = cr1();
        cout << ret << endl;
    }
    while (ret != -1000);
    return ret;
}

