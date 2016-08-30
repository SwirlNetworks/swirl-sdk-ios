/*
 * SWRLVisitManager.h
 * Copyright 2015-2016 Swirl Networks, Inc. All Rights Reserved.
 */

#ifndef __SWRLVISITMANAGER__
#define __SWRLVISITMANAGER__

#import <Foundation/Foundation.h>
#import <Swirl/SWRLManager.h>
#import <Swirl/SWRLVisit.h>

/**
 * A component which consumes the various Enter/Exit/Dwell events from the signal detectors and tracks enter and exit times, 
 * accumulates dwell and elapsed times by location and placement, and generates logical Visit objects and 
 * delegate callbacks Visit start, dwell and end.
 */
@interface SWRLVisitManager : SWRLManager
/**
 * Gets current or most recent visit whether active or inactive.
 * \returns most recent visit
 */
- (SWRLVisit *)          recentVisit;

/**
 * Gets all active (started and not ended) Location Visits sorted by signal and distance from most-specific and nearest 
 * to least-specific and farthest.  The sort order is Beacon, Wifi, Region and by distance where possible within each type.
 * \returns Array of Location Visits that are not ended
 */
- (NSArray<SWRLVisit*>*) activeLocationVisits;
/**
 * Gets all active (started and not ended) Placement Visits sorted by signal and distance from most-specific and nearest
 * to least-specific and farthest.  The sort order is Beacon, Wifi, Region and by distance where possible within each type.
 * \returns Array of Placement Visits that are not ended
 */
- (NSArray<SWRLVisit*>*) activePlacementVisits;
@end

/**
 *  Callbacks from the VisitManager for events around Visits
 */
@protocol SWRLVisitManagerDelegate <NSObject>
@optional
/**
 * Called when a Visit to a new Location and Placement is beginnng
 * @param manager VisitManager
 * @param visit Visit object which contains information on start, end and accumulated and elapsed dwell time
 */
- (void) visitManager:(SWRLVisitManager *)manager didBeginVisit:(SWRLVisit *)visit;
/**
 * Called periodically as a user remains in a current Location and Placement
 * @param manager VisitManager
 * @param visit Visit object which contains information on start, end and accumulated and elapsed dwell time
 */
- (void) visitManager:(SWRLVisitManager *)manager didUpdateDwellForVisit:(SWRLVisit *)visit;
/**
 * Called when a Visit to a new Location and Placement has ended
 * @param manager VisitManager
 * @param visit Visit object which contains information on start, end and accumulated and elapsed dwell time
 */
- (void) visitManager:(SWRLVisitManager *)manager didEndVisit:(SWRLVisit *)visit;
@end

#endif