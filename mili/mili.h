/*
MiLi: A set of minimal libraries composed only by 1 header file each.

    MiLi is free software: you can redistribute it and/or modify
    it under the terms of the Boost Software License.
    This file is part of the MiLi Minimalistic Library.

    Copyright (C) Daniel Gutson, FuDePAN 2009-2013.
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

    This is the main include file.
*/

#ifndef MILI_H
#define MILI_H

//deprecated: will desapear in next version
#ifdef NO_MILI_NAMESPACE
#   define NAMESPACE_BEGIN
#   define NAMESPACE_END
#else
#   define NAMESPACE_BEGIN namespace mili {
#   define NAMESPACE_END }
#endif

#ifndef NO_PLATFORM_DETECTION
#    include "platform_detection.h"
#endif

#ifndef NO_BITWISE_ENUMS
#   include "bitwise_enums.h"
#endif

#ifndef NO_PREPOS_CALLER
#   include "prepos_caller.h"
#endif

#ifndef NO_DELETE_CONTAINER
#   include "delete_container.h"
#endif

#ifndef NO_PROMOTION_DISABLE
#   include "promotion_disable.h"
#endif

#ifndef NO_FACTORY
#   include "factory.h"
#endif

#ifndef NO_INVARIANTS
#   include "invariants.h"
#endif

#ifndef NO_TYPE_MAPPER
#   include "type_mapper.h"
#endif

#ifndef NO_PROPERTIES
#   include "properties.h"
#endif

#ifndef NO_STRING_UTILS
#   include "string_utils.h"
#endif

#ifndef NO_RANKER
#   include "ranker.h"
#endif

#ifndef NO_VARIANTS_SET
#   include "variants_set.h"
#endif

#ifndef NO_CONTAINER_UTILS
#   include "container_utils.h"
#endif

#ifndef NO_STREAM_UTILS
#   include "stream_utils.h"
#endif

#ifndef NO_ARITH_UTILS
#   include "arith_utils.h"
#endif

#ifndef NO_RANDOM_GEN
#   include "random_gen.h"
#endif

#ifndef NO_LOOP_UNROLLING
#   include "loop_unrolling.h"
#endif

#ifndef NO_COMPILE_ASSERT
#   include "compile_assert.h"
#endif

#ifndef NO_TEMPLATE_INFO
#   include "template_info.h"
#endif

#ifndef NO_BINSTREAMS
#   include "binary_streams.h"
#endif

#ifndef NO_COROUTINES
#   include "coroutines.h"
#endif

#ifndef NO_FAST_LIST
#   include "fast_list.h"
#endif

#ifndef NO_GENERIC_EXCEPTION
#   include "generic_exception.h"
#endif

#ifndef NO_RAII
#   include "raii.h"
#endif

#ifndef NO_AUTO_ARRAY
#   include "auto_array.h"
#endif

#ifndef NO_METAPROGRAMMING_UTILS
#   include "metaprogramming_utils.h"
#endif

#ifndef NO_LICENSE_TEXT
#   include "license_text.h"
#endif

#ifndef NO_NON_COPYABLE
#   include "non_copyable.h"
#endif

#undef NAMESPACE_BEGIN
#undef NAMESPACE_END

#endif
