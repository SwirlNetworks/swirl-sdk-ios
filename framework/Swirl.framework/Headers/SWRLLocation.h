/*
 * SWRLLocation.h
 * Copyright 2015-2016 Swirl Networks, Inc. All Rights Reserved.
 */

#ifndef __SWRLLOCATION__
#define __SWRLLOCATION__

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/***** Signal Types ****/

typedef NS_ENUM(int, SWRLSignalType) {
    /** Signal is Beacon */
    SWRLSignalTypeBeacon    = 1,
    /** Signal is a WifiInfo */
    SWRLSignalTypeWifi      = 2,
    /** Signal is a Region */
    SWRLSignalTypeGeofence  = 3
};

/**
 * SWRLSignal is an abstract base class for any presence signal object.  Concrete subclasses are Beacon, WifiInfo and Region.
 * A signal is tied to a logical placement and location.
 */

@interface SWRLSignal : NSObject
/** @name Accessing Attributes */
/** Unique identifier for this signal.  Generally used only to lookup and distinquish different signals. */
@property (nonatomic, readonly) NSString *          identifier;
/** Type of signal. */
@property (nonatomic, readonly) SWRLSignalType      type;
/** This is the approximate range to the beacon.  This is a rough approximation. */
@property (nonatomic, readonly) double              range;
/** This is the swirl internal identifier */
@property (nonatomic, readonly) NSString *          resolvedIdentifier;

- (instancetype) initWithIdentifier:(NSString *)identifier;
@end

/**
 * SWRLPlacement represents a logical and business-friendly name given to a specific area inside a location. 
 * For example - cosmetics, electronics department, checkout, neighborhood, parking lot, etc.  
 * A SWRLPlacement is contained within a SWRLLocation.
 */

@interface SWRLPlacement : NSObject
/** @name Accessing Attributes */
/** Unique identifier of a placement. */
@property (nonatomic, readonly) NSString *          identifier;
/** Display name of the placement. */
@property (nonatomic, readonly) NSString *          name;
/** A placement flagged as overlapping allows beacons to overlap with other beacons in other placements. */
@property (nonatomic, readonly) BOOL                overlapping;

- (instancetype)initWithDictionary:(NSDictionary *)placement;
@end

/**
 * SWRLLocation represents a physical street, city, state address or real world location.
 */
@interface SWRLLocation : NSObject
/** @name Accessing Attributes */
/** Unique identifier of the location. */
@property (nonatomic, readonly) NSString *          identifier;
/** A friendly name associated with the location */
@property (nonatomic, readonly) NSString *          name;
/** The street address for the location */
@property (nonatomic, readonly) NSDictionary *      address;
/** Latitude associated with the location */
@property (nonatomic, readonly) double              latitude;
/** Longitude associated with the location */
@property (nonatomic, readonly) double              longitude;
/** Timezone for the location */
@property (nonatomic, readonly) NSString *          timezone;
/** If a location represents a specific location with content, the placement will be non-nil.
 *  If a location represents the overall location (without regard to sub-area), the placement will be nil.
 */
@property (nonatomic, readonly) SWRLPlacement *     placement;
/** A customer assigned identifier or code associated with this location. */
@property (nonatomic, readonly) NSString *          externalIdentifier;
/** A signal that most recently triggered an event in this location */
@property (nonatomic, weak, readonly) SWRLSignal *  signal;

- (SWRLLocation *)location;

- (instancetype) initWithDictionary:(NSDictionary *)location signal:(nullable SWRLSignal *)signal;

@end

NS_ASSUME_NONNULL_END

#endif
