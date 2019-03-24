#include <limits.h>
#include "gtest/gtest.h"
#include <cstring>

#ifndef HTTPC_CORE_HTTPC_HTTP_REQUEST_
#include "core/httpc_http_request.h"
#endif

class HttpRequestTest : public ::testing::Test
{
protected:
    virtual void SetUp() {
        ;
    }
    virtual void TearDown() {
        ;
    }
    HttpRequest http_request;
};

TEST_F(HttpRequestTest, ToString_ShouldPass)
{
    char message[] = "CONNECT 192.168.3.22:22 HTTP/1.1\r\nHost: 192.168.3.22:22\r\n\r\n";
    http_request.SetMethod(httpc::http::HttpMethod::CONNECT);
    http_request.SetUrl("192.168.3.22:22");
    http_request.SetHttpVersison(httpc::http::kDefaultHttpVersion);
    http_request.PutHeader(httpc::http::header::kHost, "192.168.3.22:22");
    ASSERT_EQ(0, strcmp(http_request.ToString().c_str(), message));
}

TEST_F(HttpRequestTest, IsHttpRequest_ShouldPass)
{
    char message[] = "CONNECT 192.168.3.22:22 HTTP/1.1\r\nHost: 192.168.3.22:22\r\n\r\n";
    ASSERT_EQ(true, HttpRequest::IsHttpRequest(message, strlen(message)));
}

TEST_F(HttpRequestTest, AddPrefixToUrl_ShouldPass)
{
    char message[300] = "GET /signin HTTP/1.1\r\nHost: 192.168.3.22:22\r\n\r\n";
    char result[] = "GET http://192.168.3.22/signin HTTP/1.1\r\nHost: 192.168.3.22:22\r\n\r\n";
    HttpRequest::AddPrefixToUrl(message, strlen(message), std::string("http://192.168.3.22"));
    ASSERT_EQ(0, strcmp(message, result));
}

