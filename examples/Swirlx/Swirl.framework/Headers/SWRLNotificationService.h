/*
 * SWRLSwirl.h
 * Copyright 2015-2016 Swirl Networks, Inc. All Rights Reserved.
 */

#ifndef __SWRLNOTIFICATIONSERVICE__
#define __SWRLNOTIFICATIONSERVICE__

#import <UserNotifications/UserNotifications.h>

@interface SWRLNotificationService : UNNotificationServiceExtension
@property (nonatomic, strong) void (^contentHandler)(UNNotificationContent *);
@property (nonatomic, strong) UNMutableNotificationContent *content;

- (void)didReceiveNotificationRequest:(UNNotificationRequest *)request withContentHandler:(void (^)(UNNotificationContent *contentToDeliver))contentHandler;
- (void)serviceExtensionTimeWillExpire;

@end

#endif
