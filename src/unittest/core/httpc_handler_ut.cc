#include <limits.h>
#include "gtest/gtest.h"
#include "core/httpc_handler.h"

class HandlerTest : public ::testing::Test
{
protected:
    virtual void SetUp() {
        ;
    }
    virtual void TearDown() {
        ;
    }
    Handler handler;
};

TEST_F(HandlerTest, ConnectServer_ShouldPass)
{
    ASSERT_EQ(true, handler.ConnectProxyServer("115.156.135.252", "9001"));
}
