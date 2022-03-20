#include "GitHubClient.hpp"
#include <sstream>
#include <boost/iostreams/stream.hpp>
#include "boost/foreach.hpp"

using namespace client;
using namespace data_model;

GitHubClient::GitHubClient(HttpClient *client){
    this->client = client;
}

GitHubClient::~GitHubClient(){
    delete this->client;
}

User GitHubClient::getUserInfo(const char* username){
    std::stringstream ss;
    ss << "/users/" << username;
    std::string response = this->client->getRequest("api.github.com", ss.str().c_str(), "443");   
    ptree json = this->jsonFromString(response);
    return User(&json);
}

std::vector<Repo> GitHubClient::getUserRepos(const char* username){
    std::vector<Repo> repos;
    std::stringstream ss;
    ss << "/users/" << username << "/repos";
    std::string response = this->client->getRequest("api.github.com", ss.str().c_str(), "443");   
    ptree json = this->jsonFromString(response);
    BOOST_FOREACH(const ptree::value_type& child, json){
        repos.push_back(Repo(&child.second));
    }
    return repos;
}

ptree GitHubClient::jsonFromString(std::string input){
    ptree tree;
    boost::iostreams::stream<boost::iostreams::array_source> stream(input.c_str(), input.length());
    boost::property_tree::read_json(stream, tree);
    return tree;
}