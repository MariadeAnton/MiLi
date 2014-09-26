/*
raii.h: A minimal library to provide the RAII feature
    This file is part of the MiLi Minimalistic Library.

    Copyright (C) Lucas Besso & Raul Striglio, FuDePAN 2011
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

#ifndef RAII_H
#define RAII_H

NAMESPACE_BEGIN

template <class T, void (T::*M)(void)>
class RAII
{

public:
    RAII(T& inst) : _var(inst) {}
    ~RAII()
    {
        (_var.*M)();
    }

private:
    T& _var;
};

NAMESPACE_END

#endif
