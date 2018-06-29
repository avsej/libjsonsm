#
# Copyright 2018 Couchbase, Inc. All rights reserved.
#

INCLUDE(FindGTest)
FIND_PACKAGE(GTest REQUIRED)
INCLUDE_DIRECTORIES(${GTEST_INCLUDE_DIRS})

ADD_EXECUTABLE(slow-matcher-tests slow_matcher_tests.cc)
TARGET_LINK_LIBRARIES(slow-matcher-tests jsonsm ${GTEST_BOTH_LIBRARIES} ${LIBPROFILER})
SET_TARGET_PROPERTIES(slow-matcher-tests PROPERTIES COMPILE_FLAGS "${LJSM_CORE_CXXFLAGS}")

ADD_CUSTOM_TARGET(all-tests DEPENDS slow-matcher-tests)
ADD_TEST(NAME BUILD-TESTS COMMAND ${CMAKE_COMMAND} --build "${PROJECT_BINARY_DIR}" --target all-tests)

ADD_TEST(NAME slow-matcher COMMAND $<TARGET_FILE:slow-matcher-tests>)
