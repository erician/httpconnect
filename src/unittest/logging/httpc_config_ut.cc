#include <limits.h>
#include "gtest/gtest.h"
#include "logging/httpc_config.h"
#include "logging/httpc_const.h"

class ConfigTest : public ::testing::Test
{
protected:
    virtual void SetUp() {
        config.Init("logging/httpc_logging.ini");
    }
    virtual void TearDown() {
        ;
    }
    Config config;
};

TEST_F(ConfigTest, IsHave_ShouldPass)
{
    ASSERT_EQ(true, config.IsHave(httpc::Config::kLogFilePath));
}

TEST_F(ConfigTest, GetValue_ShouldPass)
{
    ASSERT_EQ("../logs/log.txt", config.GetValue(httpc::Config::kLogFilePath));
}


