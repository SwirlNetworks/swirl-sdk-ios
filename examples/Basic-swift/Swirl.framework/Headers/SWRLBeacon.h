/*
 * SWRLBeacon.h
 * Copyright 2015-2016 Swirl Networks, Inc. All Rights Reserved.
 */


#ifndef __SWRLBEACON__
#define __SWRLBEACON__

#import <CoreLocation/CoreLocation.h>
#import <Swirl/SWRLLocation.h>
#import <Swirl/SWRLBeaconAdvertisement.h>

@class SWRLPeripheral;
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
 *  @name Accessing Beacon Attributes
 *  ====================================================================================================================
 */

/** 
 * Current state of the beacon (uknown, outside, inside).  See SWRLBeaconState. 
 */
@property (nonatomic, readonly) SWRLBeaconState     state;

/** 
 * Current average rssi 
 */
@property (nonatomic, readonly) int                 rssi;

/** 
 * Is the Placement associated with this beacon set to allow overlapping beacons. 
 */

- (BOOL) isOverlapping;

/** 
 * Is the mobile device currently within the beacon range
 */
- (BOOL) isEntered;
- (void) setEntered:(BOOL)value;

/** 
 *  Retrieve any additional non-identifier related data associated with the beacon advertisements.  In the case of
 *  Eddystone beacons, this would include TLM data base-64 encoded.
 */
- (NSString *)extraInfo;

/**
 * Retrieve the manufacturer of the beacon device.
 */
- (NSString *)manufacturer;

/**
 * Retreive the model of the beacon device
 */
- (NSString *)model;

/** 
 * Retreive the serial number of the beacon device as recorded in the platform. 
 */

- (NSString *)serial;

/**
 * Retreive the protocol of the underlying advertisements
 */
- (int)protocol;

/**
 * Retreive the protocol description of the underlying advertisements
 */
- (NSString *)protocolDescription;

/**
 * Retreive the address of the beacon device
 */
- (NSString *)address;

/**
 * Is the beacon in a connectable state
 */
- (BOOL) isConnectable;

/**
 * Retreive the peripheral of the beacon if possible.
 */
- (SWRLPeripheral *)peripheral;

/**
 * Retreive the partner information for this beacon
 */
- (SWRLObject *)partner;

/**
 * Customize RSSI smoothing parameters
 *  opt_sample_age - seconds to average over
 *  max_sample_age - max seconds to average over if not min samples
 *  min_samples    - min samples required
 * @param params Smoothing parameters
 */
- (void) setRssiParameters:(NSDictionary *)params;

// ====================================================================================================================
// Internal use
// ====================================================================================================================


- (instancetype)initWithAdvertisement:(SWRLBeaconAdvertisement *)advertisement;
- (BOOL) isAdvertisement:(SWRLBeaconAdvertisement *)advertisement;
- (BOOL) addAdvertisement:(SWRLBeaconAdvertisement *)advertisement;
- (void) addAdvertisements:(SWRLAdvertisements *)advertisements;
- (SWRLBeaconAdvertisement *)lastAdvertisement;
- (SWRLAdvertisements *)allAdvertisements;
- (NSTimeInterval)oldestAdvertisement;

- (SWRLBeaconScanner *)scanner;
- (void)setScanner:(SWRLBeaconScanner *)scanner;

- (NSString *)longDescription;

@end

#endif
