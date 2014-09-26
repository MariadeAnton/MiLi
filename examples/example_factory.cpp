/*
factory: A minimal library for a generic factory.
    This file is part of the MiLi Minimalistic Library.

    Copyright (C) Daniel Gutson and Marcelo Caro, FuDePAN 2009
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
#include "mili/mili.h"
using namespace mili;

using std::string;
using std::cout;

struct Shape
{
    virtual void print_shape() const = 0;
    virtual ~Shape() {}
};

class Circle : public Shape
{
    virtual void print_shape() const
    {
        cout << "a circle\n";
    }
};

class Rectangle : public Shape
{
    virtual void print_shape() const
    {
        cout << "a rectangle\n";
    }
};

int main()
{
    Factory<string, Shape> shapes_factory;

    shapes_factory.register_factory<Circle>("circle");
    shapes_factory.register_factory<Rectangle>("rectangle");
    Shape* s = shapes_factory.new_class("circle");

    s->print_shape();

    delete s;

    return 0;
}
