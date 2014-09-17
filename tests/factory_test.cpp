/*
    This file is part of the MiLi Minimalistic Library.

    Copyright (C) Hugo Arregui, FuDePAN 2011
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

    This is a test file.
*/

#include "google/gtest/gtest.h"
#include "google/gmock/gmock.h"
#include <string>
#include "mili/mili.h"

using namespace mili;
using namespace testing;
using std::string;

struct Shape
{
    virtual string shape_name() const = 0;
    virtual ~Shape() {}
};

class Circle : public Shape
{
    virtual string shape_name() const
    {
        return "circle";
    }
};

class Rectangle : public Shape
{
    virtual string shape_name() const
    {
        return "rectangle";
    }
};

TEST(FactoryTest, test)
{
    Factory<string, Shape> shapes_factory;
    shapes_factory.register_factory<Circle>("circle");

	/* When compiling for Windows the Rectangle template argument in
    the following line is considered to be the function
    __gdi_entry WINGDIAPI BOOL WINAPI Rectangle(__in HDC hdc, __in int left, __in int top, __in int right, __in int bottom);
    defined in WinGDI.h. So I must ad the class keyword to discriminate. */
    shapes_factory.register_factory<class Rectangle>("rectangle");
    
    Shape* s = shapes_factory.new_class("circle");

    ASSERT_EQ("circle", s->shape_name());
    delete s;
}
