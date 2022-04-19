#include "GitHubClient.hpp"
#include <sstream>
#include <boost/iostreams/stream.hpp>
#include "boost/foreach.hpp"
#include "boost/assign.hpp"

using namespace client;
using namespace data_model;

GitHubClient::GitHubClient(HttpClient *client)
{
    this->client = client;
}

GitHubClient::~GitHubClient()
{
    delete this->client;
}

Response<User> GitHubClient::getUserInfo(const char *username)
{
    std::stringstream ss;
    ss << "/users/" << username;
    try
    {
        std::string response = this->client->getRequest("api.github.com", ss.str().c_str(), "443");
        ptree json = this->jsonFromString(response);
        boost::optional<std::string> message = json.get_optional<std::string>("message");
        if (message)
            return Response<User>::error(message.get().c_str());

        return Response<User>::success(User(&json));
    }
    catch (beast::system_error e)
    {
        return Response<User>::error(e.what());
    }
}

Response<std::vector<Repo> > GitHubClient::getUserRepos(const char *username)
{
    std::vector<Repo> repos = std::vector<Repo>();
    std::stringstream ss;
    ss << "/users/" << username << "/repos";
    try
    {
        std::string response = this->client->getRequest("api.github.com", ss.str().c_str(), "443");
        ptree json = this->jsonFromString(response);
        boost::optional<std::string> message = json.get_optional<std::string>("message");
        if (message)
            return Response<std::vector<Repo> >::error(message.get().c_str());
        BOOST_FOREACH (const ptree::value_type &child, json)
        {
            repos.push_back(Repo(&child.second));
        }
        return Response<std::vector<Repo> >::success(repos);
    }
    catch (beast::system_error e)
    {
        return Response<std::vector<Repo> >::error(e.what());
    }
}

ptree GitHubClient::jsonFromString(std::string input)
{
    ptree tree;
    boost::iostreams::stream<boost::iostreams::array_source> stream(input.c_str(), input.length());
    boost::property_tree::read_json(stream, tree);
    return tree;
}