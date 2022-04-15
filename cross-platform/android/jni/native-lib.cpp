#include <jni.h>
#include <string>
#include "../../shared/src/http/HttpClient.hpp"
#include "../../shared/src/http/GitHubClient.hpp"
#include "../../shared/src/sqlite/SQLiteDatabaseConnector.hpp"
#include "../../shared/src/GitHubContext.hpp"

extern "C" JNIEXPORT jstring JNICALL Java_com_ycagri_android_github_Library_addUser(
    JNIEnv *env, jobject thiz, jstring dbPath, jstring username)
{
    const char *dbPathString = env->GetStringUTFChars(dbPath, nullptr);
    const char *usernameString = env->GetStringUTFChars(username, nullptr);

    GitHubHttpClient *client = new GitHubClient(new HttpClient());
    DatabaseConnector *connector = new SQLiteDatabaseConnector(dbPathString);
    context::Context *context = new context::GitHubContext(client, connector);
    std::string res = context->addUser(usernameString);

    env->ReleaseStringUTFChars(dbPath, dbPathString);
    env->ReleaseStringUTFChars(username, usernameString);

    delete context;

    return env->NewStringUTF(res.c_str());
}

extern "C" JNIEXPORT jstring JNICALL Java_com_ycagri_android_github_Library_getRepos(
    JNIEnv *env, jobject thiz, jstring dbPath, jstring username)
{
    const char *dbPathString = env->GetStringUTFChars(dbPath, nullptr);
    const char *usernameString = env->GetStringUTFChars(username, nullptr);

    GitHubHttpClient *client = new GitHubClient(new HttpClient());
    DatabaseConnector *connector = new SQLiteDatabaseConnector(dbPathString);
    context::Context *context = new context::GitHubContext(client, connector);
    std::string res = context->getUserRepos(usernameString);

    env->ReleaseStringUTFChars(dbPath, dbPathString);
    env->ReleaseStringUTFChars(username, usernameString);

    delete context;

    return env->NewStringUTF(res.c_str());
}