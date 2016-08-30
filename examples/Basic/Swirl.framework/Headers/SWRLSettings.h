/*
 * SWRLSettings.h
 * Copyright 2015-2016 Swirl Networks, Inc. All Rights Reserved.
 */

#ifndef __SWRLSETTINGS__
#define __SWRLSETTINGS__

#import <Foundation/Foundation.h>

extern NSString *const SWRLSettingApiKey;
extern NSString *const SWRLSettingApiHost;
extern NSString *const SWRLSettingUserInfo;
extern NSString *const SWRLSettingUseIDFA;
extern NSString *const SWRLSettingUseLocationFenced;
extern NSString *const SWRLSettingUseLocationSignificant;
extern NSString *const SWRLSettingLocationFenceMin;
extern NSString *const SWRLSettingLocationFenceMax;

extern NSString *const SWRLSettingContentNotifications;
extern NSString *const SWRLSettingContentDelay;
extern NSString *const SWRLSettingContentShowDelay;
extern NSString *const SWRLSettingContentTimeout;
extern NSString *const SWRLSettingContentLoadingTimeout;
extern NSString *const SWRLSettingContentCode;
extern NSString *const SWRLSettingContentShowToast;

extern NSString *const SWRLSettingBeaconFilter;
extern NSString *const SWRLSettingBeaconScanInterval;
extern NSString *const SWRLSettingBeaconRestInterval;
extern NSString *const SWRLSettingBeaconProximityCheck;
extern NSString *const SWRLSettingBeaconServicesAlways;
extern NSString *const SWRLSettingBeaconServices;
extern NSString *const SWRLSettingBeaconUuidsAlways;
extern NSString *const SWRLSettingBeaconUuids;

extern NSString *const SWRLSettingsDidChangeNotification;
extern NSString *const SWRLSettingsDefaultsChanged;
extern NSString *const SWRLSettingsChangedKeys;


@interface SWRLSettings : NSObject
@property (nonatomic, readonly) NSDictionary *allSettings;

- (instancetype)initWithPath:(NSString *)path prefix:(NSString *)name;

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

