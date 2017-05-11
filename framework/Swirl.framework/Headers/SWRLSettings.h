/*
 * SWRLSettings.h
 * Copyright 2015-2016 Swirl Networks, Inc. All Rights Reserved.
 */

#ifndef __SWRLSETTINGS__
#define __SWRLSETTINGS__

#import <Foundation/Foundation.h>

/** @name Settings */

/** API Access Code.  This is for temporary API access using a code */
extern NSString *const SWRLSettingApiAccessCode;
/** API Key.  This is the API key assigned through the platform */
extern NSString *const SWRLSettingApiKey;
/** API Secret.  This is the API secret assigned through the platform */
extern NSString *const SWRLSettingApiSecret;
/** API Enabled.  Failsafe used to disable the SDK remotely if necessary. Default:YES. */
extern NSString *const SWRLSettingApiEnabled;
/** API Host.  This is primarily used internally for switching between testing and live infrastrucures. */
extern NSString *const SWRLSettingApiHost;
/** API Ping Enabled.  Default: YES */
extern NSString *const SWRLSettingApiPingEnabled;
/** API Ping Window.  Seconds over which to randomize device registration */
extern NSString *const SWRLSettingApiPingWindow;
/** UserInfo. This is the option which backs the userInfo property on Swirl. */
extern NSString *const SWRLSettingUserInfo;
/** Allow the SDK to use IDFAs.  The default is YES. */
extern NSString *const SWRLSettingUseIDFA;
/** Location detection in the SDK can use regions to detect location changes. Default is YES */
extern NSString *const SWRLSettingUseLocationFenced;
/** Location detection in the SDK can use significant location change detection. Default is NO. */
extern NSString *const SWRLSettingUseLocationSignificant;
/** Minimium size of the userFence in meters. Default is 30.0 */
extern NSString *const SWRLSettingLocationFenceMin;
/** Maximum size of the userFence in meters. Default is 5000.0 */
extern NSString *const SWRLSettingLocationFenceMax;
/** Minimum interval between GPS samples on foreground event (once per foreground). Default is 300.0 seconds */
extern NSString *const SWRLSettingLocationForegroundGpsMin;
/** An array of location change information. Mostly for debugging */
extern NSString *const SWRLSettingLocationHistory;
/** How many location changes to record. Default is 0 (location recording disabled) */
extern NSString *const SWRLSettingLocationHistoryMax;
/** Boolean allow notifications for content.  Default is YES. */
extern NSString *const SWRLSettingContentNotifications;
/** Minimum number of seconds allowed between notification delivery. Default is 30.0 */
extern NSString *const SWRLSettingContentDelay;
/** Number of additional seconds to hold content after loading is complete. Default is 2.0 */
extern NSString *const SWRLSettingContentShowDelay;
/** Default expiration for content that was received, but not yet displayed. Default is 900.0 seconds */
extern NSString *const SWRLSettingContentTimeout;
/** Default timeout for loading spinner. Default is 15.0 seconds */
extern NSString *const SWRLSettingContentLoadingTimeout;
/** If content is being requested with a demo or content code. */
extern NSString *const SWRLSettingContentCode;
/** Boolean that controls whether or not to show the content toast view when content is dismissed. */
extern NSString *const SWRLSettingContentShowToast;
/** Boolean that controls whether or not to show the content toast before showing the full view. */
extern NSString *const SWRLSettingContentShowToastFirst;
/** Boolean that controls whether or not to show the content toolbar. */
extern NSString *const SWRLSettingContentShowToolbar;
/** Comma separated list of mac-addresses to allow through. Testing. */
extern NSString *const SWRLSettingBeaconFilter;
/** Controls whether all beacons (including unknown protocols) are reflected to server (Default:NO) */
extern NSString *const SWRLSettingBeaconScanGeneric;
/** Global RSSI threshold.  Default: -95 */
extern NSString *const SWRLSettingBeaconThreshold;
/** Default scan interval when scanning for beacons. Default is 3.0 */
extern NSString *const SWRLSettingBeaconScanInterval;
/** Default rest interval when scanning for beacons. Default is 2.0 */
extern NSString *const SWRLSettingBeaconRestInterval;
/** Optimal interval for rssi averaging. Default is 20.0 */
extern NSString *const SWRLSettingBeaconOptSampleInterval;
/** Maximum interval for rssi averaging (if can't get enought samples). Default is 60.0 */
extern NSString *const SWRLSettingBeaconMaxSampleInterval;
/** Minimum required samples to return a value. Default is 2 */
extern NSString *const SWRLSettingBeaconMinSamples;
/** Update frequency of cached rssi values in seconds. Default is 1.0 */
extern NSString *const SWRLSettingBeaconSampleResolution;
/** Force beacon scan to run always (regardless of location permissions, Default is NO */
extern NSString *const SWRLSettingBeaconScanAlways;
/** Boolean to control whether or not to run the beacon proximity check. Default is YES */
extern NSString *const SWRLSettingBeaconProximityCheck;
/** Comma separated list of services to scan for. Default is FEEB,FEAA (securecast, eddystone) */
extern NSString *const SWRLSettingBeaconServicesAlways;
/** List of region based service ids. Varies by Region. */
extern NSString *const SWRLSettingBeaconServices;
/** Comma separated list of UUIDs to always listen for (ibeacon). Default is 0c900860-7e44-9182-186d-5c49ad933f81 (Swirl UUID). */
extern NSString *const SWRLSettingBeaconUuidsAlways;
/** List of region based iBeacon UUIDS. Varies by region. */
extern NSString *const SWRLSettingBeaconUuids;
/** Maximum number of IBeacon UUIDs to monitor. Default: 10 */
extern NSString *const SWRLSettingBeaconMaxUuids;
/** Flag to control if Ibeacons are resolved with swirl backend. Default:YES */
extern NSString *const SWRLSettingBeaconResolveIBeacon;
/** Flag to control if Eddystone EID beacons are resolved with swirl backend. Default:NO */
extern NSString *const SWRLSettingBeaconResolveEddystoneEID;
/** Flag to control if Eddystone UID beacons are resolved with swirl backend. Default:NO */
extern NSString *const SWRLSettingBeaconResolveEddystoneUID;
/** Interval to control how long before idle beacon removed from internal tables. Default:MINUTES(16) */
extern NSString *const SWRLSettingBeaconExpiration;
/** Time of last reset/settings initialization */
extern NSString *const SWRLSettingLastResetTime;
/** Enable administration/configuration: connect to beacons, include errored beacons, etc */
extern NSString *const SWRLSettingConfigEnabled;
/** Comma separated list of additional configuration services to scan for.  Default is FFC0 */
extern NSString *const SWRLSettingConfigBeaconServices;
/** Google Proximity Beacon API Key */
extern NSString *const SWRLSettingGoogleBeaconApiKey;

