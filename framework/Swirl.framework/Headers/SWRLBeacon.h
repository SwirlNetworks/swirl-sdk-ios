/*
 * SWRLBeacon.h
 * Copyright 2015-2016 Swirl Networks, Inc. All Rights Reserved.
 */


#ifndef __SWRLBEACON__
#define __SWRLBEACON__

#import <CoreLocation/CoreLocation.h>
#import <Swirl/SWRLLocation.h>
#import <Swirl/SWRLBeaconAdvertisement.h>

@class SWRLBeaconScanner;

#define SWRLBeaconInvalidRSSI       (-999)
#define SWRLBeaconInvalidRange      ( 999)
#define SWRLBeaconEnteredRSSI       (-1)

/** Beacon state relative to current threshold set for the beacon. */
typedef NS_ENUM(int, SWRLBeaconState) {
    /**
     * The state (range) of the beacon could not be determined.  This could be because there are insufficient
     * valid advertisements to compute a range.  This can be because the beacon has timed out or it has just been
     * detected and cannot make a determination yet.
     */
    SWRLBeaconStateUnknown = 0,
    
    /**
     * The rabge of the beacon is outside the range set for this beacon.  The SWRLBeaconManager
     * has sufficient samples to make a determination and has determined the beacon to be out of range.
     */
    SWRLBeaconStateOutside,
    
    /**
     * The range of the beacon is wihtin the range set for this beacon. The SWRLBeaconManager has sufficient samples
     * to make a determination and has determined the beacon to be within range.
     */
    
    SWRLBeaconStateInside
};

typedef NSMutableArray<SWRLBeaconAdvertisement*> SWRLAdvertisements;

/**
 *  A SWRLBeacon object defines a type of SWRLSignal that is based on the device’s proximity to a Bluetooth beacon, as opposed
 *  to a geographic location or wifi network. A beacon aggregates a set of SWRLBeaconAdvertisements from a specific
 *  beacon device and matches that device with logical location, placement, and custom attributes specified through the platform.
 *  When the beacon device comes in range, the SWRLBeaconManager will change the state of the beacon and will generate  
 *  appropriate events through its delegate interface SWRLBeaconManagerDelegate.
 */
@interface SWRLBeacon : SWRLSignal

/** ====================================================================================================================
 *  @name Accessing Beacon Location
 *  ====================================================================================================================
 */

/** Logical location associated to this beacon through the plaform. See SWRLLocation. */
@property (nonatomic, readonly) SWRLLocation *      location;

/** ====================================================================================================================
 *  @name Accessing Beacon Range and State
 *  ====================================================================================================================
 */
/** Current state of the beacon (uknown, outside, inside).  See SWRLBeaconState. */
@property (nonatomic, readonly) SWRLBeaconState     state;
/** Current range of the beacon in meters.  This number is not very accurate and fluctuates dramatically. */
@property (nonatomic, readonly) double              range;
/** Current average rssi */
@property (nonatomic, readonly) int                 rssi;

/** ====================================================================================================================
 *  @name Accessing Custom Labels and Attributes
 *  ====================================================================================================================
 */

/** Dictionary of optional custom attributes sent by the server for resolved beacons. */
@property (nonatomic, readonly) NSDictionary *      attributes;
/** Array of label strings sent by the server for resolved beacons. */
@property (nonatomic, readonly) NSArray<NSString*> *labels;

/** ====================================================================================================================
 *  @name Accessing Other Beacon Attributes
 *  ====================================================================================================================
 */

/** Timestamp (timeIntervalSince1970) of the last advertisement received. */
@property (nonatomic, readonly) NSTimeInterval      lastDetected;
/** Error (usually set if there is a beacon detected, but this application has no access). */
@property (nonatomic, readonly) NSError *           error;

/** Is the Placement associated with this beacon set to allow overlapping beacons. */
- (BOOL) isOverlapping;
/** Has this beacon been successfully resolved by the server. */
- (BOOL) isResolved;
/** Is the mobile device currently within the beacon range */
- (BOOL) isEntered;

/** 
 *  Retrieve any additional non-identifier related data associated with the beacon advertisements.  In the case of
 *  Eddystone beacons, this would include TLM data base-64 encoded.
 */
- (NSString *)extraInfo;

/** Retreive the serial number of the beacon device as recorded in the platform. */
- (NSString *)serial;

// ====================================================================================================================
// Internal use
// ====================================================================================================================
@property (nonatomic) NSTimeInterval lastEventTime;

- (void) setError:(NSError *)error;
- (void) setEntered:(BOOL)value;

- (instancetype)initWithAdvertisement:(SWRLBeaconAdvertisement *)advertisement;
- (BOOL) isAdvertisement:(SWRLBeaconAdvertisement *)advertisement;
- (BOOL) addAdvertisement:(SWRLBeaconAdvertisement *)advertisement;
- (void) addAdvertisements:(SWRLAdvertisements *)advertisements;
- (SWRLBeaconAdvertisement *)lastAdvertisement;
- (SWRLAdvertisements *)allAdvertisements;
- (NSTimeInterval)oldestAdvertisement;

- (void)setScanner:(SWRLBeaconScanner *)scanner;
- (SWRLBeaconScanner *)scanner;

- (void) resolve:(NSDictionary *)info;

@end

#endif
