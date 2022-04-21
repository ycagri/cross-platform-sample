#include <gtest/gtest.h>
#include <http/HttpClient.hpp>

using namespace client;

TEST(HttpClientTest, GetUserRequestTest){
    HttpClient* req = new HttpClient();
    std::string response = req->getRequest("api.github.com", "/users/ycagri", "443");
    EXPECT_TRUE(response.rfind("{\"login\":\"ycagri\"") == 0);
    delete req;
}

TEST(HttpClientTest, GetReposRequestTest){
    HttpClient* req = new HttpClient();
    std::string response = req->getRequest("api.github.com", "/users/ycagri/repos", "443");
    EXPECT_TRUE(response.rfind("[{\"id\":341657976,") == 0);
    delete req;
}