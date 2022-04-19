#include <gtest/gtest.h>
#include <http/HttpClient.hpp>
#include "boost/assign.hpp"

using namespace client;

TEST(HttpClientTest, GetRequestTest){
    HttpClient* req = new HttpClient();
    std::map<std::string, std::string> headers =  boost::assign::map_list_of ("user-agent", "node.js");
    std::string response = req->getRequest("api.github.com", "/users/ycagri", "443", headers);
    std::cout << response << std::endl;
    EXPECT_NE(0, response.length());
    delete req;
}