#ifndef GITHUB_CLIENT
#define GITHUB_CLIENT
#include "HttpClient.hpp"
#include "model/User.hpp"
#include "model/Repo.hpp"
#include "Response.hpp"
#include <string>
#include <vector>

using namespace data_model;

namespace client
{

    class GitHubHttpClient
    {
    public:
        virtual ~GitHubHttpClient() {}
        virtual Response<User> getUserInfo(const char *username) = 0;
        virtual Response<std::vector<Repo> > getUserRepos(const char *username) = 0;
    };

    class GitHubClient : public GitHubHttpClient
    {
    public:
        GitHubClient(HttpClient *client);
        ~GitHubClient();

        Response<User> getUserInfo(const char *username);
        Response<std::vector<Repo> > getUserRepos(const char *username);

    private:
        HttpClient *client;

        ptree jsonFromString(std::string input);
        bool isSuccessful(ptree response);
    };

}

#endif