/*
factory_registry: A simple way to registry derived classes without .h file
    This file is part of the MiLi Minimalistic Library.

    Copyright (C) Leandro Ramos, FuDePAN 2012
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

#include<iostream>
#include<string>
#include"mili/mili.h"

/* This example was written in one file for simplicity but it could write in separete files */

//! Speaker interface .h

struct Speaker
{
    virtual void saySomething() = 0;
};

//! End of speaker interface file

//! Hello.cpp file


class Hello: public Speaker
{
    virtual void saySomething();
};

void Hello::saySomething()
{
    std::cout << "Hello" << std::endl;
}

REGISTER_FACTORIZABLE_CLASS(Speaker, Hello, std::string, "Hello");

//! End of Hello.cpp

//! Goodbye.cpp


class Goodbye: public Speaker
{
    virtual void saySomething();
};

void Goodbye::saySomething()
{
    std::cout << "Goodbye" << std::endl;
}

REGISTER_FACTORIZABLE_CLASS(Speaker, Goodbye, std::string, "Goodbye");

//! End of Goodbye.cpp

//! Main file


int main()
{
    std::string className;
    Speaker* speaker;

    std::cout << "Which speaker would you like?" << std::endl;
    std::cin >> className;
    speaker = mili::FactoryRegistry<Speaker, std::string>::new_class(className);
    if (speaker == NULL)
    {
        std::cout << "Speaker " << className << " doesn't exist" << std::endl;
    }
    else
    {
        speaker->saySomething();
        delete speaker;
    }
    return 0;
}
