/*
 * SWRLRegionManager.h
 * Copyright 2015-2016 Swirl Networks, Inc. All Rights Reserved.
 */

#ifndef __SWRLREGIONMANAGER__
#define __SWRLREGIONMANAGER__

#import <Foundation/Foundation.h>
#import <Swirl/SWRLManager.h>
#import <Swirl/SWRLRegion.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * A component which manages a working set of Region objects (retreived using the API) that are 'near' the users location. 
 * These regions represent both geofences and 'control' regions. Geofences have logical location, placement and other metadata associated. 
 * Control regions are used internally by the SDK to control other signal detection, like when to start and stop scanning for beacons or what 
 * iBeacon UUIDs are nearby. This component either starts its own os specific location manager or depends upon the host app 
 * to post location information onto the bus. It generates RegionEnter/RegionExit events onto the bus.
 */

@interface SWRLRegionManager : SWRLManager
@property (nonatomic, copy, readonly) SWRLRegion *monitoredArea;
@property (nonatomic, copy, readonly) NSArray<SWRLRegion*> *monitoredRegions;
@property (nonatomic, copy, readonly) NSArray<SWRLRegion*> *enteredRegions;

- (void) start;
- (void) stop;

+ (SWRLRegionManager *)shared;
@end

/**
 * Callbacks from the SWRLRegionManager
 *
 */
@protocol SWRLRegionManagerDelegate <NSObject>
@optional
/**
 * Called whenever the set of entered and/or exited regions changes
 * @param manager The SWRLRegionManager
 * @param entered A set of SWRLRegions representing the regions that have been entered
 * @param exited A set of SWRLRegions representing the regions that have been exited
 */
- (void) regionManager:(SWRLRegionManager *)manager didEnterRegions:(NSSet<SWRLRegion*> *)entered exitRegions:(NSSet<SWRLRegion*>*)exited;
@end

NS_ASSUME_NONNULL_END

#endif

