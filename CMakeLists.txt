# This CMakeLists.txt file helps defining your block building and compiling
# Include the main biicode macros and functions
# To learn more about the CMake use with biicode, visit http://docs.biicode.com/c++/building.html
# Or check the examples below


include(${CMAKE_HOME_DIRECTORY}/biicode.cmake)
# Initializes block variables
INIT_BIICODE_BLOCK()
ADD_BIICODE_TARGETS()
TARGET_INCLUDE_DIRECTORIES(${BII_LIB_TARGET} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
