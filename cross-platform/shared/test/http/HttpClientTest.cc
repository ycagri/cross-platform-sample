#include <gtest/gtest.h>
#include <http/HttpClient.hpp>

using namespace http_client;

TEST(HttpClientTest, GetRequestTest){
    HttpClient* req = new HttpClient();
    std::string response = req->getRequest("login.salesforce.com", "/", "443");
    EXPECT_NE(0, response.length());
    delete req;
}