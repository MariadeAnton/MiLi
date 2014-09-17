/*
promotion_disable.h: A minimalistic library to disable undesired
    type promotions in C++.
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

#include "mili/mili.h"

using namespace mili;

float f(Restrict<float> rf)
{
    return rf + 1.0f;
}

float g(Restrict<float, FloatingPoints> fp)
{
    return fp + 1.0f;
}

float h(Restrict<double, NotNarrowing> nn)
{
    return nn + 1.2;
}

int main()
{
    f(1.0f);
    // f(1); error
    g(1.0);
    h(2.0);

    return 0;
}
