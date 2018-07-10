/* -*- Mode: C; tab-width: 4; c-basic-offset: 4; indent-tabs-mode: nil -*- */
/*
 * Copyright 2018 Couchbase, Inc. All rights reserved.
 */

#include "internal.h"

#include <string.h>

#include "jsonsl/jsonsl.h"

#define MAX_DEPTH 32

static int parse_error_callback(jsonsl_t jp, jsonsl_error_t error, struct jsonsl_state_st *state, jsonsl_char_t *at)
{
    (void)jp;
    (void)error;
    (void)state;
    (void)at;
    return 0;
}

typedef struct parser_context {
    int level;
    ljsm_EXPRESSION *stack[1];
} parser_context;

static void die(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");
    va_end(args);
    abort();
}

static void parse_push_callback(jsonsl_t jp, jsonsl_action_t action, struct jsonsl_state_st *state,
                                const jsonsl_char_t *at)
{
    parser_context *ctx = jp->data;

    switch (state->type) {
        case JSONSL_T_LIST:
            ctx->level++;
            ctx->stack[ctx->level] = calloc(1, sizeof(ljsm_EXPRESSION));
            if (ctx->level == 0) {
                fprintf(stderr, "Root(");
            }
            break;
    }
    (void)jp;
    (void)action;
    (void)state;
    (void)at;
}

static void parse_pop_callback(jsonsl_t jp, jsonsl_action_t action, struct jsonsl_state_st *state,
                               const jsonsl_char_t *at)
{
    parser_context *ctx = jp->data;
    ljsm_EXPRESSION *cur = ctx->stack[ctx->level];

    if (cur->type == LJSM_EXPRESSION_UNKNOWN) {
        if (state->type == JSONSL_T_STRING) {
            char *buf;
            size_t len;
            buf = (char *)jp->base + state->pos_begin;
            len = jp->pos - state->pos_begin + 1;
            if (memcmp(buf, "\"and\"", len) == 0) {
                cur->type = LJSM_EXPRESSION_AND;
            } else if (memcmp(buf, "\"or\"", len) == 0) {
                cur->type = LJSM_EXPRESSION_OR;
            } else if (memcmp(buf, "\"equals\"", len) == 0) {
                cur->type = LJSM_EXPRESSION_EQUALS;
            } else if (memcmp(buf, "\"field\"", len) == 0) {
                cur->type = LJSM_EXPRESSION_FIELD;
            } else if (memcmp(buf, "\"greater\"", len) == 0) {
                cur->type = LJSM_EXPRESSION_GREATERTHAN;
            } else if (memcmp(buf, "\"greaterequal\"", len) == 0) {
                cur->type = LJSM_EXPRESSION_GREATEREQUAL;
            } else if (memcmp(buf, "\"lessthan\"", len) == 0) {
                cur->type = LJSM_EXPRESSION_LESSTHAN;
            } else if (memcmp(buf, "\"lessequal\"", len) == 0) {
                cur->type = LJSM_EXPRESSION_LESSEQUAL;
            } else if (memcmp(buf, "\"value\"", len) == 0) {
                cur->type = LJSM_EXPRESSION_VALUE;
            } else if (memcmp(buf, "\"anyin\"", len) == 0) {
                cur->type = LJSM_EXPRESSION_ANYIN;
            } else {
                die("FIXME: unknown operator: \"%.*s\"", (int)len, buf);
            }
            fprintf(stderr, "<%.*s>", (int)len, buf);
        } else {
            die("FIXME: unexpected JSON node type '%c' while expression node is not defined", state->type);
        }
    } else {
        switch (state->type) {
            case JSONSL_T_LIST:
                ctx->level--;
                fprintf(stderr, " sz=%d)", (int)state->nelem);
                break;
            case JSONSL_T_STRING:
                switch (cur->type) {
                case LJSM_EXPRESSION_VALUE:
                    cur->v.value.data = (char *)jp->base + state->pos_begin;
                    cur->v.value.data_len = jp->pos - state->pos_begin + 1;
                    fprintf(stderr, "<%.*s>(n=%d)", (int)cur->v.value.data_len, cur->v.value.data);
                }
                break;
        }
    }
    (void)jp;
    (void)action;
    (void)state;
    (void)at;
}

ljsm_STATUS ljsm_expression_parse_json(ljsm_EXPRESSION **out, const char *expr, size_t expr_len)
{
    parser_context *ctx;
    jsonsl_t jp;
    int nlevels = MAX_DEPTH;

    ctx = calloc(1, sizeof(parser_context) + ((nlevels - 1) * sizeof(struct ljsm_EXPRESSION *)));
    ctx->level = -1; /* stack is empty */

    jp = jsonsl_new(nlevels);
    jp->action_callback_PUSH = parse_push_callback;
    jp->action_callback_POP = parse_pop_callback;
    jp->error_callback = parse_error_callback;
    jp->data = ctx;
    jsonsl_enable_all_callbacks(jp);
    fprintf(stderr, "\n\n\n");
    jsonsl_feed(jp, expr, expr_len);
    fprintf(stderr, "\n\n\n");
    jsonsl_destroy(jp);
    *out = ctx->stack[0];
    free(ctx);

    (void)out;
    (void)expr;
    (void)expr_len;
    return LJSM_OK;
}
