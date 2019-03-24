#include <limits.h>
#include "gtest/gtest.h"
#include "utils/args/httpc_args.h"

class ArgsTest : public ::testing::Test
{
protected:
    virtual void SetUp() {
        ;
    }
    virtual void TearDown() {
        ;
    }
    Args args;
    Options option;
};

TEST_F(ArgsTest, DoesnotHave_ShouldPass)
{
    ASSERT_EQ(false, args.HasKey(Options::PROXY_SERVER_IP));
}

TEST_F(ArgsTest, HasClient_ShouldPass)
{
    ASSERT_EQ(true, option.DoesHaveKey(Options::PROXY_SERVER_PORT));
}


