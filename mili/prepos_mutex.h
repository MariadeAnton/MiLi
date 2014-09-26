/*
prepos_caller: A minimal library for wrapping object methods calls.
    This file provides the pre-call and pos-call actions to lock/unlock
    a pthread mutex, respectivelly.
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

#ifndef PREPOS_MUTEX_H
#define PREPOS_MUTEX_H

#include <pthread.h>

struct PreMutex
{
    pthread_mutex_t* const mutex;

    PreMutex(pthread_mutex_t* mutex) : mutex(mutex) {}
    PreMutex(const PreMutex& other) : mutex(other.mutex) {}

    void operator()() const
    {
        pthread_mutex_lock(mutex);
    }
};

struct PosMutex
{
    pthread_mutex_t* const mutex;

    PosMutex(pthread_mutex_t* mutex) : mutex(mutex) {}
    PosMutex(const PosMutex& other) : mutex(other.mutex) {}

    void operator()() const
    {
        pthread_mutex_unlock(mutex);
    }
};

#endif
