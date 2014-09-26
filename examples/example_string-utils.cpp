/*
string_utils: A minimal library with string utilities.
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

#include <iostream>
#include <map>
#include "mili/mili.h"

using namespace mili;
using namespace std;

int main()
{
    lstring ls("helLO");

    ls[1] = 'E';
    cout << (ls[2] == 'L') << endl;             /* prints 1 (true) */

    cout << ls << endl;                         /* prints "hello" */
    cout << (ls == "HELLO") << endl;            /* prints 1 (true) */

    map<lstring, int> m;
    m["Hello"] = 3;
    m["Goodbye"] = 5;

    cout << m["hELLo"] << endl;                 /* prints 3 (matches with "Hello") */

    cout << begins_with(ls, "HE") << endl;      /* prints 1 (true) */
    cout << ends_with(ls, "Ello") << endl;      /* prints 1 (true) */

    cout << toupper("Hello World!") << endl;    /* prints "HELLO WORLD!" */

    cout << to_string(123.4) << endl;
    int n;
    cout << to_number("abc", n) << endl;        /* prints 0 (false), because "abc" is not valid */
    cout << to_number<float>("123.4") << endl;

    std::string str = "Why?";
    cout << ensure_found(str.find_first_of("h", 0)) << endl;    /* prints 1 */
    try
    {
        cout << ensure_found(str.find_first_of(" ", 0)) << endl;    /* throw StringNotFound  */
    }
    catch (const StringNotFound& f)
    {
        cout << "Do something" << endl;     /* prints Do something */
    }
    cout << ensure_found(str.find_first_of(" ", 0), str.size()) << endl;    /* prints str.size() */

    cout << substr("Hello World", Pos_(2), Count_(6)) << endl;     /* prints "llo Wo" */
    cout << substr("Hello World", Pos_(2), Pos_(6)) << endl;       /* prints "llo W" */

    return 0;
}

