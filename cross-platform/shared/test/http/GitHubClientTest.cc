#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <http/GitHubClient.hpp>
#include <iostream>
#include <fstream>

using namespace client;
using namespace data_model;
using ::testing::Return;

class MockHttpClient: public HttpClient {
    public:
        MOCK_METHOD(std::string, getRequest, (const char* host, const char* path, const char* port), (override));
};

std::string readData(const char* path) {
    std::ifstream ifs (path, std::ifstream::in);
    std::ostringstream sstr;
    sstr << ifs.rdbuf();
    ifs.close();
    return sstr.str();
}

TEST(GitHubClientTest, GetUserInfoTest){
    MockHttpClient *client = new MockHttpClient();
    GitHubClient *ghClient = new GitHubClient(client);
    
    EXPECT_CALL(*client, getRequest(testing::StrEq("api.github.com"), testing::StrEq("/users/ycagri"), testing::StrEq("443"))).WillOnce(Return(readData("../shared/test/data/api-user-ycagri.json")));
    User user = ghClient->getUserInfo("ycagri");
    EXPECT_EQ(4305880, user.getId());
    EXPECT_STREQ("ycagri", user.getLogin().c_str());
    EXPECT_STREQ("Yigit Cagri Akkaya", user.getName().c_str());
    EXPECT_STREQ("https://avatars.githubusercontent.com/u/4305880?v=4", user.getAvatar().c_str());
    EXPECT_STREQ("Ankara", user.getLocation().c_str());
    EXPECT_EQ(13, user.getPublicRepoCount());
    delete ghClient;
}

TEST(GitHubClientTest, GetUserReposTest){
    MockHttpClient *client = new MockHttpClient();
    GitHubClient *ghClient = new GitHubClient(client);
    
    EXPECT_CALL(*client, getRequest(testing::StrEq("api.github.com"), testing::StrEq("/users/ycagri/repos"), testing::StrEq("443"))).WillOnce(Return(readData("../shared/test/data/api-repos-ycagri.json")));
    std::vector<Repo> repos = ghClient->getUserRepos("ycagri");
    Repo repo = repos.at(0);
    EXPECT_EQ(13, repos.size());
    EXPECT_EQ(341657976, repo.getId());
    EXPECT_STREQ("bluetooth-messenger", repo.getName().c_str());
    EXPECT_STREQ("Yet another bluetooth messenger for Android devices", repo.getDescription().c_str());
    EXPECT_STREQ("https://github.com/ycagri/bluetooth-messenger", repo.getUrl().c_str());
    EXPECT_FALSE(repo.isPrivateRepo());
    EXPECT_FALSE(repo.isFork());
    EXPECT_STREQ("", repo.getLanguage().c_str());
    EXPECT_EQ(0, repo.getWatcherCount());
    EXPECT_EQ(0, repo.getForkCount());
    EXPECT_EQ(4305880, repo.getUserId());
    delete ghClient;
}