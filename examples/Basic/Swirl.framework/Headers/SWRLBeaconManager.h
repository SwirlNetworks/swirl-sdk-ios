/*
 *  SWRLBeaconManager.h
 *	Copyright 2015-2016 Swirl Networks, Inc. All rights reserved.
 */

#ifndef __SWRLBEACONMANAGER__
#define __SWRLBEACONMANAGER__

#import <Swirl/SWRLManager.h>
#import <Swirl/SWRLBeacon.h>
#import <Swirl/SWRLBeaconScanner.h>

NS_ASSUME_NONNULL_BEGIN

@protocol SWRLBeaconManagerDelegate;

/// The SWRLBeaconManager class is instantiated by the framework to coordinate and manage SWRLBeacons.  An instance
/// of this class is created when the framework is initialized and started when the SWRLSwirl start: is called.
/// For the most part, you do not need to interact with this class directly.  If you are interested in beacon level
/// events and transitions, then you would add a delegate through the Swirl class and implement delegate methods.
/// For information about the delegate methods you use to receive events, see SWRLBeaconManagerDelegate.

@interface SWRLBeaconManager : SWRLManager<SWRLBeaconScannerDelegate>
/// @name Accessing Beacon Manager State

/// The beacon currently determined to be closest to the mobile device.
@property (nonatomic, readonly, nullable) SWRLBeacon *              nearest;

/// All of the beacons currently managed by the beacon manager, including beacons that may be in an error state.
@property (nonatomic, readonly, nullable) NSArray<SWRLBeacon*> *    beacons;
@end

/// The SWRLBeaconManager protocol defines the methods used to receive beacon update from the SWRLBeaconManager.
/// Upon receiving a beacon event, you can use the result to update your user interface or
/// perform other actions.
/// <p>
/// The methods of your delegate object are called from the thread associated with the dispatch queue that you used
/// when you added the delegate. See [addDelegate:queue:](SWRLSwirl addDelegate:queue:)

@protocol SWRLBeaconManagerDelegate <NSObject>
@optional
/**
 *  Tells the delegate that the beacon manager was able to resolve the beacon.
 *
 *  @param manager  The SWRLBeaconManager reporting the event
 *  @param beacon   The resolved beacon
 */
- (void) beaconManager:(SWRLBeaconManager *)manager didResolveBeacon:(SWRLBeacon *)beacon;

/// Tells the delegate that the mobile device is within range of the beacon.
/// @param manager The SWRLBeaconManager reporting the event
/// @param beacon The beacon that has been entered
- (void) beaconManager:(SWRLBeaconManager *)manager didEnterBeacon:(SWRLBeacon *)beacon;
/// Tells the delegate that the mobile device changed the beacon it is closest to.
/// @param manager The SWRLBeaconManager reporting the event
/// @param beacon The beacon that is now the nearest beacon
- (void) beaconManager:(SWRLBeaconManager *)manager didChangeNearest:(SWRLBeacon *)beacon;
/// Tells the delegate that the mobile device is still within range of the beacon.  Called periodically.
/// @param manager The SWRLBeaconManager reporting the event
/// @param beacon The beacon that the mobile device is within range of
- (void) beaconManager:(SWRLBeaconManager *)manager didDwellBeacon:(SWRLBeacon *)beacon;
/// Tells the delegate that the mobile device left the range of the beacon.
/// @param manager The SWRLBeaconManager reporting the event
/// @param beacon The beacon that was exited
- (void) beaconManager:(SWRLBeaconManager *)manager didExitBeacon:(SWRLBeacon *)beacon;
@end

NS_ASSUME_NONNULL_END

#endif

