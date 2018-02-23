/*
 * SWRLSettings.h
 * Copyright 2015-2016 Swirl Networks, Inc. All Rights Reserved.
 */
 

#ifndef __SWRLSETTINGS__
#define __SWRLSETTINGS__

#import <Foundation/Foundation.h>

extern NSString *const SWRLSettingApiAccessCode;            // API Access Code.  This is for temporary API access using a code
extern NSString *const SWRLSettingApiKey;                   // API Key.  This is the API key assigned through the platform 
extern NSString *const SWRLSettingApiSecret;                // API Secret.  This is the API secret assigned through the platform 
extern NSString *const SWRLSettingApiEnabled;               // API Enabled.  Failsafe used to disable the SDK remotely if necessary. Default:YES. 
extern NSString *const SWRLSettingApiHost;                  // API Host.  This is primarily used internally for switching between testing and live infrastrucures. 
extern NSString *const SWRLSettingApiPingEnabled;           // API Ping Enabled.  Default: YES 
extern NSString *const SWRLSettingApiPingWindow;            // API Ping Window.  Seconds over which to randomize device registration 
extern NSString *const SWRLSettingUserInfo;                 // UserInfo. This is the option which backs the userInfo property on Swirl. 
extern NSString *const SWRLSettingDeferredDelay;            // Delay in seconds, for deferred startup tasks
extern NSString *const SWRLSettingUseLocationFenced;        // Location detection in the SDK can use regions to detect location changes. Default is YES
extern NSString *const SWRLSettingUseLocationSignificant;   // Location detection in the SDK can use significant location change detection. Default is YES. 
extern NSString *const SWRLSettingLocationFenceMin;         // Minimium size of the userFence in meters. Default is 100.0 (if background location enabled), 10.0 otherwise
extern NSString *const SWRLSettingLocationFenceMax;         // Maximum size of the userFence in meters. Default is 5000.0
extern NSString *const SWRLSettingLocationActiveFenceMax;   // Maximum number of active geo-fences around user. Default is 0.
extern NSString *const SWRLSettingLocationMaxAccuracy;      // Maximum number of meters of fuzz to allow in location accuracy. Default is 0.
extern NSString *const SWRLSettingLocationForegroundGpsMin; // Minimum interval between GPS samples on foreground event (once per foreground). Default is 300.0 seconds
extern NSString *const SWRLSettingLocationHistory;          // An array of location change information. Mostly for debugging 
extern NSString *const SWRLSettingLocationHistoryMax;       // How many location changes to record. Default is 0 (location recording disabled) 
extern NSString *const SWRLSettingContentNotifications;     // Boolean allow notifications for content.  Default is YES. 
extern NSString *const SWRLSettingContentDelay;             // Minimum number of seconds allowed between notification delivery. Default is 30.0 
extern NSString *const SWRLSettingContentLoadDelay;         // Number of seconds to preload before showing content default is 5.0
extern NSString *const SWRLSettingContentSpinnerTimeout;    // Default timeout for loading spinner. Default is 5.0 seconds
extern NSString *const SWRLSettingContentTimeout;           // Default expiration for content that was received, but not yet displayed. Default is 900.0 seconds
extern NSString *const SWRLSettingContentCode;              // If content is being requested with a demo or content code.
extern NSString *const SWRLSettingContentUseFullScreen;     // Use extended areas on larger phones. Default YES.
extern NSString *const SWRLSettingContentShowToast;         // Boolean that controls whether or not to show the content toast view when content is dismissed. 
extern NSString *const SWRLSettingContentShowToastFirst;    // Boolean that controls whether or not to show the content toast before showing the full view. 
extern NSString *const SWRLSettingContentShowToolbar;       // Boolean that controls whether or not to show the content toolbar. 
extern NSString *const SWRLSettingBeaconFilter;             // Comma separated list of mac-addresses to allow through. Testing. 
extern NSString *const SWRLSettingBeaconScanGeneric;        // Controls whether all beacons (including unknown protocols) are reflected to server (Default:NO) 
extern NSString *const SWRLSettingBeaconThreshold;          // Global RSSI threshold.  Default: -105 
extern NSString *const SWRLSettingBeaconScanInterval;       // Default scan interval when scanning for beacons. Default is 3.0 
extern NSString *const SWRLSettingBeaconRestInterval;       // Default rest interval when scanning for beacons. Default is 2.0 
extern NSString *const SWRLSettingBeaconOptSampleInterval;  // Optimal interval for rssi averaging. Default is 20.0 
extern NSString *const SWRLSettingBeaconMaxSampleInterval;  // Maximum interval for rssi averaging (if can't get enought samples). Default is 60.0 
extern NSString *const SWRLSettingBeaconMinSamples;         // Minimum required samples to return a value. Default is 2 
extern NSString *const SWRLSettingBeaconSampleResolution;   // Update frequency of cached rssi values in seconds. Default is 1.0 
extern NSString *const SWRLSettingBeaconScanAlways;         // Force beacon scan to run always (regardless of location permissions, Default is NO 
extern NSString *const SWRLSettingBeaconProximityCheck;     // Boolean to control whether or not to run the beacon proximity check. Default is YES 
extern NSString *const SWRLSettingBeaconServicesAlways;     // Comma separated list of services to scan for. Default is FEEB,FEAA (securecast, eddystone) 
extern NSString *const SWRLSettingBeaconServices;           // List of region based service ids. Varies by Region. 
extern NSString *const SWRLSettingBeaconUuidsAlways;        // Comma separated list of UUIDs to always listen for (ibeacon). By default contains 2 Swirl UUIDs.
extern NSString *const SWRLSettingBeaconUuids;              // List of region based iBeacon UUIDS. Varies by region.
extern NSString *const SWRLSettingBeaconMaxUuids;           // Number of UUIDs to monitor (max number of shared CLBeaconRegions to use). Default is 5.
extern NSString *const SWRLSettingBeaconNamespaces;         // List of region based Eddystone UID namespaces. Varies by region.
extern NSString *const SWRLSettingBeaconNamespacesAlways;   // Comma separated list of hexstring namespaces. Default is Swirl Namespace.
extern NSString *const SWRLSettingBeaconResolveIBeacon;     // Flag to control if Ibeacons are resolved with swirl backend. Default:YES 
extern NSString *const SWRLSettingBeaconResolveEddystoneEID;// Flag to control if Eddystone EID beacons are resolved with swirl backend. Default:NO 
extern NSString *const SWRLSettingBeaconResolveEddystoneUID;// Flag to control if Eddystone UID beacons are resolved with swirl backend. Default:YES
extern NSString *const SWRLSettingBeaconExpiration;         // Interval to control how long before idle beacon removed from internal tables. Default:MINUTES(16) 
extern NSString *const SWRLSettingLastResetTime;            // Time of last reset/settings initialization 
extern NSString *const SWRLSettingConfigEnabled;            // Enable administration/configuration: connect to beacons, include errored beacons, etc 
extern NSString *const SWRLSettingConfigBeaconServices;     // Comma separated list of additional configuration services to scan for.  Default is FFC0 
extern NSString *const SWRLSettingGoogleBeaconApiKey;       // Google Proximity Beacon API Key
extern NSString *const SWRLSettingUseNewNotifications;      // Use new UserNotification framework (default NO)

extern NSString *const SWRLSettingsDidChangeNotification;
extern NSString *const SWRLSettingsDefaultsChanged;
extern NSString *const SWRLSettingsChangedKeys;

/**
 *  SWRLSettings is a singleton that is initialized by the SWRLAPI.  It is local encrypted storage for
 *  the all of the swirl files and settings.
 *
 *  For the most part, you do not need to interact directly with this class, but you can use it to
 *  set options at points other thant Swirl start:.
 * 
 *  See SWRLSettings.h for a description of currently exposed options.
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

