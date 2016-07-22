//
//  SWRRegion.h
//  Swirl
//
//  Created by Thomas Middleton on 10/29/15.
//
//

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
 * A logical Location and Placement associated to this georegion through the platform.
 */
@property (nonatomic, readonly) SWRLLocation *              location;
/**
 * A set of property value pairs associated to this Location-Placement through the platform.
 */
@property (nonatomic, readonly) NSDictionary *              attributes;
/**
 * A set of labels assigned to this Location-Placement through the platform.
 */
@property (nonatomic, readonly) NSArray<NSString*> *        labels;
/**
 * A representation of the raw-JSON metadata that came from the server for this
 * region
 */
@property (nonatomic, readonly) NSDictionary *              info;

- (instancetype) initWithDictionary:(NSDictionary *)info;

/**
 * Determine if a given lattitude and longitude lie within the Region or not.
 *
 * @param coordinate A coordinate (latitude, longitude) to test for inclusion
 * @returns YES if the coordinate is contained with in the bounding region and where
 * specified the arbitrary polygon within, NO otherwise.
 */
- (BOOL) containsCoordinate:(CLLocationCoordinate2D)coordinate;

@end

