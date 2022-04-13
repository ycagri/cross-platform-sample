#include <gtest/gtest.h>
#include <http/Response.hpp>

using namespace client;

TEST(ResponseTest, ResponseSuccessTest)
{
    std::string data = std::string("success");
    Response<std::string> res = Response<std::string>::success(data);
    EXPECT_EQ(data, res.getData());
    EXPECT_STREQ("", res.getError().c_str());
    EXPECT_TRUE(res.isSuccessful());
}

TEST(ResponseTest, ResponseErrorTest)
{
    Response<std::string> res = Response<std::string>::error("error");
    EXPECT_STREQ("error", res.getError().c_str());
    EXPECT_FALSE(res.isSuccessful());
}