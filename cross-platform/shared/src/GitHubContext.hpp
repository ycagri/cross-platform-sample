#ifndef GITHUB_CONTEXT
#define GITHUB_CONTEXT
#include "sqlite/SQLiteDatabaseConnector.hpp"
#include "http/GitHubClient.hpp"

using namespace client;

namespace context
{
    class Context
    {
        public:
            virtual std::string addUser(const char* username) = 0;
            virtual std::string getUserRepos(const char* username) = 0;
    };

    class GitHubContext: public Context {
        public:
            GitHubContext(GitHubHttpClient *httpClient, DatabaseConnector *con);
            ~GitHubContext();
            
            std::string addUser(const char* username);
            std::string getUserRepos(const char* username);

        private:
            GitHubHttpClient *client;
            DatabaseConnector* connector;
    };
}


#endif