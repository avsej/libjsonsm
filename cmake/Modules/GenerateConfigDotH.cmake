#
# Copyright 2018 Couchbase, Inc. All rights reserved.
#

# Writes the 'config.h' header..
INCLUDE(CheckFunctionExists)
INCLUDE(CheckIncludeFiles)
INCLUDE(CheckSymbolExists)

IF(UNIX)
  CHECK_INCLUDE_FILES(stdint.h HAVE_STDINT_H)
  CHECK_INCLUDE_FILES(strings.h HAVE_STRINGS_H)
  CHECK_INCLUDE_FILES(sys/types.h HAVE_SYS_TYPES_H)
  CHECK_INCLUDE_FILES(unistd.h HAVE_UNISTD_H)
  CHECK_INCLUDE_FILES(inttypes.h HAVE_INTTYPES_H)
ENDIF()

CONFIGURE_FILE(
  ${PROJECT_SOURCE_DIR}/cmake/config-cmake.h.in
  ${LJSM_GENSRCDIR}/config.h)
