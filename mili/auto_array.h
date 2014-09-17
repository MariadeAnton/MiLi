/*
auto_array: an auto_ptr counterpart for array objects
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
*/

#ifndef AUTO_ARRAY_H
#define AUTO_ARRAY_H

NAMESPACE_BEGIN

template <class T>
class auto_array
{
public:
    auto_array(T* _array) :
        array(_array)
    {}

    ~auto_array()
    {
        release();
    }

    T* get() const
    {
        return array;
    }

    T& operator[](size_t n)
    {
        return array[n];
    }

    const T& operator[](size_t n) const
    {
        return array[n];
    }

    auto_array<T>& operator=(const auto_array<T>& b)
    {
        reset(b.array);
        return *this;
    }

    void reset(T* _array)
    {
        release();
        array = _array;
    }

    T* release()
    {
        T* const tmp = array;
        delete[] array;
        array = NULL;
        return tmp;
    }
private:
    T* array;
};


NAMESPACE_END

#endif
