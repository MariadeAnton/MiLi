/*
loop_unrolling: A minimal library for TMP loop unrolling.
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
*/

#ifndef LOOP_UNROLLING_H
#define LOOP_UNROLLING_H

NAMESPACE_BEGIN

template <bool Unroll, unsigned int N, class Operation>
struct _FOR
{
    static void iterate(Operation& op)
    {
        op();
        _FOR < Unroll, N - 1, Operation >::iterate(op);
    }
};

template <bool Unroll, class Operation>
struct _FOR<Unroll, 0, Operation>
{
    static void iterate(Operation&)
    {}
};

template <unsigned int N, class Operation>
struct _FOR<false, N, Operation>
{
    static void iterate(Operation& op)
    {
        for (unsigned int i = 0; i < N; ++i)
            op();
    }
};

struct UnrollAlwaysClause
{
    template <unsigned int N>
    struct clause
    {
        enum { unroll = true };
    };
};

template <unsigned int MAX>
struct UnrollUpToClause
{
    template <unsigned int N>
    struct clause
    {
        enum { unroll = (N <= MAX) };
    };
};

template < unsigned int N, class Operation, class UnrollClause = UnrollAlwaysClause >
struct FOR
{
    static void iterate(Operation& op)
    {
        typedef typename UnrollClause::template clause<N> clause;
        _FOR<clause::unroll, N, Operation>::iterate(op);
    }
};

NAMESPACE_END

#endif
