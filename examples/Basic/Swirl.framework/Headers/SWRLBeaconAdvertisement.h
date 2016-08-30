/*
 * SWRLBeaconAdvertisement.h
 * Copyright 2015-2016 Swirl Networks, Inc. All Rights Reserved.
 */

#ifndef __SWRLBEACONADVERTISEMENT__
#define __SWRLBEACONADVERTISEMENT__

#import <Foundation/Foundation.h>

@class CBUUID;

NS_ASSUME_NONNULL_BEGIN

/// A SWRLBeaconAdvertisement is an object which represents a Bluetooth Beacon advertisement in a normalized way for
/// consumption by the rest of the framework.  Beacon protocols broadcast beacon identity information and optionally
/// other attributes, like telemetry (temperature, time, battery, etc).

@interface SWRLBeaconAdvertisement : NSObject<NSCopying>
/// @name Accessing Advertisement Attributes
/// The protocol specific identifier, represented as a urn. For the most part these are opaque and are not processed
/// on the client other than to test for equality.
@property (nonatomic, readonly) NSString *      identifier;
/// A timestamp using timeIntervalSince1970 indicating when the advertisement was detected.
@property (nonatomic, readonly) NSTimeInterval  detected;
/// The signal strength (RSSI) as reported by the operating system.
@property (nonatomic, readonly) int             rssi;
/// The measured power included for some beacon protocols.
@property (nonatomic, readonly) int             dbm1;
/// Extra out-of-band data.  Like Eddystone TLM packet data.  Base-64 encoded.
@property (nonatomic, readonly) NSString *      extraInfo;
/// The peripheral UUID of the device generating these advertisements
@property (nonatomic, readonly) NSUUID *        device;

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

#endif
