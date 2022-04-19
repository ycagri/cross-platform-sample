#include <gtest/gtest.h>
#include <http/HttpClient.hpp>
#include "boost/assign.hpp"

using namespace client;

TEST(HttpClientTest, GetRequestTest){
    HttpClient* req = new HttpClient();
    std::string response = req->getRequest("api.github.com", "/users/ycagri", "443");
    std::cout << response << std::endl;
    EXPECT_NE(0, response.length());
    delete req;
}