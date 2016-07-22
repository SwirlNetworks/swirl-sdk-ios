//
//  SWRLWifiManager.h
//  Swirl
//
//  Created by Thomas Middleton on 5/13/16.
//
//

#import <Foundation/Foundation.h>
#import <Swirl/SWRLManager.h>
#import <Swirl/SWRLLocation.h>

/**
 * Represents a wifi signal.
 */

@interface SWRLWifiInfo : SWRLSignal
/** SSID */
@property (nonatomic, readonly) NSString *          name;
/** Location (and Placement) associated with this wifi network */
@property (nonatomic, readonly) SWRLLocation *      location;
/** Signal strength (if available) */
@property (nonatomic, readonly) int                 rssi;
/** Timestamp (unix-epoch) of when the network was first detected */
@property (nonatomic, readonly) NSTimeInterval      detected;
/** Attributes associated to this network via the platform */
@property (nonatomic, readonly) NSDictionary *      attributes;
/** Labels associated to this network via the platform */
@property (nonatomic, readonly) NSArray<NSString*> *labels;
/** Error (if present) */
@property (nonatomic, readonly) NSError *           error;

- (BOOL) isResolved;
@end

/**
 * Component which manages detecting and responding to wifi network changes.
 */
@interface SWRLWifiManager : SWRLManager
@end

/**
 * Callbacks for the WifiManager.
 */
@protocol SWRLWifiManagerDelegate <NSObject>
@optional
/** 
 * Sent when an access point enter is detected for the connected wifi network
 * @param manager The WifiManager
 * @param wifi The WifiInfo object
 */
- (void) wifiManager:(SWRLWifiManager *)manager didEnterWifi:(SWRLWifiInfo *)wifi;
/** 
 * Sent when an accesspoint exit is detected for the connected wifi network
 * @param manager The WifiManager
 * @param wifi the WifiInfo object
 */
- (void) wifiManager:(SWRLWifiManager *)manager didExitWifi:(SWRLWifiInfo *)wifi;
@end
