/*
 * SWRLVisit.h
 * Copyright 2015-2016 Swirl Networks, Inc. All Rights Reserved.
 */

#ifndef __SWRLVISIT__
#define __SWRLVISIT__

#import <Foundation/Foundation.h>
#import <Swirl/SWRLLocation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 *  A SWRLVisit object encapsulates information about places that the user has been. Visit objects are created by
 *  the framework and delivered by the SWRLVisitManager object to its delegate after it receives relevant signal events
 *  from other managers running within the framework.  It monitors the SWRLBeaconManagerDelegate, the SWRLWifiManagerDelegate
 *  and the SWRLRegionManagerDelegate for events related to locations and translates those events into logical visit
 *  events.
 *
 *  The visit includes the location where the visit occurred and information about the arrival and departure times as 
 *  relevant. You do not create visit objects directly, nor should you subclass a SWRLVisit.  You receive these objects
 *  by receiving delegate callbacks from the SWRLVisitManager. See SWRLVisitManagerDelegate.
 *
 *  Visit objects contain as much information about the visit as possible but may not always include both the arrival 
 *  and departure times. For example, when the user arrives at a location, the system may send an event with only an 
 *  arrival time. When the user departs a location, the event can contain both the arrival time 
 *  (if your app was monitoring visits prior to the user’s arrival) and the departure time.
 */

@interface SWRLVisit : NSObject
/** @name Accessing Location    */
/** The Location of the visit.  */
@property (nonatomic, readonly) SWRLLocation *		location;
/** The date of the most recent enter or distantPast if not entered. */
@property (nonatomic, readonly)	NSDate *			arrivalDate;
/** The date of the most recent exit or distantFuture if not yet exited */
@property (nonatomic, readonly)	NSDate *			departureDate;
/** The accumulated dwell across potentially multiple enters and exits */
@property (nonatomic, readonly) NSTimeInterval		dwellTime;
/** The total elapsed time since the first enter until now or the last exit time */
@property (nonatomic, readonly) NSTimeInterval      elapsedTime;

- (instancetype) initWithLocation:(SWRLLocation *)location visit:(nullable SWRLVisit *)visit;
- (instancetype) parentVisit;

- (NSTimeInterval) intervalSinceDeparture;

@end

NS_ASSUME_NONNULL_END

#endif
