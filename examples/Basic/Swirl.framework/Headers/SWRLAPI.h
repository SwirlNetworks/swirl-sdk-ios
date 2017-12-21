/*
 * SWRLAPI.h
 * Copyright 2015-2016 Swirl Networks, Inc. All Rights Reserved.
 */

#ifndef __SWRLAPI__
#define __SWRLAPI__

#import <Foundation/Foundation.h>
#import <Swirl/SWRLBase.h>
#import <Swirl/SWRLSettings.h>
#import <Swirl/SWRLLocation.h>

// =====================================================================================================================
// SWRLAPI - REST API authenticatino and mobile serving api
// =====================================================================================================================

@interface SWRLAPI : NSObject
@property (nonatomic, readonly) dispatch_queue_t    queue;
@property (nonatomic, readonly) NSString *          apiHost;
@property (nonatomic, readonly) NSString *          cdnHost;
@property (nonatomic, readonly) NSString *          apiKey;
@property (nonatomic, readonly) NSString *          arbitrationKey;
@property (nonatomic, readonly) NSString *          userKey;
@property (nonatomic, readonly) NSString *          partnerName;
@property (nonatomic) NSDictionary *                userInfo;
@property (nonatomic) NSData *                      deviceToken;

- (void) httpRequest:(NSString *)url headers:(NSDictionary *)headers body:(NSData *)body completion:(void (^)(NSURLResponse *response, NSData *data, NSError *error))completion;
- (void) jsonRequest:(NSString *)url headers:(NSDictionary *)headers data:(NSData *)body completion:(void (^)(int status, NSDictionary *result, NSError *error))completion;
- (void) jsonRequest:(NSString *)url body:(NSDictionary *)body completion:(void (^)(int status, NSDictionary *result, NSError *error))completion;
- (void) dataRequest:(NSString *)url completion:(void (^)(NSData *data, NSError *error))completion;

- (void) startWithOptions:(NSDictionary *)options completion:(void (^)(NSError *))completion;
- (void) settingsWithCompletion:(void (^)(NSError *error))completion;
- (void) ping;
- (void) regionsWithCoordinate:(CLLocationCoordinate2D)coord completion:(void (^)(NSArray *regions, NSDictionary *area, NSTimeInterval expires, NSError *error))completion;
- (void) wifiWithIdentifier:(NSString *)identifier rssi:(int)rssi completion:(void (^)(NSDictionary *result, NSError *error))completion;
- (void) beaconWithIdentifier:(NSString *)identifier extraInfo:(NSString *)extraInfo rssi:(int)rssi completion:(void (^)(NSDictionary *result, NSError *error))completion;
- (void) contentWithInfo:(NSDictionary *)info completion:(void (^)(NSDictionary *, NSDictionary *, NSError*))completion;
- (BOOL) contentWithLocation:(SWRLLocation *)location locationDwell:(NSTimeInterval)ldwell placementDwell:(NSTimeInterval)cdwell
              placementEnter:(NSTimeInterval)entry completion:(void (^)(NSDictionary *, NSError *))completion;
- (void) imageWithIdentifier:(NSString *)identifier completion:(void (^)(UIImage *image, NSError *error))completion;
- (void) downloadURL:(NSString *)url completion:(void (^)(NSURL *fileURL, NSError *error))completion;
- (void) uploadImage:(UIImage *)image partner:(NSString *)partner completion:(void (^)(NSDictionary *, NSError *))completion;
- (void) logEvent:(NSString *)event data:(NSString *)data;
- (void) flush:(BOOL)wait;
- (void) reset;

- (void) processDeferred;

- (void) clearLocationLocks:(void (^)(NSError *))completion; // testing only

+ (instancetype)shared;

@end

#endif
