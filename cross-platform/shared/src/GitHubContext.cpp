#include "GitHubContext.hpp"

using namespace context;
using namespace client;

GitHubContext::GitHubContext(GitHubHttpClient *httpClient, DatabaseConnector *con){
    this->client = httpClient;
    this->connector = con;
}

GitHubContext::~GitHubContext(){
    delete this->client;
    delete this->connector;
}

std::string GitHubContext::addUser(const char* username) {
    Response<User> response = this->client->getUserInfo(username);
    if(response.isSuccessful()) {
        this->connector->insertUser(response.getData());
    }

    return response.getError();
}

std::string GitHubContext::getUserRepos(const char* username){
    Response<std::vector<Repo> > response = this->client->getUserRepos(username);
    if(response.isSuccessful()) {
        this->connector->insertRepos(response.getData());
    }

    return response.getError();
}