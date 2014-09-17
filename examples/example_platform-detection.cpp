/*
platform-detection:
    This file is part of the MiLi Minimalistic Library.

    Copyright (C) Daniel Muñoz, FuDePAN 2012
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

#include <iostream>
#include "mili/mili.h"

/* Operating System example */
#if defined (MILI_OS)
#    if   MILI_OS == MILI_OS_LINUX
#        define OS_STRING "Linux"
#    elif MILI_OS == MILI_OS_WINDOWS
#        define OS_STRING "Windows"
#    elif MILI_OS == MILI_OS_MAC
#        define OS_STRING "Mac"
#    elif MILI_OS == MILI_OS_UNKNOWN
#        define OS_STRING "Unknown"
#    else
#        define OS_STRING "Error (MILI_OS has an invalid value)"
#    endif

#else /* !defined (MILI_OS) */
#    define OS_STRING "Error (MILI_OS is not defined)"

#endif /* defined (MILI_OS) */

/* Compiler example */
#if defined (MILI_COMPILER)
#    if   MILI_COMPILER == MILI_COMPILER_VS
#        define COMPILER_STRING "Visual C++"
#    elif MILI_COMPILER == MILI_COMPILER_GCC
#        define COMPILER_STRING "GNU-GCC"
#    elif MILI_COMPILER == MILI_COMPILER_ICC
#        define COMPILER_STRING "Intel C/C++"
#    elif MILI_COMPILER == MILI_COMPILER_UNKNOWN
#        define COMPILER_STRING "Unknown"
#    else
#        define COMPILER_STRING "Error (MILI_COMPILER has an invalid value)"
#    endif

#else /* !defined (MILI_COMPILER) */
#    define COMPILER_STRING "Error (MILI_COMPILER is not defined)"

#endif /* defined (MILI_COMPILER) */

int main()
{
    int result = EXIT_SUCCESS;

    std::cout<<"switch/case output: ";

    /* Another Operating System example */
    switch(MILI_OS)
    {
        case MILI_OS_LINUX:
            std::cout<<"Linux"; 
            break;
        case MILI_OS_WINDOWS:
            std::cout<<"Windows";
            break;
        case MILI_OS_MAC:
            std::cout<<"Mac";
            break;
        case MILI_OS_UNKNOWN:
            std::cout<<"Unknown";
            break;
        default:
            std::cout<<"Error (MILI_OS has an invalid value)";
            result = EXIT_FAILURE;
    }

    std::cout<<" OS / ";

    /* Another Compiler example */
    switch(MILI_COMPILER)
    {
        case MILI_COMPILER_VS:
            std::cout<<"Visual C++"; 
            break;
        case MILI_COMPILER_GCC:
            std::cout<<"GNU-GCC";
            break;
        case MILI_COMPILER_ICC:
            std::cout<<"Intel C/C++";
            break;
        case MILI_COMPILER_UNKNOWN:
            std::cout<<"Unknown";
            break;
        default:
            std::cout<<"Error (MILI_COMPILER has an invalid value)";
            result = EXIT_FAILURE;
    }

    std::cout<<" Compiler"<<std::endl;
    
    std::cout<<"Conditional compilation output: " OS_STRING " OS / " COMPILER_STRING " Compiler"<<std::endl;

    return result;
}

