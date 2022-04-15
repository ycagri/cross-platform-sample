//
//  ios_lib.m
//  ios-lib
//
//  Created by ycagri on 14.04.2022.
//

#import "ios_lib.h"
#include "http/HttpClient.hpp"
#include "http/GitHubClient.hpp"
#include "sqlite/SQLiteDatabaseConnector.hpp"
#include "GitHubContext.hpp"

@implementation ios_lib
- (NSString*) addUser: (NSString *)dbPath: (NSString *)username {
    const char* dbPathString = [dbPath cStringUsingEncoding:NSASCIIStringEncoding];
    const char* usernameString = [username cStringUsingEncoding:NSASCIIStringEncoding];

    GitHubHttpClient *client = new GitHubClient(new HttpClient());
    DatabaseConnector *connector = new SQLiteDatabaseConnector(dbPathString);
    context::Context *context = new context::GitHubContext(client, connector);
    std::string res = context->addUser(usernameString);
    
    delete context;
    return [NSString stringWithCString:res.c_str() encoding:[NSString defaultCStringEncoding]];
}

- (NSString*) getRepos: (NSString *)dbPath: (NSString *)username {
    const char* dbPathString = [dbPath cStringUsingEncoding:NSASCIIStringEncoding];
    const char* usernameString = [username cStringUsingEncoding:NSASCIIStringEncoding];

    GitHubHttpClient *client = new GitHubClient(new HttpClient());
    DatabaseConnector *connector = new SQLiteDatabaseConnector(dbPathString);
    context::Context *context = new context::GitHubContext(client, connector);
    std::string res = context->getUserRepos(usernameString);
    
    delete context;
    return [NSString stringWithCString:res.c_str() encoding:[NSString defaultCStringEncoding]];
}
@end
