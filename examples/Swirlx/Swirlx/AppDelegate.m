// =====================================================================================================================
// Swirlx - Sample
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
    
    UIUserNotificationSettings *settings = [application currentUserNotificationSettings];
    settings = [UIUserNotificationSettings settingsForTypes:settings.types|UIUserNotificationTypeAlert|UIUserNotificationTypeSound
                                                 categories:settings.categories];
    [application registerUserNotificationSettings:settings];
}

// =====================================================================================================================
// application:didReceiveLocalNotifications:
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
    
    // NOTE: because this a test application with some configurable options, we will write this
    // api-key to those options, but in a normal application this would not be required
    if ([[NSUserDefaults standardUserDefaults] objectForKey:@"swirl_options"] == nil) {
        #error "REPLACE-YOUR-API-KEY"
        NSDictionary *options = @{ SWRLSettingApiKey : @"REPLACE-WITH-YOUR-API-KEY" }; // ADD-YOUR-API-KEY
        [[NSUserDefaults standardUserDefaults] setObject:options forKey:@"swirl_options"];
        [[NSUserDefaults standardUserDefaults] synchronize];
    }
    
    // NOTE: a more typical start example would only have a static dictionary of options, usually just api-key
    //  [[Swril shared] start:@{ SWRLSettingApiKey: @"zzxx93TY712345fPTkyKkvrF48cz99999ggggg9999" }];
    
    [[Swirl shared] start:[[NSUserDefaults standardUserDefaults] objectForKey:@"swirl_options"]];
    
    [self requestPermissions:application];
    return YES;
}

@end
