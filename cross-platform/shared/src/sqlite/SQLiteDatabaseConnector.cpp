#include "SQLiteDatabaseConnector.hpp"
#include <iostream>
#include <sstream>

SQLiteDatabaseConnector::SQLiteDatabaseConnector(const char *filename)
{
    sqlite3_open_v2(filename, &dbConnection, SQLITE_OPEN_READWRITE, NULL);
    sqlite3_exec(this->dbConnection, "PRAGMA foreign_keys = ON;", NULL, NULL, NULL);
    const char *usersTableQuery = "Create Table If Not Exists tbl_users(id Integer Primary Key, login Text, name Text, avatar Text, location Text, public_repo_count Integer);";
    sqlite3_exec(this->dbConnection, usersTableQuery, NULL, NULL, NULL);
    const char *reposTableQuery = "Create Table If Not Exists tbl_repos(id Integer Primary Key, name Text, description Text, is_private Integer, is_fork Integer, language Text, watcher_count Integer, fork_count Integer, user_id Integer, Foreign Key(user_id) References tbl_users(id));";
    int rc = sqlite3_exec(this->dbConnection, reposTableQuery, NULL, NULL, NULL);
}

SQLiteDatabaseConnector::~SQLiteDatabaseConnector()
{
    sqlite3_close_v2(dbConnection);
}

bool SQLiteDatabaseConnector::dropTable(const char *tableName)
{
    std::stringstream ss;
    ss << "Drop Table " << tableName << ";";
    int rc = sqlite3_exec(this->dbConnection, ss.str().c_str(), NULL, NULL, NULL);
    return rc == SQLITE_OK;
}

bool SQLiteDatabaseConnector::insertUser(User user)
{
    sqlite3_stmt *stmt;
    const char *query = "Insert Or Replace Into tbl_users(id, login, name, avatar, location, public_repo_count) Values(?,?,?,?,?,?)";
    sqlite3_prepare_v2(dbConnection, query, strlen(query), &stmt, 0);
    sqlite3_bind_int(stmt, 1, user.getId());
    sqlite3_bind_text(stmt, 2, user.getLogin().c_str(), user.getLogin().length(), NULL);
    sqlite3_bind_text(stmt, 3, user.getName().c_str(), user.getName().length(), NULL);
    sqlite3_bind_text(stmt, 4, user.getAvatar().c_str(), user.getAvatar().length(), NULL);
    sqlite3_bind_text(stmt, 5, user.getLocation().c_str(), user.getLocation().length(), NULL);
    sqlite3_bind_int(stmt, 6, user.getPublicRepoCount());
    int s = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return s == SQLITE_DONE;
}

bool SQLiteDatabaseConnector::insertRepos(std::vector<Repo> repos)
{
    sqlite3_exec(dbConnection, "BEGIN TRANSACTION;", NULL, NULL, NULL);
    for (std::vector<Repo>::iterator it = repos.begin(); it != repos.end(); ++it)
    {
        sqlite3_stmt *stmt;
        const char *query = "Insert Or Replace Into tbl_repos(id, name, description, is_private, is_fork, language, watcher_count, fork_count, user_id) Values(?,?,?,?,?,?,?,?,?)";
        sqlite3_prepare_v2(dbConnection, query, strlen(query), &stmt, 0);
        sqlite3_bind_int(stmt, 1, it->getId());
        sqlite3_bind_text(stmt, 2, it->getName().c_str(), it->getName().length(), NULL);
        sqlite3_bind_text(stmt, 3, it->getDescription().c_str(), it->getDescription().length(), NULL);
        sqlite3_bind_int(stmt, 4, it->isPrivateRepo() ? 1 : 0);
        sqlite3_bind_int(stmt, 5, it->isFork() ? 1 : 0);
        sqlite3_bind_text(stmt, 6, it->getLanguage().c_str(), it->getLanguage().length(), NULL);
        sqlite3_bind_int(stmt, 7, it->getWatcherCount());
        sqlite3_bind_int(stmt, 8, it->getForkCount());
        sqlite3_bind_int(stmt, 9, it->getUserId());
        int s = sqlite3_step(stmt);
        sqlite3_finalize(stmt);
        if (s != SQLITE_DONE)
        {
            sqlite3_exec(dbConnection, "ROLLBACK;", NULL, NULL, NULL);
            return false;
        }
    }
    int rc = sqlite3_exec(dbConnection, "END TRANSACTION;", NULL, NULL, NULL);
    return rc == SQLITE_OK;
}
