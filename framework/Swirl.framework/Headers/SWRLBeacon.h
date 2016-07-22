/**
 *	SWRLBeacon.h
 *	Swirl
 *  Beacon and related classes.
 *	@copyright 2015 Swirl Networks, Inc. All rights reserved.
 */

#ifndef __SWRLBEACON__
#define __SWRLBEACON__

#import <CoreLocation/CoreLocation.h>
#import <Swirl/SWRLLocation.h>
#import <Swirl/SWRLBeaconAdvertisement.h>

@class SWRLBeaconScanner;

#define SWRLBeaconInvalidRSSI       (-999)
#define SWRLBeaconInvalidRange      ( 999)

/**
 * Beacon state
 */
typedef NS_ENUM(int, SWRLBeaconState) {
    /**
     * Unknown
     */
    SWRLBeaconStateUnknown = 0,
    /**
     * Outside the range of the beacon
     */
    SWRLBeaconStateOutside,
    /**
     * Inside the range of the beacon
     */
    SWRLBeaconStateInside
};

typedef NSMutableArray<SWRLBeaconAdvertisement*> SWRLAdvertisements;

@interface SWRLBeacon : SWRLSignal
//@property (nonatomic, readonly) NSString *          identifier;
@property (nonatomic, readonly) SWRLLocation *      location;       // location
@property (nonatomic, readonly) SWRLBeaconState     state;
@property (nonatomic, readonly) double              range;          // current range estimate
@property (nonatomic, readonly) int                 rssi;           // calculated value from advertisements
@property (nonatomic, readonly) NSTimeInterval      lastDetected;    // timestamp
@property (nonatomic, readonly) NSDictionary *      attributes;     // extended attributes
@property (nonatomic, readonly) NSArray<NSString*> *labels;         // assigned labels
@property (nonatomic, readonly) NSError *           error;          // error?

@property (nonatomic) NSTimeInterval lastEventTime;

- (BOOL) isEntered;
- (BOOL) isOverlapping;

- (void) setError:(NSError *)error;
- (void) setEntered:(BOOL)value;

- (instancetype)initWithAdvertisement:(SWRLBeaconAdvertisement *)advertisement;

- (BOOL) isAdvertisement:(SWRLBeaconAdvertisement *)advertisement;
- (BOOL) addAdvertisement:(SWRLBeaconAdvertisement *)advertisement;
- (void) addAdvertisements:(SWRLAdvertisements *)advertisements;
- (SWRLBeaconAdvertisement *)lastAdvertisement;
- (SWRLAdvertisements *)allAdvertisements;
- (NSTimeInterval)oldestAdvertisement;
- (NSTimeInterval)firstDetected;

- (void)setScanner:(SWRLBeaconScanner *)scanner;
- (SWRLBeaconScanner *)scanner;

- (BOOL) isResolved;
- (NSString *)resolvedIdentifier;
- (void) resolve:(NSDictionary *)info;
- (NSString *)extraInfo;
- (NSString *)serial;

@end

#endif
