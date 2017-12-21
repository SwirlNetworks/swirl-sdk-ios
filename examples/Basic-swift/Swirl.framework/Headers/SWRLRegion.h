/*
 * SWRLRegion.h
 * Copyright 2015-2016 Swirl Networks, Inc. All Rights Reserved.
 */

#ifndef __SWRLREGION__
#define __SWRLREGION__

#import <Swirl/SWRLBase.h>
#import <Swirl/SWRLLocation.h>

/**
 * A SWRLRegion object represents a geofence.
 *
 */
@interface SWRLRegion : SWRLSignal
/**
 * An CLCircularRegion which provides
 * a center point (latitude and longitude) and a radius in meters which defines the area
 * covered by the region or an outer bounding area for regions which are further refined by an arbitrary
 * polygon.
 */
@property (nonatomic, readonly) CLCircularRegion *          region;

/**
 * For polygon regions, polyCount is the number of entries in the polyPoints array
 */
@property (nonatomic, readonly) NSInteger                   polyCount;

/**
 * For polygon regions, polyPoints is an array of polyCount coordinates that 
 * represent the vertices of the polygon that refines the circular bounding region
 */
@property (nonatomic, readonly) CLLocationCoordinate2D *    polyCoords;

/**
 * A string representing the type of region: control, geofence
 */
@property (nonatomic, readonly) NSString *                  regionType;


- (instancetype) initWithDictionary:(NSDictionary *)info;

/**
 * Determine if a given lattitude and longitude lie within the Region or not.
 *
 * @param coordinate A coordinate (latitude, longitude) to test for inclusion
 * @returns YES if the coordinate is contained with in the bounding region and where
 * specified the arbitrary polygon within, NO otherwise.
 */
- (BOOL) containsCoordinate:(CLLocationCoordinate2D)coordinate;

/**
 * Determine if a give location (plus tolerance) is within a circular region.
 * Polygon regions will default to strict containment.
 *
 * @param location to test
 * @param accuracy maximum tolerance to allow (accuracy of the location will be used, clipped to this value)
 * @returns YES if within the region, NO otherwise
 */
- (BOOL) containsLocation:(CLLocation *)location accuracy:(CLLocationDistance)accuracy;

/**
 * Determine the distance of a location to the region.
 * @param location The location to use in determining distance from the region.
 * @returns The distance from the region, negative values are inside the region.
 */
- (double) distanceFromLocation:(CLLocation *)location;


- (void) setLastDetected:(NSTimeInterval)ts;

@end

extern NSString *const SWRLRegionPrefix; // com.swirl.region.

#endif

