/* -*- Mode: C; tab-width: 4; c-basic-offset: 4; indent-tabs-mode: nil -*- */
/*
 * Copyright 2018 Couchbase, Inc. All rights reserved.
 */

#ifndef LIBJSONSM_JSONSM_H
#define LIBJSONSM_JSONSM_H 1

#include <stddef.h>
#include <stdint.h>

#include <libjsonsm/configuration.h>
#include <libjsonsm/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Get the version of the library.
 *
 * @param version where to store the numeric representation of the
 *         version (or NULL if you don't care)
 *
 * @return the textual description of the version ('\0'
 *          terminated). Do <b>not</b> try to release this string.
 *
 */
LJSM_PUBLIC_API
const char *ljsm_version(uint32_t *version);

#ifdef __cplusplus
}
#    endif /* __cplusplus */

#endif /* LIBJSONSM_JSONSM_H */
