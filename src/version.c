/* -*- Mode: C; tab-width: 4; c-basic-offset: 4; indent-tabs-mode: nil -*- */
/*
 * Copyright 2018 Couchbase, Inc. All rights reserved.
 */

#include "internal.h"

LJSM_PUBLIC_API
const char *ljsm_version(uint32_t *version)
{
    if (version != NULL) {
        *version = (uint32_t)LJSM_VERSION;
    }

    return LJSM_VERSION_STRING;
}
