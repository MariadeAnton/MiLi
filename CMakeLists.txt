# This CMakeLists.txt file helps defining your block building and compiling
# Include the main biicode macros and functions
# To learn more about the CMake use with biicode, visit http://docs.biicode.com/c++/building.html
# Or check the examples below


include(${CMAKE_HOME_DIRECTORY}/biicode.cmake)
# Initializes block variables
INIT_BIICODE_BLOCK()

SET(TEST_FILES tests/arith-utils_tests.cpp
			tests/auto_array_test.cpp
			tests/binary-streams_test.cpp
			tests/bitwise-enums_test.cpp
			tests/compile_assert_test.cpp
			tests/container-utils_test.cpp
			tests/delete-container_test.cpp
			tests/factory_registry_test.cpp
			tests/factory_test.cpp
			tests/fast-list_test.cpp
			tests/generic_exceptions_test.cpp
			tests/invariants_tests.cpp
			tests/license_text_test.cpp
			tests/loop-unrolling_test.cpp
			tests/metaprogramming_utils_test.cpp
			tests/platform-detection_test.cpp
			tests/prepos-caller_test.cpp
			tests/promotion_disable_test.cpp
			tests/properties_tests.cpp
			tests/raii_test.cpp
			tests/random_gen_test.cpp
			tests/stream-utils_test.cpp
			tests/string-utils_test.cpp
			tests/template-info_test.cpp
			tests/type-mapper_test.cpp
			tests/variants_set_test.cpp)

FOREACH(TEST_FILE ${TEST_FILES})
	list(REMOVE_ITEM BII_LIB_SRC ${TEST_FILE})
	list(REMOVE_ITEM BII_tests_mili_test_suite_SRC ${TEST_FILE})
	list(APPEND BII_tests_mili_test_suite_MAIN ${TEST_FILE})
ENDFOREACH()
MESSAGE("${BII_tests_mili_test_suite_SRC}")
ADD_BIICODE_TARGETS()

FOREACH(BII_TARGET ${BII_BLOCK_TARGETS})
	TARGET_INCLUDE_DIRECTORIES(${BII_TARGET} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
ENDFOREACH()
