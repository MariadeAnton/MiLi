/*
delete_container: A minimal library for deleting the objects of a container of pointers.
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
#include "mili/mili.h"

using namespace mili;

struct AnObject
{
    int i;
    float f;
};

int main()
{
    std::vector<AnObject*> vec1;
    auto_vector_delete_container<std::vector<char*> > vec2;

    vec1.push_back(new AnObject);
    vec1.push_back(new AnObject);
    vec1.push_back(new AnObject);

    vec2.push_back(new char[10]);
    vec2.push_back(new char[10]);
    vec2.push_back(new char[10]);

    delete_container(vec1);
    // vector_delete_container(vec2) is called when exiting

    return 0;
}
