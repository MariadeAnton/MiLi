/*
type_mapper: A minimal library that implements a type mapper.
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

#ifndef TYPE_MAPPER_H
#define TYPE_MAPPER_H

NAMESPACE_BEGIN

#define declare_type_mapper(name)   \
    template <class From>           \
    struct name                     \
    {                               \
        typedef From type;          \
    }

#define add_mapping(mapper, from_type, to_type) \
    template<>                                  \
    struct mapper<from_type>                    \
    {                                           \
        typedef to_type type;                   \
    }

#define add_mapping_for_pointers(mapper, to_type)   \
    template <class From>                           \
    struct mapper<From*>                            \
    {                                               \
        typedef to_type type;                       \
    }

#define add_mapping_const_removal(mapper)           \
    template <class From>                           \
    struct mapper<const From>                       \
    {                                               \
        typedef typename mapper<From>::type type;   \
    }

#define add_mapping_ref_removal(mapper)             \
    template <class From>                           \
    struct mapper<From&>                            \
    {                                               \
        typedef typename mapper<From>::type type;   \
    }

#define map_type_(mapper, from_type) mapper<from_type>::type
#define map_type(mapper, from_type) typename map_type_(mapper, from_type)

// Some useful mappers:

// Removes const and &:
declare_type_mapper(BasicType);
add_mapping_const_removal(BasicType);
add_mapping_ref_removal(BasicType);

NAMESPACE_END

#endif
