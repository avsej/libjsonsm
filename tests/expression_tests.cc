/* -*- Mode: C++; tab-width: 4; c-basic-offset: 4; indent-tabs-mode: nil -*- */
/*
 * Copyright 2018 Couchbase, Inc. All rights reserved.
 */

#include <libjsonsm/jsonsm.h>

#include <gtest/gtest.h>

class ExpressionTest : public ::testing::Test
{
};

TEST_F(ExpressionTest, testParsingJSONequals)
{
    ljsm_STATUS status;

    std::string json_src = R"(
        ["equals",
          ["field", "name"],
          ["value", "foo"]
        ]
    )";
    ljsm_EXPRESSION *json_expr = NULL;
    status = ljsm_expression_parse_json(&json_expr, json_src.c_str(), json_src.size());
    ASSERT_EQ(LJSM_OK, status);
}

TEST_F(ExpressionTest, DISABLED_testEquivalence)
{
    ljsm_STATUS status;

    std::string json_src = R"(
        ["or",
          ["equals",
            ["field", "name", "first"],
            ["value", "Neil"]
          ],
          ["and",
            ["lessthan",
              ["field", "age"],
              ["value", 50]
            ],
            ["equals",
              ["field", "isActive"],
              ["value", true]
            ]
          ]
        ]
    )";
    ljsm_EXPRESSION *json_expr = NULL;
    status = ljsm_expression_parse_json(&json_expr, json_src.c_str(), json_src.size());
    ASSERT_EQ(LJSM_OK, status);

    std::string str_src = R"(name.first == 'Neil' || (age < 50 && isActive == true))";
    ljsm_EXPRESSION *str_expr = NULL;
    status = ljsm_expression_parse_str(&str_expr, str_src.c_str(), str_src.size());
    ASSERT_EQ(LJSM_OK, status);
}
