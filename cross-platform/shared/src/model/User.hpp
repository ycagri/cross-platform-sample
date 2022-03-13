#ifndef USER
#define USER
#include <boost/property_tree/json_parser.hpp>
#include <string>

using boost::property_tree::ptree;

namespace data_model
{
    class User
    {
    private:
        long int id;
        std::string login;
        std::string name;
        std::string avatar;
        std::string location;
        int publicRepoCount;

    public:
        User(const ptree *user);
        long int getId();
        std::string getLogin();
        std::string getName();
        std::string getAvatar();
        std::string getLocation();
        int getPublicRepoCount();
    };
}

#endif