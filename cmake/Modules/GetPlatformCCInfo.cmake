#
# Copyright 2018 Couchbase, Inc. All rights reserved.
#

# Gets string/platform information about the specific compiler
# Defines:
#  LJSM_CC_STRING for the C compiler string (i.e. "msvc", "mingw")
#  LJSM_ARCH_STRING for the target architecture, e.g. "x86"

# Figure out how we're building!
IF(MSVC)
  IF(CMAKE_CL_64)
    SET(LJSM_ARCH_STRING "amd64")
  ELSE()
    SET(LJSM_ARCH_STRING "x86")
  ENDIF(CMAKE_CL_64)

  IF(MSVC80)
    SET(LJSM_CC_STRING "vs8")
  ELSEIF(MSVC90)
    SET(LJSM_CC_STRING "vc9")
  ELSEIF(MSVC_VERSION EQUAL 1600)
    SET(LJSM_CC_STRING "vc10")
  ELSEIF(MSVC_VERSION EQUAL 1700)
    SET(LJSM_CC_STRING "vc11")
  ELSEIF(MSVC_VERSION EQUAL 1800)
    SET(LJSM_CC_STRING "vc12")
  ELSEIF(MSVC_VERSION EQUAL 1900)
    SET(LJSM_CC_STRING "vc14")
  ENDIF()
ELSE()
  IF(UNIX)
    SET(LJSM_CC_STRING "gcc")
    EXECUTE_PROCESS(
      COMMAND
      uname -m
      COMMAND
      tr -d '\n'
      OUTPUT_VARIABLE
      LJSM_ARCH_STRING)
  ELSE()
    IF(CMAKE_SIZEOF_VOID_P EQUAL 8)
      SET(LJSM_ARCH_STRING "amd64")
    ELSE()
      SET(LJSM_ARCH_STRING "x86")
    ENDIF()
    SET(LJSM_CC_STRING "mingw")
  ENDIF()
ENDIF()
