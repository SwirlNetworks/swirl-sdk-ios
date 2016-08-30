//
//  SWRLBeaconScanner.h
//  Swirl
//
//
//

#ifndef __SWRLBEACONSCANNER__
#define __SWRLBEACONSCANNER__

#import <Foundation/Foundation.h>
#import <Swirl/SWRLManager.h>
#import <Swirl/SWRLBeaconAdvertisement.h>

NS_ASSUME_NONNULL_BEGIN

@interface  SWRLBeaconScanner : SWRLManager
- (void) squelchBeaconAdvertisement:(SWRLBeaconAdvertisement *)advertisement expiration:(NSTimeInterval)expiration;
@end

@protocol SWRLBeaconScannerDelegate <NSObject>
- (void) beaconScanner:(nullable SWRLBeaconScanner *)scanner didDetectBeaconAdvertisement:(SWRLBeaconAdvertisement *)advertisement;
@end

@interface SWRLIBeaconScanner   : SWRLBeaconScanner @end
@interface SWRLBluetoothScanner : SWRLBeaconScanner @end

NS_ASSUME_NONNULL_END

#endif
