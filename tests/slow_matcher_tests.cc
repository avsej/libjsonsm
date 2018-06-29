/* -*- Mode: C; tab-width: 4; c-basic-offset: 4; indent-tabs-mode: nil -*- */
/*
 * Copyright 2018 Couchbase, Inc. All rights reserved.
 */

#include <libjsonsm/jsonsm.h>

#include <gtest/gtest.h>

class SlowMatcherTest : public ::testing::Test
{
};

TEST_F(SlowMatcherTest, testTruth)
{
    ASSERT_TRUE(true);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