extern NSString *const SWRLSettingsDidChangeNotification;
extern NSString *const SWRLSettingsDefaultsChanged;
extern NSString *const SWRLSettingsChangedKeys;

/**
 * SWRLSettings is a singleton that is initialized by the SWRLAPI.  It is local encrypted storage for
 * the all of the swirl files and settings.
 * 
 * For the most part, you do not need to interact directly with this class, but you can use it to
 * set options at points other thant Swirl start:.
 *
 * See Settings for a description of currently exposed options.
 */

@interface SWRLSettings : NSObject
@property (nonatomic, readonly) NSDictionary *allSettings;

- (NSString *) stringForKey:(NSString *)key default:(NSString *)value;
- (BOOL) boolForKey:(NSString *)key default:(BOOL)value;
- (int)  intForKey:(NSString *)key default:(int)value;
- (double) doubleForKey:(NSString *)key default:(double)value;
- (NSTimeInterval)intervalForKey:(NSString *)key default:(NSTimeInterval)value;
- (NSArray *)arrayForKey:(NSString *)key default:(id)value;
- (NSDictionary *)dictionaryForKey:(NSString *)key default:(NSDictionary *)value;

- (instancetype) setAll:(NSDictionary *)keyValues;
- (instancetype) setValue:(id)value forKey:(NSString *)key;
- (instancetype) setArray:(NSArray *)value forKey:(NSString *)key allowEmpty:(BOOL)allowEmpty;
- (instancetype) remove:(NSString *)key;
- (instancetype) setDefaults:(NSDictionary *)defaultValues;

- (id)	 loadObjectForKey:(NSString *)key;
- (BOOL) storeObject:(id)object forKey:(NSString *)key;
- (BOOL) removeObjectForKey:(NSString *)key;
- (NSArray<NSString*>*)objectKeysWithPrefix:(NSString *)prefix;
- (NSUInteger)objectSizeForKey:(NSString *)key;

- (BOOL) storeImage:(UIImage *)image quality:(float)quality forKey:(NSString *)key;
- (UIImage *)loadImageForKey:(NSString *)key;

- (void) commit;
- (void) reset;

+ (instancetype)shared;
@end

#endif

