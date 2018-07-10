/* -*- Mode: C; tab-width: 4; c-basic-offset: 4; indent-tabs-mode: nil -*- */
/*
 * Copyright 2018 Couchbase, Inc. All rights reserved.
 */

#include "internal.h"

#include <ctype.h>

typedef enum {
    TOK_INVALID,
    TOK_FIELD,
    TOK_VALUE,
    TOK_PAREN,     /* "("     */
    TOK_END_PAREN, /* ")"     */
    TOK_TRUE,      /* "true"  */
    TOK_FALSE,     /* "false" */
    TOK_AND,       /* "&&"    */
    TOK_OR,        /* "||"    */
    TOK_EQ,        /* "=="    */
    TOK_NEQ,       /* "!="    */
    TOK_GT,        /* ">"     */
    TOK_GTE,       /* ">="    */
    TOK_LT,        /* "<"     */
    TOK_LTE,       /* "<="    */
    TOK__MAX
} ljsm_token_type;

typedef struct ljsm_token {
    struct ljsm_token *next;
    ljsm_token_type type;
    size_t pos;
    size_t len;
} ljsm_token;

typedef struct ljsm_parser_context {
    const char *expr;
    size_t expr_len;
    ljsm_token *tokens;
    size_t tokens_len;
    ljsm_token *cur_token;
} ljsm_parser_context;

static void ljsm_scan_ops(ljsm_parser_context *ctx, ljsm_token *tok, size_t pos)
{
    switch (ctx->expr[pos]) {
        case '(':
            tok->type = TOK_PAREN;
            tok->len = 1;
            break;
        case ')':
            tok->type = TOK_END_PAREN;
            tok->len = 1;
            break;
        case '>':
            tok->type = TOK_GT;
            tok->len = 1;
            if (pos + 1 < ctx->expr_len && ctx->expr[pos + 1] == '=') {
                tok->type = TOK_GTE;
                tok->len = 2;
            }
            break;
        case '<':
            tok->type = TOK_LT;
            tok->len = 1;
            if (pos + 1 < ctx->expr_len && ctx->expr[pos + 1] == '=') {
                tok->type = TOK_LTE;
                tok->len = 2;
            }
            break;
        case '|':
            if (pos + 1 < ctx->expr_len && ctx->expr[pos + 1] == '|') {
                tok->type = TOK_OR;
                tok->len = 2;
            }
            break;
        case '&':
            if (pos + 1 < ctx->expr_len && ctx->expr[pos + 1] == '&') {
                tok->type = TOK_AND;
                tok->len = 2;
            }
            break;
        case '=':
            if (pos + 1 < ctx->expr_len && ctx->expr[pos + 1] == '=') {
                tok->type = TOK_EQ;
                tok->len = 2;
            }
            break;
        case '!':
            if (pos + 1 < ctx->expr_len && ctx->expr[pos + 1] == '=') {
                tok->type = TOK_NEQ;
                tok->len = 2;
            }
            break;
    }
}

static void ljsm_tokenize(ljsm_parser_context *ctx)
{
    size_t pos = 0;
    ljsm_token *tok = NULL;

    ctx->tokens = NULL;
    ctx->tokens_len = 0;
    if (ctx->expr == NULL || ctx->expr_len == 0) {
        return;
    }

    while (pos < ctx->expr_len) {
        ljsm_token *t;
        while (pos < ctx->expr_len && isspace(ctx->expr[pos])) {
            pos++;
        }
        if (pos >= ctx->expr_len) {
            break;
        }
        t = malloc(sizeof(ljsm_token));
        if (tok) {
            tok->next = t;
        } else {
            ctx->tokens = t;
        }
        tok = t;
        tok->pos = pos;
        tok->type = TOK_INVALID;
        ljsm_scan_ops(ctx, tok, pos);
        if (tok->type) {
            pos += tok->len;
            while (pos < ctx->expr_len && isspace(ctx->expr[pos])) {
                pos++;
            }
            ctx->tokens_len++;
            continue;
        }
        while (pos < ctx->expr_len && !isspace(ctx->expr[pos])) {
            pos++;
        }
        tok->len = pos - tok->pos;
        tok->next = NULL;
        ctx->tokens_len++;
        pos++;
    }
    /* there might be no whitespace after last token */
    if (tok && tok->pos < ctx->expr_len) {
        tok->len = ctx->expr_len - tok->pos;
    }
}

static int ljsm_advance_token(ljsm_parser_context *ctx)
{
    if (ctx->cur_token) {
        ctx->cur_token = ctx->cur_token->next;
        if (ctx->cur_token) {
            return 1;
        }
    } else {
        ctx->cur_token = ctx->tokens;
        if (ctx->cur_token) {
            return 1;
        }
    }
    return 0;
}

static void ljsm_parse(ljsm_parser_context *ctx)
{
    ctx->cur_token = NULL;
    if (ctx->tokens == NULL || ctx->tokens_len == 0) {
        return;
    }
    while (ljsm_advance_token(ctx)) {
        /* ljsm_token *tok = ctx->cur_token; */
        /* fprintf(stderr, "<%.*s>\n", (int)tok->len, ctx->expr + tok->pos); */
    }
}

ljsm_STATUS ljsm_expression_parse_str(ljsm_EXPRESSION **out, const char *expr, size_t expr_len)
{
    ljsm_parser_context ctx;

    ctx.expr = expr;
    ctx.expr_len = expr_len;
    ljsm_tokenize(&ctx);
    ljsm_parse(&ctx);

    (void)out;
    return LJSM_OK;
}
