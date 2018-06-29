#
# Copyright 2018 Couchbase, Inc. All rights reserved.
#

ADD_EXECUTABLE(jsm jsm.c)
TARGET_LINK_LIBRARIES(jsm jsonsm ${LIBPROFILER})
INSTALL(TARGETS jsm
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
