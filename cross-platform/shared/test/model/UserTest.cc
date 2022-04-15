#include <gtest/gtest.h>
#include <model/User.hpp>

using namespace data_model;

TEST(UserTest, UserConstructorTest)
{
    ptree userJson;
    boost::property_tree::read_json("../shared/test/data/api-user-ycagri.json", userJson);
    User *user = new User(&userJson);
    EXPECT_EQ(4305880, user->getId());
    EXPECT_STREQ("ycagri", user->getLogin().c_str());
    EXPECT_STREQ("Yigit Cagri Akkaya", user->getName().c_str());
    EXPECT_STREQ("https://avatars.githubusercontent.com/u/4305880?v=4", user->getAvatar().c_str());
    EXPECT_STREQ("Ankara", user->getLocation().c_str());
    EXPECT_EQ(13, user->getPublicRepoCount());
    delete user;
}