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
 * SWRLSignal is an abstract base class for any presence signal object.  Concrete subclasses are Beacon, WifiInfo and Region
 */

@interface SWRLSignal : NSObject
@property (nonatomic, readonly) NSString *          identifier;
@property (nonatomic, readonly) SWRLSignalType      type;
@property (nonatomic, readonly) double              range;

- (instancetype) initWithIdentifier:(NSString *)identifier;
@end

/**
 * SWRLPlacement represents a logical location associated with a signal.
 * A logical and business-friendly name given to a specific area inside a location. For example - cosmetics, electronics department, checkout, neighborhood, 
 * parking lot, etc.  A SWRLPlacement is contained within a SWRLLocation.
 */

@interface SWRLPlacement : NSObject
@property (nonatomic, readonly) NSString *          identifier;
@property (nonatomic, readonly) NSString *          name;
@property (nonatomic, readonly) BOOL                overlapping;

- (instancetype)initWithDictionary:(NSDictionary *)placement;
@end

/**
 * SWRLLocation represents a physical street, city, state address or real world location.
 */
@interface SWRLLocation : NSObject
@property (nonatomic, readonly) NSString *          identifier;
@property (nonatomic, readonly) NSString *          name;
@property (nonatomic, readonly) NSDictionary *      address;
@property (nonatomic, readonly) double              latitude;
@property (nonatomic, readonly) double              longitude;
@property (nonatomic, readonly) NSString *          timezone;
@property (nonatomic, readonly) SWRLPlacement *     placement;
@property (nonatomic, readonly) NSString *          externalIdentifier;
@property (nonatomic, weak, readonly) SWRLSignal *  signal;

- (SWRLLocation *)location;

- (instancetype) initWithDictionary:(NSDictionary *)location signal:(nullable SWRLSignal *)signal;

@end

NS_ASSUME_NONNULL_END

#endif
