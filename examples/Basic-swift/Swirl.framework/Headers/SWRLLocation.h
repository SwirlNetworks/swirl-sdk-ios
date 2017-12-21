/*
 * SWRLLocation.h
 * Copyright 2015-2016 Swirl Networks, Inc. All Rights Reserved.
 */

#ifndef __SWRLLOCATION__
#define __SWRLLOCATION__

#import <Foundation/Foundation.h>
#import <Swirl/SWRLObject.h>
#import <Swirl/SWRLSignal.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * SWRLPlacement represents a logical and business-friendly name given to a specific area inside a location. 
 * For example - cosmetics, electronics department, checkout, neighborhood, parking lot, etc.  
 * A SWRLPlacement is contained within a SWRLLocation.
 */

@interface SWRLPlacement : SWRLObject

/** ====================================================================================================================
 *  @name Accessing Attributes 
 *  ====================================================================================================================
 */

/** 
 * A placement flagged as overlapping allows beacons to overlap with other beacons in other placements. 
 */
@property (nonatomic, readonly) BOOL                overlapping;

@end

/**
 * SWRLLocation represents a physical street, city, state address or real world location.
 */
@interface SWRLLocation : SWRLObject

/** ====================================================================================================================
 * @name Accessing Attributes
 *  ====================================================================================================================
 */

/**
 * A customer assigned identifier or code associated with this location.
 */
@property (nonatomic, readonly) NSString *          externalIdentifier;
/** 
 * The street address for the location 
 */
@property (nonatomic, readonly) NSDictionary *      address;
/** 
 * Latitude associated with the location 
 */
@property (nonatomic, readonly) double              latitude;
/** 
 * Longitude associated with the location 
 */
@property (nonatomic, readonly) double              longitude;
/** 
 * Timezone for the location 
 */
@property (nonatomic, readonly) NSString *          timezone;
/** 
 * True if live event streaming is enabled for this location 
 */
@property (nonatomic, readonly) BOOL                streamEvents;
/**
 *  If a location represents a specific location with content, the placement will be non-nil.
 *  If a location represents the overall location (without regard to sub-area), the placement will be nil.
 */
@property (nonatomic, readonly) SWRLPlacement *     placement;
/** 
 * A signal that most recently triggered an event in this location 
 */
@property (nonatomic, weak, readonly) SWRLSignal *  signal;

/**
 * Returns a location that does not include any placment information.
 */
- (SWRLLocation *)location;

- (instancetype) initWithDictionary:(NSDictionary *)location signal:(nullable SWRLSignal *)signal;

@end

NS_ASSUME_NONNULL_END

#endif
