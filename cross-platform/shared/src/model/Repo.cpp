#include "Repo.hpp"

using namespace data_model;
using boost::optional;

Repo::Repo(const ptree *repo)
{
    this->id = repo->get<long int>("id");
    this->name = repo->get<std::string>("name");
    this->description = repo->get<std::string>("description");
    if (this->description == "null")
        this->description = "";
    this->url = repo->get<std::string>("html_url");
    this->privateRepo = repo->get<bool>("private");
    this->fork = repo->get<bool>("fork");
    this->language = repo->get<std::string>("language");
    if (this->language == "null")
        this->language = "";
    this->watcherCount = repo->get<int>("watchers_count");
    this->forkCount = repo->get<int>("forks_count");
    ptree owner = repo->get_child("owner");
    this->userId = repo->get_child("owner").get<long int>("id");
}

Repo::~Repo()
{
}

long int Repo::getId()
{
    return this->id;
}
std::string Repo::getName()
{
    return this->name;
}

std::string Repo::getDescription()
{
    return this->description;
}

std::string Repo::getUrl()
{
    return this->url;
}

bool Repo::isPrivateRepo()
{
    return this->privateRepo;
}

bool Repo::isFork()
{
    return this->fork;
}

std::string Repo::getLanguage()
{
    return this->language;
}
int Repo::getWatcherCount()
{
    return this->watcherCount;
}
int Repo::getForkCount()
{
    return this->forkCount;
}
long int Repo::getUserId()
{
    return this->userId;
}