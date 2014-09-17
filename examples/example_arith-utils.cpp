/*
arith_utils: A minimal library with arithmetic utilities.
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
#include "mili/mili.h"

using namespace mili;

int main()
{
    if (bchain(1) < 2 < 3)
        std::cout << "1 < 2 < 3 -> TRUE" << std::endl;

    int x(10);
    if ((5 >= bchain(4) < 10) == x)
        std::cout << "5 >= 4 < 10 == x -> TRUE" << std::endl;

    float r = power<2>(2);
    std::cout << "2^2 == " << r << std::endl;
    if (r != 4)
    {
        return EXIT_FAILURE;
    }

    r = power < -2 > (2);
    std::cout << "2^(-2) == " << r << std::endl;
    if (r != .25)
    {
        return EXIT_FAILURE;
    }

    r = cubic_root(27);
    std::cout << "27^(1/3) == " << r << std::endl;
    if (r != 3)
    {
        return EXIT_FAILURE;
    }

    if (in_range(3.141692f, 10.0f, 11.0f))
        return EXIT_FAILURE;
    else
        return EXIT_SUCCESS;
}

