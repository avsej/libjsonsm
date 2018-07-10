/* -*- Mode: C++; tab-width: 4; c-basic-offset: 4; indent-tabs-mode: nil -*- */
/*
 * Copyright 2018 Couchbase, Inc. All rights reserved.
 */

#include <libjsonsm/jsonsm.h>

#include <gtest/gtest.h>

class SlowMatcherTest : public ::testing::Test
{
};

TEST_F(SlowMatcherTest, DISABLED_testMatcher)
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

    ljsm_EXPRESSION *expr = NULL;
    status = ljsm_expression_parse_json(&expr, json_src.c_str(), json_src.size());
    ASSERT_EQ(LJSM_OK, status);

    ljsm_MATCHER *matcher;
    status = ljsm_matcher_new_slow(&matcher);
    ASSERT_EQ(LJSM_OK, status);

    std::string data_str = R"(
        {"age":32,
         "isActive":true,
         "name":
             {"first":"Neil"}
        }
    )";
    bool result = ljsm_matcher_match(matcher, data_str.c_str(), data_str.size());
    ASSERT_TRUE(result);
}
