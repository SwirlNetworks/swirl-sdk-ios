/*
 * SWRLWifiManager.h
 * Copyright 2015-2016 Swirl Networks, Inc. All Rights Reserved.
 */

#ifndef __SWRLWIFIMANAGER__
#define __SWRLWIFIMANAGER__

#import <Foundation/Foundation.h>
#import <Swirl/SWRLManager.h>
#import <Swirl/SWRLLocation.h>

/**
 *  A SWRLWifiInfo object is a SWRLSignal which represents a wifi access point that the mobile device is or was
 *  connected to.  In order to activate detection, the SSIDs of the networks you are interested in need to be
 *  white-listed in the platform and all of the BSSIDs need to be added.  Any wifi events not related to the white-listed
 *  SSIDs and listed BSSIDs are not reported.
 */

@interface SWRLWifiInfo : SWRLSignal
/** ====================================================================================================================
 *  @name Accessing Attributes
 *  ====================================================================================================================
 */

/** 
 * The Signal strength (if available) associated with the detection event. 
 */
@property (nonatomic, readonly) int rssi;

@end

/**
 *  An instance of the SWRLWifiManager class is instantiated by the framework and started when Swirl is started.  For the
 *  most part, you do not interact directly with this class.  If you are interested in receiving wifi related events, then
 *  you use the addDelegate: method on Swirl to add an object which implements some or all of the methods in the
 *  SWRLWifiManagerDelegate.
 */
@interface SWRLWifiManager : SWRLManager
@end

/**
 *  The SWRLWifiManagerDelegate protocol defines methods used to receive updates about wifi network events from the SWRLWifiManager.
 *  Upon receiving these events, you can use the result to update your user interface or take other actions.
 *
 *  The methods of your delegate object are called from the thread associated with the dispatch queue that you used when you added the
 *  delegate. See addDelegate:queue:
 */
@protocol SWRLWifiManagerDelegate <NSObject>
@optional
/** 
 * Tells the delegate that an access point enter is detected for the connected wifi network
 * @param manager The WifiManager reporting the event
 * @param wifi The WifiInfo object representing the entered access point
 */
- (void) wifiManager:(SWRLWifiManager *)manager didEnterWifi:(SWRLWifiInfo *)wifi;
/**
 * Tells the delegate that the user has dwelled in a wifi network
 * @param manager The WifiManager reporting the event
 * @param wifi The WifiInfo object representing the entered access point
 */
- (void) wifiManager:(SWRLWifiManager *)manager didDwellWifi:(SWRLWifiInfo *)wifi;
/**
 * Tells the delegate than an access point exit is detected for the connected wifi network
 * @param manager The WifiManager reporting the event
 * @param wifi the WifiInfo object representing the exited access point
 */
- (void) wifiManager:(SWRLWifiManager *)manager didExitWifi:(SWRLWifiInfo *)wifi;
@end

#endif
