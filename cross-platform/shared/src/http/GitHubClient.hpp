#ifndef GITHUB_CLIENT
#define GITHUB_CLIENT
#include "HttpClient.hpp"
#include "model/User.hpp"
#include "model/Repo.hpp"
#include <string>
#include <vector>

using namespace data_model;

namespace client
{
    class GitHubClient
    {
        public:
            GitHubClient(HttpClient* client);
            ~GitHubClient();

            User getUserInfo(const char* username);
            std::vector<Repo> getUserRepos(const char* username);

        private:
            HttpClient *client;

            ptree jsonFromString(std::string input);
    };
       
}


#endif