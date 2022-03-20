#include "User.hpp"

using namespace data_model;

User::User(const ptree *user)
{
    this->id = user->get<long int>("id");
    this->login = user->get<std::string>("login");
    this->name = user->get<std::string>("name");
    this->avatar = user->get<std::string>("avatar_url");
    this->location = user->get<std::string>("location");
    this->publicRepoCount = user->get<int>("public_repos");
}

long int User::getId()
{
    return this->id;
}

std::string User::getLogin()
{
    return this->login;
}

std::string User::getName()
{
    return this->name;
}

std::string User::getAvatar()
{
    return this->avatar;
}

std::string User::getLocation()
{
    return this->location;
}

int User::getPublicRepoCount()
{
    return this->publicRepoCount;
}