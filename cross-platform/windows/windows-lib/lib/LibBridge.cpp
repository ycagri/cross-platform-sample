#include "LibBridge.h"
#if __has_include("LibBridge.g.cpp")
#include "LibBridge.g.cpp"
#endif
#include "http/HttpClient.hpp"
#include "http/GitHubClient.hpp"
#include "sqlite/SQLiteDatabaseConnector.hpp"
#include "GitHubContext.hpp"

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::lib::implementation
{
    winrt::hstring LibBridge::AddUser(const::winrt::hstring dbPath, const::winrt::hstring username)
    {
        std::string dbPathStr = winrt::to_string(dbPath);
        std::string usernameStr = winrt::to_string(username);

        GitHubHttpClient* client = new GitHubClient(new HttpClient());
        DatabaseConnector* connector = new SQLiteDatabaseConnector(dbPathStr.c_str());
        context::Context* context = new context::GitHubContext(client, connector);
        std::string res = context->addUser(usernameStr.c_str());
        delete context;

        return winrt::to_hstring(res);
    }

    winrt::hstring LibBridge::GetUserRepos(const::winrt::hstring dbPath, const::winrt::hstring username)
    {
        std::string dbPathStr = winrt::to_string(dbPath);
        std::string usernameStr = winrt::to_string(username);

        GitHubHttpClient* client = new GitHubClient(new HttpClient());
        DatabaseConnector* connector = new SQLiteDatabaseConnector(dbPathStr.c_str());
        context::Context* context = new context::GitHubContext(client, connector);
        std::string res = context->getUserRepos(usernameStr.c_str());
        delete context;

        return winrt::to_hstring(res);
    }
}
