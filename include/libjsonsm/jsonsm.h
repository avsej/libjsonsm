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

typedef enum {
    /** Success */
    LJSM_OK = 0,
    /** Invalid arguments */
    LDCP_BADARG = 1
} ljsm_STATUS;

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

typedef enum {
    LJSM_EXPRESSION_UNKNOWN = 0,
    LJSM_EXPRESSION_VALUE,
    LJSM_EXPRESSION_FIELD,
    LJSM_EXPRESSION_OR,
    LJSM_EXPRESSION_AND,
    LJSM_EXPRESSION_ANYIN,
    LJSM_EXPRESSION_EQUALS,
    LJSM_EXPRESSION_LESSTHAN,
    LJSM_EXPRESSION_LESSEQUAL,
    LJSM_EXPRESSION_GREATERTHAN,
    LJSM_EXPRESSION_GREATEREQUAL,
    LJSM_EXPRESSION__MAX
} ljsm_EXPRESSION_TYPE;

typedef struct ljsm_EXPRESSION_VALUE {
    const char *data;
    size_t data_len;
} ljsm_EXPRESSION_VALUE;

typedef struct ljsm_EXPRESSION {
    ljsm_EXPRESSION_TYPE type;
    union {
        ljsm_EXPRESSION_VALUE value;
    } v;
} ljsm_EXPRESSION;

LJSM_PUBLIC_API ljsm_STATUS ljsm_expression_parse_json(ljsm_EXPRESSION **out, const char *expr, size_t expr_len);
LJSM_PUBLIC_API ljsm_STATUS ljsm_expression_parse_str(ljsm_EXPRESSION **out, const char *expr, size_t expr_len);

typedef enum {
    LJSM_MATCHER_FAST = 0, /** default matcher */
    LJSM_MATCHER_SLOW = 1, /** non-optimizing matcher, for testing purposes */
    LJSM_MATCHER__MAX
} ljsm_MATCHER_TYPE;

typedef struct ljsm_MATCHER {
    ljsm_MATCHER_TYPE type;
} ljsm_MATCHER;

LJSM_PUBLIC_API ljsm_STATUS ljsm_matcher_new_slow(ljsm_MATCHER **out);

LJSM_PUBLIC_API int ljsm_matcher_match(ljsm_MATCHER *matcher, const char *data, size_t data_len);

#ifdef __cplusplus
}
#    endif /* __cplusplus */

#endif /* LIBJSONSM_JSONSM_H */
