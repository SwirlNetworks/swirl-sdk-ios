//
//  SWRAPI.h
//  Swirl
//
//  Created by Thomas Middleton on 11/2/15.
//
//

#import <Foundation/Foundation.h>
#import <Swirl/SWRLSettings.h>
#import <Swirl/SWRLLocation.h>

@interface SWRLAPI : NSObject
@property (nonatomic) dispatch_queue_t      queue;
@property (nonatomic) NSDictionary *        userInfo;
@property (nonatomic, readonly) NSString *  apiHost;
@property (nonatomic, readonly) NSString *  apiKey;
@property (nonatomic, readonly) NSString *  userKey;

- (instancetype) initWithPath:(NSString *)path prefix:(NSString *)prefix queue:(dispatch_queue_t)queue;
- (void) startWithCompletion:(void (^)(NSError *))completion;
- (void) settingsWithCompletion:(void (^)(NSError *error))completion;
- (void) registerWithCompletion:(void (^)(NSError *error))completion;
- (void) regionsWithCoordinate:(CLLocationCoordinate2D)coord completion:(void (^)(NSArray *regions, NSDictionary *area, NSTimeInterval expires, NSError *error))completion;
- (void) wifiWithIdentifier:(NSString *)identifier rssi:(int)rssi completion:(void (^)(NSDictionary *result, NSError *error))completion;
- (void) beaconWithIdentifier:(NSString *)identifier extraInfo:(NSString *)extraInfo rssi:(int)rssi completion:(void (^)(NSDictionary *result, NSError *error))completion;
- (void) contentWithInfo:(NSDictionary *)info completion:(void (^)(NSDictionary *, NSDictionary *, NSError*))completion;
- (void) contentWithLocation:(SWRLLocation *)location locationDwell:(NSTimeInterval)ldwell placementDwell:(NSTimeInterval)cdwell
                 completion:(void (^)(NSDictionary *, NSError *))completion;
- (void) logEvent:(NSString *)event data:(NSString *)data;
- (void) flush;
- (void) reset;

+ (instancetype)shared;

@end