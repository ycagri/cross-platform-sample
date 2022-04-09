#include <gtest/gtest.h>
#include <sqlite/SQLiteDatabaseConnector.hpp>
#include "boost/foreach.hpp"

User* ReadUser(){
    ptree userJson;
    boost::property_tree::read_json("../shared/test/data/api-user-ycagri.json", userJson);
    return new User(&userJson);
}

std::vector<Repo> ReadRepos() {
    std::vector<Repo> repos;
    ptree reposJson;
    boost::property_tree::read_json("../shared/test/data/api-repos-ycagri.json", reposJson);
    BOOST_FOREACH(const ptree::value_type& child, reposJson){
        repos.push_back(Repo(&child.second));
    }
    return repos;
}

TEST(SQLiteDatabaseConnector, InsertUserTableTest){
    SQLiteDatabaseConnector* db = new SQLiteDatabaseConnector(":memory:");
    User* user = ReadUser();
    bool ret = db->insertUser(*user);
    EXPECT_TRUE(ret);
    delete db;
    delete user;
}

TEST(SQLiteDatabaseConnector, InsertReposErrorTableTest){
    SQLiteDatabaseConnector* db = new SQLiteDatabaseConnector(":memory:");
    std::vector<Repo> repos = ReadRepos();
    bool ret = db->insertRepos(repos);
    EXPECT_FALSE(ret);
    delete db;
}

TEST(SQLiteDatabaseConnector, InsertReposTableTest){
    SQLiteDatabaseConnector* db = new SQLiteDatabaseConnector(":memory:");
    User* user = ReadUser();
    db->insertUser(*user);

    std::vector<Repo> repos = ReadRepos();
    bool ret = db->insertRepos(repos);
    EXPECT_FALSE(ret);
    delete db;
    delete user;
}