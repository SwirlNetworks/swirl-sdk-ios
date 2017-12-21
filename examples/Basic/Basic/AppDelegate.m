// =====================================================================================================================
// Basic - Sample
// AppDelegate.h
//
// Copyright 2015-2016, Swirl Networks, Inc.  All Rights Reserved..
// =====================================================================================================================

#import <Swirl/Swirl.h>
#import "AppDelegate.h"
#import "ContentManager.h"


@implementation AppDelegate {
    CLLocationManager *locationManager; // used for requesting location permissions
}

- (void) requestPermissions:(UIApplication *)application {
    [(locationManager = [[CLLocationManager alloc] init]) requestAlwaysAuthorization];
    
    if ([UIDevice currentDevice].systemVersion.floatValue < 10.0) {
        UIUserNotificationSettings *settings = [application currentUserNotificationSettings];
        settings = [UIUserNotificationSettings settingsForTypes:settings.types|UIUserNotificationTypeAlert|UIUserNotificationTypeSound
                                                     categories:settings.categories];
        [application registerUserNotificationSettings:settings];
        [application registerForRemoteNotifications];
    } else {
        [[UNUserNotificationCenter currentNotificationCenter] requestAuthorizationWithOptions:(UNAuthorizationOptionAlert|UNAuthorizationOptionSound)
            completionHandler:^(BOOL granted, NSError * _Nullable error) {
                NSLog(@"notification permissions granted=%d (error=%@)", granted, error);
                dispatch_async(dispatch_get_main_queue(), ^{
                    [application registerForRemoteNotifications];
                });
            }];
    }
}

// =====================================================================================================================
// application:didReceiveLocalNotification:
//
//  Need to hook this and pass notifications to the Swirl SDK.  Swirl will ignore notifications that are not Swirl notifications
//  otherwise, it will dispatch the attached content.  If you do not hook this, then notifications will not work in the
//  case where the application is being launched because the user opened a notification, but it was already running and
//  so didFinishLaunchingWithOptions is never called.
// =====================================================================================================================

- (void)application:(UIApplication *)application didReceiveLocalNotification:(UILocalNotification *)notification {
    [[Swirl shared] postObject:notification];
}

// =====================================================================================================================
// application:didFinishLaunchingWithOptions:
//  Configure any options
//  Add any delegates, like the ContentManager or any custom delegates (they can also be added and removed later)
//  Start the SDK
// =====================================================================================================================

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    [[Swirl shared] addDelegate:[ContentManager new]];

	#error "REPLACE-WITH-YOUR-API-KEY"
	[[Swirl shared] start:@{ SWRLSettingApiKey: @"REPLACE-WITH-YOUR-API-KEY" }];
    
    [self requestPermissions:application];
    return YES;
}

@end
