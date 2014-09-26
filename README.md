MiLi
====
MiLi: A set of minimal libraries composed only by 1 header file each.
    Copyright (C) 2009 - 2013  Daniel Gutson et al, FuDePAN

See the online documentation, new versions, and issue tracking at http://mili.googlecode.com

Notes
=====

** This is an adaptation of the original library http://mili.googlecode.com to enable its use with Biicode.

Github repository link: https://github.com/MariadeAnton/MiLi

Biicode repository link: http://www.biicode.com/hithwen/mili

Basic usage
============
    * copy the content of the include directory to where your headers files are.
    * just include "mili.h"
    * if you want to enclose the MiLi classes into the mili namespace, #define MILI_NAMESPACE
    * each library has it's own define to disable its inclusion:
    * platform_detection:   NO_PLATFORM_DETECTION
    * bitwise_enums:        NO_BITWISE_ENUMS
    * promotion_disable:    NO_PROMOTION_DISABLE
    * prepos_caller:        NO_PREPOS_CALLER
    * delete_container:     NO_DELETE_CONTAINER
    * factory:              NO_FACTORY
    * invariants:           NO_INVARIANTS
    * type_mapper:          NO_TYPE_MAPPER
    * properties:           NO_PROPERTIES
    * string_utils:         NO_STRING_UTILS
    * container_utils:      NO_CONTAINER_UTILS
    * stream_utils:         NO_STREAM_UTILS
    * arith_utils:          NO_ARITH_UTILS
    * binary_streams:       NO_BINSTREAMS
    * loop_unrolling:       NO_LOOP_UNROLLING
    * compile_assert:       NO_COMPILE_ASSERT
    * template_info:        NO_TEMPLATE_INFO
    * coroutines:           NO_COROUTINES
    * fast_list:            NO_FAST_LIST
    * ranker:               NO_RANKER
    * variants_set:         NO_VARIANTS_SET
    * random_gen:           NO_RANDOM_GEN
    * generic_exception:    NO_GENERIC_EXCEPTION
    * raii:                 NO_RAII
    * auto_array            NO_AUTO_ARRAY
    * metaprogramming_utils NO_METAPROGRAMMING_UTILS
    * license_text          NO_LICENSE_TEXT

You might want to copy the include files in an include directory.
If so, just run the 'install.sh' script:
    sudo ./install.sh
and then
    #include <mili/mili.h>


Send comments to info@fudepan.org.ar

Thanks!
    FuDePAN team.
