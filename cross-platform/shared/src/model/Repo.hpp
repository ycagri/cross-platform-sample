#ifndef REPO
#define REPO
#include <boost/property_tree/json_parser.hpp>
#include <string>

using boost::property_tree::ptree;

namespace data_model
{

    class Repo
    {
    public:
        Repo(const ptree *repo);
        ~Repo();

        long int getId();
        std::string getName();
        std::string getDescription();
        std::string getUrl();
        bool isPrivateRepo();
        bool isFork();
        std::string getLanguage();
        int getWatcherCount();
        int getForkCount();
        long int getUserId();

    private:
        long int id;
        std::string name;
        std::string description;
        std::string url;
        bool privateRepo;
        bool fork;
        std::string language;
        int watcherCount;
        int forkCount;
        long int userId;
    };
}

#endif