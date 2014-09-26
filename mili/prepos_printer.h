/*
prepos_caller: A minimal library for wrapping object methods calls.
    This action can be used either as a pre-call or pos-call,
    to print a message (either to stdout, stderr, etc.).
    This file is part of the MiLi Minimalistic Library.

    Copyright (C) Daniel Gutson, FuDePAN 2008-2009
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
*/

#ifndef PREPOS_PRINTER_H
#define PREPOS_PRINTER_H

#include <string>
#include <iostream>

struct PrePosPrinter
{
    const std::string msg;
    std::ostream& os;

    PrePosPrinter(const std::string& msg, std::ostream& os = std::cout) : msg(msg), os(os) {}

    void operator()() const
    {
        os << msg << std::endl;
    }
};

#endif
