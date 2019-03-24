#include <limits.h>
#include "gtest/gtest.h"
#include "core/httpc_http_response.h"
#include <cstring>

#ifndef HTTPC_UTILS_HTTPC_STRINGUTIL_
#include "utils/httpc_stringutil.h"
#endif

#ifndef HTTPC_CORE_HTTPC_HTTP_
#include "core/httpc_http.h"
#endif

class HttpResponseTest : public ::testing::Test
{
protected:
    virtual void SetUp() {
        ;
    }
    virtual void TearDown() {
        ;
    }
    HttpResponse http_response;
};

TEST_F(HttpResponseTest, GetStatusCode_ShouldPass)
{
    char response[] = "HTTP/1.0 200 Connection Established\r\nbbb\r\n";
    http_response.SetResponseAndResponseLen(response, strlen(response));
    ASSERT_EQ(200, atoi(http_response.GetStatusCode().c_str()));
}

TEST_F(HttpResponseTest, Replace_ShouldPass)
{
    char response[] = "HTTP/1.0 200 Connection 192.168.3.22\r\nbbb\r\n";
    char result[] =   "HTTP/1.0 200 Connection eastlake.git\r\nbbb\r\n";
    HttpResponse::Replace(response, strlen(response), httpc::http::kDefaultReplaceSrc, \
                            httpc::http::kDefaultReplaceDes);    
    ASSERT_EQ(0, strcmp(response, result));
}

