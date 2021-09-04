//
//  AppDelegate.m
//  sample
//
//  Created by 洪青文 on 2020/9/4.
//  Copyright © 2020 洪青文. All rights reserved.
//

#import "AppDelegate.h"
#import "HomeViewController.h"
#import "TXTThirdSDK/OpenSDK1.8.7.1_NoPay/WXApi.h"

@interface AppDelegate ()<WXApiDelegate>

@end

@implementation AppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    // Override point for customization after application launch.
    HomeViewController *baseView = [[HomeViewController alloc]initWithNibName:@"HomeViewController" bundle:[NSBundle mainBundle]];
      UINavigationController *nav = [[UINavigationController alloc] initWithRootViewController:baseView];
      
      self.window.rootViewController = nav;
      [self.window makeKeyAndVisible];
    
   
    
    return YES;
}

- (BOOL)application:(UIApplication *)application continueUserActivity:(NSUserActivity *)userActivity restorationHandler:(void (^)(NSArray<id<UIUserActivityRestoring>> * _Nullable))restorationHandler{
    return [WXApi handleOpenUniversalLink:userActivity delegate:self];
}

- (void)applicationWillEnterForeground:(UIApplication *)application{
    
    [[NSNotificationCenter defaultCenter] postNotificationName:@"applicationWillEnterForeground" object:nil];
}

@end
