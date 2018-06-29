#
# Copyright 2018 Couchbase, Inc. All rights reserved.
#

# Gets the libjsonsm version
# Sets:
#  LJSM_VERSION: Version string
#  LJSM_CHANGESET: SCM Revision number
#  LJSM_VERSION_HEX Numeric hex version
#  LJSM_VERSION_MAJOR
#  LJSM_VERSION_MINOR
#  LJSM_VERSION_PATCH

## Try git first ##
FIND_PROGRAM(GIT_EXECUTABLE NAMES git git.exe)
MACRO(RUNGIT outvar)
  EXECUTE_PROCESS(COMMAND git ${ARGN}
    OUTPUT_VARIABLE ${outvar}
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    OUTPUT_STRIP_TRAILING_WHITESPACE)
ENDMACRO()

if (GIT_EXECUTABLE)
  RUNGIT(LJSM_REVDESCRIBE describe --long)
  RUNGIT(LJSM_VERSION describe)
  STRING(REPLACE "-" "_" LJSM_VERSION "${LJSM_VERSION}")
  MESSAGE(STATUS "Sanitized VERSION=${LJSM_VERSION}")
  RUNGIT(LJSM_VERSION_CHANGESET rev-parse HEAD)

  EXECUTE_PROCESS(
    COMMAND echo ${LJSM_VERSION}
    COMMAND awk -F. "{printf \"0x%0.2d%0.2d%0.2d\", $1, $2, $3}"
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    OUTPUT_VARIABLE LJSM_VERSION_HEX)
ENDIF()

IF(LJSM_VERSION)
  # Have the version information
  CONFIGURE_FILE(${LJSM_GENINFODIR}/distinfo.cmake.in ${LJSM_GENINFODIR}/distinfo.cmake)
ENDIF()

# library version
IF(NOT LJSM_VERSION AND EXISTS ${LJSM_GENINFODIR}/distinfo.cmake)
  INCLUDE(${LJSM_GENINFODIR}/distinfo.cmake)
ENDIF()

IF (NOT LJSM_VERSION)
  SET(LJSM_NOGITVERSION ON)
  SET(LJSM_VERSION "0.0.0")
ENDIF()
IF (NOT LJSM_VERSION_CHANGESET)
  SET(LJSM_VERSION_CHANGESET "0xdeadbeef")
ENDIF()
IF (NOT LJSM_VERSION_HEX)
  SET(LJSM_VERSION_HEX 0x000000)
ENDIF()

# Now parse the version string
STRING(REPLACE "." ";" LJSM_VERSION_LIST "${LJSM_VERSION}")
LIST(GET LJSM_VERSION_LIST 0 LJSM_VERSION_MAJOR)
LIST(GET LJSM_VERSION_LIST 1 LJSM_VERSION_MINOR)
LIST(GET LJSM_VERSION_LIST 2 LJSM_VERSION_PATCH)

# Determine the SONAME for the library
SET(LJSM_SONAME_FULL "${LJSM_VERSION_MAJOR}.${LJSM_VERSION_MINOR}.${LJSM_VERSION_PATCH}")

MESSAGE(STATUS "libjsonsm ${LJSM_VERSION_MAJOR},${LJSM_VERSION_MINOR},${LJSM_VERSION_PATCH}")
MESSAGE(STATUS "Building libjsonsm ${LJSM_VERSION}/${LJSM_VERSION_CHANGESET}")