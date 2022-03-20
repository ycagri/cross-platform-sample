#include <gtest/gtest.h>
#include <model/Repo.hpp>

using namespace data_model;

TEST(RepoTest, RepoConstructorTest)
{
    ptree repoJson;
    boost::property_tree::read_json("../shared/test/data/repo-bluetooth-messenger.json", repoJson);
    Repo *repo = new Repo(&repoJson);
    EXPECT_EQ(341657976, repo->getId());
    EXPECT_STREQ("bluetooth-messenger", repo->getName().c_str());
    EXPECT_STREQ("Yet another bluetooth messenger for Android devices", repo->getDescription().c_str());
    EXPECT_STREQ("https://github.com/ycagri/bluetooth-messenger", repo->getUrl().c_str());
    EXPECT_FALSE(repo->isPrivateRepo());
    EXPECT_FALSE(repo->isFork());
    EXPECT_STREQ("", repo->getLanguage().c_str());
    EXPECT_EQ(0, repo->getWatcherCount());
    EXPECT_EQ(0, repo->getForkCount());
    EXPECT_EQ(4305880, repo->getUserId());
    delete repo;
}