#ifndef SQLiteDatabaseConnector_hpp
#define SQLiteDatabaseConnector_hpp

#include <stdio.h>
#include "sqlite3.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <map>
#include <vector>
#include "model/User.hpp"
#include "model/Repo.hpp"

using namespace data_model;

class DatabaseConnector {
    public:
        virtual ~DatabaseConnector() { }

        virtual bool dropTable(const char* tableName) = 0;
        virtual bool insertUser(User user) = 0;
        virtual bool insertRepos(std::vector<Repo> repos) = 0;
};


class SQLiteDatabaseConnector: public DatabaseConnector {

    public:
        SQLiteDatabaseConnector(const char* filename);
        ~SQLiteDatabaseConnector();

        bool dropTable(const char* tableName);
        bool insertUser(User user);
        bool insertRepos(std::vector<Repo> repos);

    private:
        sqlite3* dbConnection;
};
#endif
