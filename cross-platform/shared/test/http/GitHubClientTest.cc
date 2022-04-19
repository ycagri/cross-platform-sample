#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <http/GitHubClient.hpp>
#include <iostream>
#include <fstream>

using namespace client;
using namespace data_model;
using ::testing::Return;

class MockHttpClient : public HttpClient
{
public:
    MOCK_METHOD(std::string, getRequest, (const char *host, const char *path, const char *port), (override));
    MOCK_METHOD(std::string, getRequest, (const char *host, const char *path, const char *port, (const std::map<std::string, std::string> headerMap)), (override));
};

ACTION(NotConnectedException)
{
    boost::system::error_code err = make_error_code(beast::errc::not_connected);
    throw beast::system_error{err};
}

std::string readData(const char *path)
{
    std::ifstream ifs(path, std::ifstream::in);
    std::ostringstream sstr;
    sstr << ifs.rdbuf();
    ifs.close();
    return sstr.str();
}

TEST(GitHubClientTest, GetUserInfoTest)
{
    MockHttpClient *client = new MockHttpClient();
    GitHubClient *ghClient = new GitHubClient(client);

    EXPECT_CALL(*client, getRequest(testing::StrEq("api.github.com"), testing::StrEq("/users/ycagri"), testing::StrEq("443"), testing::_)).WillOnce(Return(readData("../shared/test/data/api-user-ycagri.json")));
    Response<User> user = ghClient->getUserInfo("ycagri");
    EXPECT_TRUE(user.isSuccessful());
    EXPECT_EQ(4305880, user.getData().getId());
    EXPECT_STREQ("ycagri", user.getData().getLogin().c_str());
    EXPECT_STREQ("Yigit Cagri Akkaya", user.getData().getName().c_str());
    EXPECT_STREQ("https://avatars.githubusercontent.com/u/4305880?v=4", user.getData().getAvatar().c_str());
    EXPECT_STREQ("Ankara", user.getData().getLocation().c_str());
    EXPECT_EQ(13, user.getData().getPublicRepoCount());
    delete ghClient;
}

TEST(GitHubClientTest, GetUserNotExistTest)
{
    MockHttpClient *client = new MockHttpClient();
    GitHubClient *ghClient = new GitHubClient(client);
    EXPECT_CALL(*client, getRequest(testing::StrEq("api.github.com"), testing::StrEq("/users/random_user_name"), testing::StrEq("443"), testing::_)).WillOnce(Return(readData("../shared/test/data/api-user-not-exist.json")));
    Response<User> user = ghClient->getUserInfo("random_user_name");
    EXPECT_FALSE(user.isSuccessful());
    EXPECT_STREQ("Not Found", user.getError().c_str());
    delete ghClient;
}

TEST(GitHubClientTest, GetUserExceptionTest)
{
    MockHttpClient *client = new MockHttpClient();
    GitHubClient *ghClient = new GitHubClient(client);
    boost::system::error_code err = make_error_code(beast::errc::not_connected);
    beast::system_error e = beast::system_error{err};
    EXPECT_CALL(*client, getRequest(testing::StrEq("api.github.com"), testing::StrEq("/users/ycagri"), testing::StrEq("443"), testing::_)).WillRepeatedly(NotConnectedException());
    Response<User> user = ghClient->getUserInfo("ycagri");
    EXPECT_FALSE(user.isSuccessful());
    EXPECT_STREQ(e.what(), user.getError().c_str());
    delete ghClient;
}

TEST(GitHubClientTest, GetUserReposTest)
{
    MockHttpClient *client = new MockHttpClient();
    GitHubClient *ghClient = new GitHubClient(client);
    EXPECT_CALL(*client, getRequest(testing::StrEq("api.github.com"), testing::StrEq("/users/ycagri/repos"), testing::StrEq("443"))).WillOnce(Return(readData("../shared/test/data/api-repos-ycagri.json")));
    Response<std::vector<Repo> > repos = ghClient->getUserRepos("ycagri");
    Repo repo = repos.getData().at(0);
    EXPECT_EQ(13, repos.getData().size());
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