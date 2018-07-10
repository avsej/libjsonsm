/* -*- Mode: C; tab-width: 4; c-basic-offset: 4; indent-tabs-mode: nil -*- */
/*
 * Copyright 2018 Couchbase, Inc. All rights reserved.
 */

#include "internal.h"

ljsm_STATUS ljsm_matcher_new_slow(ljsm_MATCHER **out)
{
    (void)out;
    return LJSM_OK;
}

int ljsm_matcher_match(ljsm_MATCHER *matcher, const char *data, size_t data_len)
{
    (void)matcher;
    (void)data;
    (void)data_len;
    return 1;
}
