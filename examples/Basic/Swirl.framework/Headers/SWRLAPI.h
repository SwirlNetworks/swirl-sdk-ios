/*
 * SWRLAPI.h
 * Copyright 2015-2016 Swirl Networks, Inc. All Rights Reserved.
 */

#ifndef __SWRLAPI__
#define __SWRLAPI__

#import <Foundation/Foundation.h>
#import <Swirl/SWRLSettings.h>
#import <Swirl/SWRLLocation.h>

@interface SWRLAPI : NSObject
@property (nonatomic) dispatch_queue_t      queue;
@property (nonatomic) NSDictionary *        userInfo;
@property (nonatomic, readonly) NSString *  apiHost;
@property (nonatomic, readonly) NSString *  apiKey;
@property (nonatomic, readonly) NSString *  userKey;
@property (nonatomic, readonly) NSString *  arbitrationKey;

- (instancetype) initWithPath:(NSString *)path prefix:(NSString *)prefix queue:(dispatch_queue_t)queue;

- (void) startWithOptions:(NSDictionary *)options completion:(void (^)(NSError *))completion;
- (void) settingsWithCompletion:(void (^)(NSError *error))completion;
- (void) ping;
- (void) regionsWithCoordinate:(CLLocationCoordinate2D)coord completion:(void (^)(NSArray *regions, NSDictionary *area, NSTimeInterval expires, NSError *error))completion;
- (void) wifiWithIdentifier:(NSString *)identifier rssi:(int)rssi completion:(void (^)(NSDictionary *result, NSError *error))completion;
- (void) beaconWithIdentifier:(NSString *)identifier extraInfo:(NSString *)extraInfo rssi:(int)rssi completion:(void (^)(NSDictionary *result, NSError *error))completion;
- (void) contentWithInfo:(NSDictionary *)info completion:(void (^)(NSDictionary *, NSDictionary *, NSError*))completion;
- (BOOL) contentWithLocation:(SWRLLocation *)location locationDwell:(NSTimeInterval)ldwell placementDwell:(NSTimeInterval)cdwell
              placementEnter:(NSTimeInterval)entry completion:(void (^)(NSDictionary *, NSError *))completion;
- (void) logEvent:(NSString *)event data:(NSString *)data;
- (void) flush:(BOOL)wait;
- (void) reset;

- (void) processDeferred;

// move to SWRLConfiguration
- (void) clearLocationLocks:(void (^)(NSError *))completion; // testing only

+ (instancetype)shared;


@end

#endif
