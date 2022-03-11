#include <gtest/gtest.h>
#include <http/HttpClient.hpp>

using namespace http_client;

TEST(HttpClientTest, GetRequestTest){
    HttpClient* req = new HttpClient();
    std::string response = req->getRequest("api.github.com", "/users/ycagri", "443");
    EXPECT_NE(0, response.length());
    delete req;
}