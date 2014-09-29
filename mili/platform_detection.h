/*
platform_detection:
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
*/

#ifndef PLATFORM_DETECTION_H
#define PLATFORM_DETECTION_H

/* There is no need for namespace (NAMESPACE_BEGIN and NAMESPACE_END) */

/* OS detection
   See: http://sourceforge.net/apps/mediawiki/predef/index.php?title=Operating_Systems
*/
#define MILI_OS_LINUX   	1
#define MILI_OS_WINDOWS 	2
#define MILI_OS_MAC     	3
#define MILI_OS_UNKNOWN 	4

/* Windows */
#if   defined (WIN32)		\
   || defined (_WIN32)		\
   || defined (_WIN64)		\
   || defined (__WIN32__)	\
   || defined (__TOS_WIN__)	\
   || defined (__WINDOWS__)
#    define MILI_OS MILI_OS_WINDOWS

/* Linux */
#elif defined (__linux__)	\
   || defined (linux)		\
   || defined (__linux)
#    define MILI_OS MILI_OS_LINUX

/* MAC */
#elif defined (macintosh)	\
   || defined (Macintosh)	\
   || defined (__APPLE__)	\
   || defined (__MACH__)
#    define MILI_OS MILI_OS_MAC

/* Unknown OS */
#else
#    define MILI_OS MILI_OS_UNKNOWN

#endif /* end OS Detection */



/* Compiler detection
   See: http://sourceforge.net/apps/mediawiki/predef/index.php?title=Compilers
*/
#define MILI_COMPILER_VS		1
#define MILI_COMPILER_GCC		2
#define MILI_COMPILER_ICC		3
#define MILI_COMPILER_UNKNOWN	4

/* Microsoft Visual C++ */
#if   defined (_MSC_VER)
#    define MILI_COMPILER MILI_COMPILER_VS

/* GCC C/C++ */
#elif defined (__GNUC__)
#    define MILI_COMPILER MILI_COMPILER_GCC

/* Intel C/C++ */
/*#elif defined (__INTEL_COMPILER)	\
   || defined (__ICC)			\
   || defined (__ECC)			\
   || defined (__ICL)
#    define MILI_COMPILER MILI_COMPILER_ICC*/

/* Unknown compiler */
#else
#    define MILI_COMPILER MILI_COMPILER_UNKNOWN

#endif /* end Compiler detection */

#endif /* PLATFORM_DETECTION_H */

