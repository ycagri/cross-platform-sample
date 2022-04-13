#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <GitHubContext.hpp>
#include "boost/foreach.hpp"

using namespace client;
using namespace data_model;
using namespace context;
using ::testing::Return;

class MockSQLiteDatabaseConnector : public DatabaseConnector
{
public:
    MOCK_METHOD(bool, dropTable, (const char *tableName), (override));
    MOCK_METHOD(bool, insertUser, (User user), (override));
    MOCK_METHOD(bool, insertRepos, (std::vector<Repo>), (override));
};

class MockGitHubHttpClient : public GitHubHttpClient
{
public:
    MOCK_METHOD(Response<User>, getUserInfo, (const char *username), (override));
    MOCK_METHOD(Response<std::vector<Repo> >, getUserRepos, (const char *username), (override));
};

std::vector<Repo> readRepos(){
    ptree reposJson;
    boost::property_tree::read_json("../shared/test/data/api-repos-ycagri.json", reposJson);
    std::vector<Repo> repos;
    BOOST_FOREACH (const ptree::value_type &child, reposJson)
    {
        repos.push_back(Repo(&child.second));
    }
    return repos;
}

TEST(GitHubContextTest, GetUserInfoErrorTest)
{    
    MockGitHubHttpClient *client = new MockGitHubHttpClient();
    ON_CALL(*client, getUserInfo(testing::StrEq("ycagri"))).WillByDefault(Return(Response<User>::error("error")));

    MockSQLiteDatabaseConnector *connector = new MockSQLiteDatabaseConnector();
    GitHubContext *context = new GitHubContext(client, connector);
    std::string res = context->addUser("ycagri");
    EXPECT_CALL(*connector, insertUser(testing::_)).Times(0);
    EXPECT_STREQ("error", res.c_str());

    delete context;
}

TEST(GitHubContextTest, GetUserInfoTest)
{
    ptree userJson;
    boost::property_tree::read_json("../shared/test/data/api-user-ycagri.json", userJson);
    User user = User(&userJson);
    
    MockGitHubHttpClient *client = new MockGitHubHttpClient();
    ON_CALL(*client, getUserInfo(testing::StrEq("ycagri"))).WillByDefault(Return(Response<User>::success(user)));

    MockSQLiteDatabaseConnector *connector = new MockSQLiteDatabaseConnector();
    EXPECT_CALL(*connector, insertUser(testing::_)).Times(1);

    GitHubContext *context = new GitHubContext(client, connector);
    std::string res = context->addUser("ycagri");
    EXPECT_STREQ("", res.c_str());

    delete context;
}

TEST(GitHubContextTest, GetReposErrorTest)
{    
    MockGitHubHttpClient *client = new MockGitHubHttpClient();
    ON_CALL(*client, getUserRepos(testing::StrEq("ycagri"))).WillByDefault(Return(Response<std::vector<Repo> >::error("error")));

    MockSQLiteDatabaseConnector *connector = new MockSQLiteDatabaseConnector();
    GitHubContext *context = new GitHubContext(client, connector);
    std::string res = context->getUserRepos("ycagri");
    EXPECT_CALL(*connector, insertRepos(testing::_)).Times(0);
    EXPECT_STREQ("error", res.c_str());

    delete context;
}

TEST(GitHubContextTest, GetReposTest)
{    
    MockGitHubHttpClient *client = new MockGitHubHttpClient();
    ON_CALL(*client, getUserRepos(testing::StrEq("ycagri"))).WillByDefault(Return(Response<std::vector<Repo> >::success(readRepos())));

    MockSQLiteDatabaseConnector *connector = new MockSQLiteDatabaseConnector();
    EXPECT_CALL(*connector, insertRepos(testing::_)).Times(1);
    
    GitHubContext *context = new GitHubContext(client, connector);
    std::string res = context->getUserRepos("ycagri");
    EXPECT_STREQ("", res.c_str());

    delete context;
}