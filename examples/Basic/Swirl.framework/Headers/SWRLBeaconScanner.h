/*
 *  SWRLBeaconScanner.h
 *	Copyright 2015-2016 Swirl Networks, Inc. All rights reserved.
 */

#ifndef __SWRLBEACONSCANNER__
#define __SWRLBEACONSCANNER__

#import <Foundation/Foundation.h>
#import <Swirl/SWRLManager.h>
#import <Swirl/SWRLBeaconAdvertisement.h>

NS_ASSUME_NONNULL_BEGIN

@interface  SWRLBeaconScanner : SWRLManager
- (void) squelchBeaconAdvertisement:(SWRLBeaconAdvertisement *)advertisement expiration:(NSTimeInterval)expiration;
@end

/**
 * The SWRLBeaconScannerDelegate protocol is how the built in beacon scanners communicate discovered beacons to the rest
 * of the system.
 */

@protocol SWRLBeaconScannerDelegate <NSObject>
- (void) beaconScanner:(nullable SWRLBeaconScanner *)scanner didDetectBeaconAdvertisement:(SWRLBeaconAdvertisement *)advertisement;
@end

/**
 * The SWRLIBeaconScanner is a beacon scanner that uses the BeaconRegion monitoring APIs on CLLocationManager to monitor for
 * iBeacon regions.  The scanner listens primarily for UUIDS and will consume one of the shared CLRegion spots for each UUID monitored.
 * By default, the SWRIL UUID is monitored, but this can be altered through Settings. If the SWRLRegionManager is being used, then
 * it can provide additional UUIDS to monitor on a region by region basis.
 */
@interface SWRLIBeaconScanner   : SWRLBeaconScanner @end

/** 
 * The SWRLBluetoothScanner is a beacon scanner that uses the CoreBluetooth APIs to scan for BLE advertisements and reports
 * those advertisements to the rest of the system.  By default, the scanner monitors for FEEB and FEAA service types which 
 * correspond to SecureCast and Eddystone respectively.  The set of protocols to scan for can be customized through Settings.
 */

@interface SWRLBluetoothScanner : SWRLBeaconScanner @end

NS_ASSUME_NONNULL_END

#endif
