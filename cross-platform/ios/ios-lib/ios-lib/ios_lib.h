//
//  ios_lib.h
//  ios-lib
//
//  Created by ycagri on 14.04.2022.
//

#import <Foundation/Foundation.h>

@interface ios_lib : NSObject
- (NSString*) addUser: (NSString *)dbPath: (NSString *)username;
- (NSString*) getUserRepos: (NSString *)dbPath: (NSString *)username;
@end
