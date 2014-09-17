# This CMakeLists.txt file helps defining your block building and compiling
# Include the main biicode macros and functions
# To learn more about the CMake use with biicode, visit http://docs.biicode.com/c++/building.html
# Or check the examples below


include(${CMAKE_HOME_DIRECTORY}/biicode.cmake)
# Initializes block variables
INIT_BIICODE_BLOCK()
# This function creates the following variables:
#     ${BII_BLOCK_NAME}       The name of the current block (e.g. "box2d")
#     ${BII_BLOCK_USER}       The user's name (e.g. "phil")
#     ${BII_BLOCK_PREFIX}     The directory where the block is located ("blocks" or "deps")

# Also it loads variables from the cmake/bii_user_block_vars.cmake
#     ${BII_CREATE_LIB}       TRUE if you want to create the library
#     ${BII_LIB_SRC}          File list to create the library
#     ${BII_LIB_TYPE}         STATIC(default) or SHARED
#     ${BII_LIB_DATA_FILES}   Data files that have to be copied to bin
#     ${BII_LIB_DEPS}         Dependencies to other libraries (user2_block2, user3_blockX)
#     ${BII_LIB_SYSTEM_DEPS}  System linking requirements as winmm, m, ws32, pthread...

# You can use or modify them here, for example, to add or remove files from targets based on OS
# Or use typical cmake configurations done BEFORE defining targets. Examples:
#     ADD_DEFINITIONS(-DFOO)
#     FIND_PACKAGE(OpenGL QUIET)
#     BII_FILTER_LIB_SRC(${BII_LIB_SRC})
#     You can add INCLUDE_DIRECTORIES here too


# Actually create targets: EXEcutables and libraries.
ADD_BIICODE_TARGETS()
TARGET_INCLUDE_DIRECTORIES(${BII_LIB_TARGET} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
# This function creates the following variables:
#     ${BII_BLOCK_TARGETS} List of targets defined in this block
#     ${BII_LIB_TARGET}  Target library name, usually in the form "user_block"
#     ${BII_exe_name_TARGET}: Executable target (e.g. ${BII_main_TARGET}. You can also use
#                            directly the name of the executable target (e.g. user_block_main)

# Example, if your library links with pthread:
#     TARGET_LINK_LIBRARIES(${BII_LIB_TARGET} pthread)
#        or directly use the library target name
#     TARGET_LINK_LIBRARIES(user_block pthread)
#     NOTE:  This can be also done adding pthread to ${BII_LIB_DEPS}
#            BEFORE calling ADD_BIICODE_TARGETS()
#
# Example: how to activate C++11. Uncomment one of this
#     target_compile_options(${BII_LIB_TARGET} PUBLIC "-std=c++11") # Win, or linux if not gcc problems
#     target_compile_options(${BII_LIB_TARGET} PUBLIC "-std=c++11"  "-stdlib=libc++") # MacOS
#     target_compile_options(${BII_LIB_TARGET} PUBLIC "-std=c++11" "-Wl,--no-as-needed") # Ubuntu if gcc problems
# with LLVM, you might need to link the target with "-lc++abi"
#
# If you want your code to be portable and activate properly C++11, you have to handle it:
# if(WIN32)
#     target_compile_options(${BII_LIB_TARGET} ... windows
# elseif(APPLE)
#     target_compile_options(${BII_LIB_TARGET} ... MacOS
# elseif(...)
#     ...
# endif()






##################################################################################################
#
#            EXAMPLES
#
##################################################################################################

#------------------ General variable --------------------#
#
# Mix your CMakeLists while you're using biicode or not. Use BIICODE variable:
#     IF(NOT BIICODE)
#        # without using biicode (your original code)
#     ELSE()
#        # using biicode
#     ENDIF()
#


#--------- Example of CMakeLists.txt that also works without biicode -------------------------#
# Imagine, you have a project named "graphic_project" and have two blocks, "phil/window_lib" and
# "phil/example", then you'll have this structure:
#
#         |-- graphic_project
#         |    +-- bii
#         |    +-- blocks
#         |    |    +-- phil
#         |    |    |    +-- window_lib
#         |    |    |    |    +-- CMakeLists.txt
#         |    |    |    |    +-- window_lib.h ---> #include <GL/glut.h>
#         |    |    |    |    +-- window_lib.cpp
#         |    |    |    +-- example
#         |    |    |    |    +-- CMakeLists.txt
#         |    |    |         +-- example.cpp ---> #include "phil/window_lib/window_lib.h"
#         |    +-- deps
#
# So, you are including phil/window_lib/window_lib.h file and linking with your system OpenGL
# library. Finally, you'd wish to link the library with OpenGL library and add your own
# definitions and compile your example.cpp with C++11 flag.
#
# The CMakeLists.txt files'd be like these:
#
#--------- phil/window_lib/CMakeLists.txt --------------#
#
#     IF(BIICODE)
#         INCLUDE(${CMAKE_HOME_DIRECTORY}/biicode.cmake)
#         INIT_BIICODE_BLOCK()
#     ELSE()
#        CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
#        PROJECT(Window_Lib)
#     ENDIF()
#
#     FIND_PACKAGE(OpenGL QUIET)
#
#     IF(BIICODE)
#        ADD_BIICODE_TARGETS()
#        SET(TARGET_NAME ${BII_LIB_TARGET})
#     ELSE()
#        SET(TARGET_NAME "window-lib")
#        ADD_LIBRARY(${TARGET_NAME} window_lib.h
#                                   window_lib.cpp)
#     ENDIF()
#
#     IF(OPENGL_FOUND)
#       TARGET_INCLUDE_DIRECTORIES(${TARGET_NAME} PUBLIC ${OPENGL_INCLUDE_DIRS})
#       TARGET_LINK_LIBRARIES(${TARGET_NAME} LINK_PUBLIC ${OPENGL_LIBRARIES})
#     ENDIF()
#
#--------- phil/example/CMakeLists.txt --------------#
#
#     IF(BIICODE)
#         INCLUDE(${CMAKE_HOME_DIRECTORY}/biicode.cmake)
#         INIT_BIICODE_BLOCK()
#     ELSE()
#        CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
#        PROJECT(Example)
#     ENDIF()
#
#     IF(NOT BIICODE)
#         ADD_DEFINITIONS(-DCMAKE_BUILD_TYPE=Release)
#         INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../../../blocks)
#         LINK_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../window_lib)
#     ENDIF()
#
#     IF(BIICODE)
#        ADD_BIICODE_TARGETS()
#        SET(TARGET_NAME ${BII_example_TARGET})
#     ELSE()
#        SET(TARGET_NAME "example")
#        ADD_EXECUTABLE(${TARGET_NAME} example.cpp)
#        TARGET_LINK_LIBRARIES(${TARGET_NAME} window-lib)
#     ENDIF()
#
#     # Only works in Win-Linux, MacOS requires diff settings for C++11
#     TARGET_COMPILE_OPTIONS(${TARGET_NAME} PRIVATE "-std=c++11")
#
#-----------------------------------------------------------------------------------------------#

