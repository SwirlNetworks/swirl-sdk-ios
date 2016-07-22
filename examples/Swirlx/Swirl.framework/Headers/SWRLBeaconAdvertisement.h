//
//  SWRLBeaconAdvertisement.h
//  Swirl
//
//  Created by Thomas Middleton on 4/20/16.
//
//

#import <Foundation/Foundation.h>

@class CBUUID;

NS_ASSUME_NONNULL_BEGIN

@interface SWRLBeaconAdvertisement : NSObject<NSCopying>
@property (nonatomic, readonly) NSString *      identifier;         // identifier, urn representation of broadcast
@property (nonatomic, readonly) NSTimeInterval  detected;           // detection timestamp
@property (nonatomic, readonly) int             rssi;               // signal strength
@property (nonatomic, readonly) int             dbm1;               // measured power included for some beacon protocols
@property (nonatomic, readonly) NSString *      extraInfo;          // extra data (encoded telemetry)
@property (nonatomic, readonly) NSUUID *        device;             // device uuid

- (NSString *)uniquePrefix;
- (void) setDbm1:(int)dbm1;
- (void) setRssi:(int)rssi;
- (void) setExtraInfo:(NSString *)extraInfo;

- (id)copyWithZone:(nullable NSZone *)zone;

+ (SWRLBeaconAdvertisement *)beaconAdvertisementWithData:(NSDictionary *)data rssi:(int)rssi timestamp:(NSTimeInterval)timestamp device:(NSUUID *)device;
+ (SWRLBeaconAdvertisement *)beaconAdvertisementWithIdentifier:(NSString *)identifier rssi:(int)rssi timestamp:(NSTimeInterval)timestamp;
+ (NSString *)uniquePrefix:(NSString *)identifier;
@end

NS_ASSUME_NONNULL_END

