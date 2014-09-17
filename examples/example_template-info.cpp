/*
template_info: A minimal library to obtain type information of a template
    parameter.
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
#include <vector>
#include <set>
#include "mili/mili.h"

using namespace mili;

struct S {};

int main()
{
    std::cout << bool(template_info<S>::is_native) << std::endl;
    std::cout << bool(template_info<char>::is_native) << std::endl;
    std::cout << bool(template_info<int>::is_same_size<long int>::value) << std::endl;
    std::cout << bool(template_info<std::vector<int> >::is_container) << std::endl;
    std::cout << bool(template_info<std::set<int> >::is_container) << std::endl;
    return 0;
}
