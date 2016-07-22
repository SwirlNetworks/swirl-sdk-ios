/*!
 *	@file SWRBeaconManager.h
 *	@framework Swirl
 *  @discussion Beacon Manager and related classes.
 *	@copyright 2015 Swirl Networks, Inc. All rights reserved.
 */

#ifndef __SWRLBEACONMANAGER__
#define __SWRLBEACONMANAGER__

#import <Swirl/SWRLManager.h>
#import <Swirl/SWRLBeacon.h>
#import <Swirl/SWRLBeaconScanner.h>

NS_ASSUME_NONNULL_BEGIN

@protocol SWRLBeaconManagerDelegate;

@interface SWRLBeaconManager : SWRLManager<SWRLBeaconScannerDelegate>
@property (nonatomic, readonly, nullable) SWRLBeacon *              nearest;
@property (nonatomic, readonly, nullable) NSArray<SWRLBeacon*> *    beacons;
@end

@protocol SWRLBeaconManagerDelegate <NSObject>
@optional
- (void) beaconManager:(SWRLBeaconManager *)manager didResolveBeacon:(SWRLBeacon *)beacon;
- (void) beaconManager:(SWRLBeaconManager *)manager didEnterBeacon:(SWRLBeacon *)beacon;
- (void) beaconManager:(SWRLBeaconManager *)manager didChangeNearest:(SWRLBeacon *)beacon;
- (void) beaconManager:(SWRLBeaconManager *)manager didDwellBeacon:(SWRLBeacon *)beacon;
- (void) beaconManager:(SWRLBeaconManager *)manager didExitBeacon:(SWRLBeacon *)beacon;
@end

NS_ASSUME_NONNULL_END

#endif

