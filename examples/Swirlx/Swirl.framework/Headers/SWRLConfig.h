/*
 * SWRLConfig.h
 * Copyright 2015-2017 Swirl Networks, Inc. All Rights Reserved.
 */

#ifndef __SWRLCONFIG__
#define __SWRLCONFIG__

#import <Foundation/Foundation.h>
#import <Swirl/SWRLObject.h>
#import <Swirl/SWRLLocation.h>
#import <Swirl/SWRLBeacon.h>
#import <Swirl/SWRLBeaconManager.h>

@class SWRLPartner;
@class SWRLLocation_Config;
@class SWRLBeacon_Config;
@class SWRLBeaconHandler;

// =====================================================================================================================
// Config
// =====================================================================================================================

/* Beacon state relative to current threshold set for the beacon. */
typedef enum  {
    SWRLConfigProgressFirmware  = 1,
    SWRLConfigProgressConfiguration,
    SWRLConfigProgressPlacement,
    SWRLConfigProgressFloorplan,
    SWRLConfigProgressImages
} SWRLConfigProgress;

@interface SWRLConfig : NSObject
+ (void) setDefaultQueue:(dispatch_queue_t)queue;
+ (void) jsonRequest:(NSString *)url body:(NSDictionary *)body completion:(void (^)(int,NSDictionary *, NSError *))completion;

+ (SWRLBeaconHandler *) beaconHandlerForManufacturer:(NSString *)manufacturer;
+ (void) setBeaconHandler:(SWRLBeaconHandler *)handler forManufacturer:(NSString *)manufacturer;
@end

// =====================================================================================================================
// User
// =====================================================================================================================

extern NSString * const SWRLRoleBeaconManager_Read;
extern NSString * const SWRLRoleBeaconManager_Write;

@interface SWRLUser : SWRLObject
@property (nonatomic, readonly) BOOL isAdmin;
@property (nonatomic, readonly) BOOL hasAdminRole;
@property (nonatomic, readonly) NSArray<SWRLPartner*> *partners;

- (NSArray<SWRLPartner*>*)partnersWithRoles:(NSArray<NSString*>*)roles;
- (BOOL) hasRoles:(NSArray<NSString*>*)roles forPartner:(SWRLPartner *)partner;

- (void) load:(void(^)(NSError *))completion;

+ (void) loginWithEmail:(NSString *)email password:(NSString *)password completion:(void (^)(SWRLUser *, NSError *))completion;

@end

// =====================================================================================================================
// Beacon Firmware
// =====================================================================================================================

/**
 * SWRLBeaconFirmware
 *
 * A SWRLBeaconFirmare object represents metadata and actual binary firmware for downloading to
 * a beacon device.
 *
 * This class is not yet released as part of a public API.
 */

@interface SWRLBeaconFirmware : SWRLObject
@property (nonatomic, readonly) NSString *manufacturer;
@property (nonatomic, readonly) NSString *model;
@property (nonatomic, readonly) NSString *version;
@property (nonatomic, readonly) NSString *notes;
@property (nonatomic, readonly) NSData *data;

- (instancetype)initWithDictionary:(NSDictionary *)properties data:(NSData *)data;

- (float) versionNum;

- (void) load:(void (^)(NSError *))completion;

- (void) download:(SWRLPeripheral *)peripheral completion:(void (^)(NSError *))completion;

+ (void) firmwareAllVersions:(void (^)(NSArray<SWRLBeaconFirmware*>*, NSError *))completion;
+ (void) firmwareVersionsForManufacturer:(NSString *)manufacturer model:(NSString *)model completion:(void (^)(NSArray<SWRLBeaconFirmware*>*, NSError *))completion;
+ (void) firmwareLatestForManufacturer:(NSString *)manufacturer model:(NSString *)model completion:(void (^)(SWRLBeaconFirmware *, NSError *))completion;

@end

typedef NSDictionary<NSString*,NSDictionary*> SWRLBeaconConfigurationInfo;

@interface SWRLBeaconConfiguration : SWRLObject

+ (void) configurationsForPartner:(SWRLPartner *)partner completion:(void (^)(NSArray<SWRLBeaconConfiguration*> *, NSError *))completion;

@end

// =====================================================================================================================
// Partner
// =====================================================================================================================

@interface SWRLPartner : SWRLObject
@property (nonatomic, readonly) BOOL isActive;
@property (nonatomic, readonly) NSString *accessCode;
@property (nonatomic, readonly) NSArray<SWRLPlacement*> *placements;
@property (nonatomic, readonly) NSArray<SWRLLocation_Config*> *locations;

- (instancetype)initWithDictionary:(NSDictionary *)properties user:(SWRLUser *)user;
- (void) load:(void (^)(NSError *))completion;
@end

// =====================================================================================================================
// ImageMarker
// =====================================================================================================================

@interface SWRLImageMarker : NSObject
@property (nonatomic) double x;
@property (nonatomic) double y;
@property (nonatomic) double radius;

- (instancetype)initWithX:(double)x y:(double)y;
- (instancetype)initWithX:(double)x y:(double)y radius:(double)radius;
@end

// =====================================================================================================================
// Floorplan
// =====================================================================================================================

@interface SWRLFloorplan : SWRLObject

- (UIImage *) image;
- (int) height;
- (int) width;
- (SWRLLocation_Config *)location;
- (void) imageWithCompletion:(void (^)(UIImage *image, NSError *error))completion;

@end

// =====================================================================================================================
// Location (Configuration)
// =====================================================================================================================

@interface SWRLLocation_Config : SWRLLocation
@property (nonatomic, readonly) NSString *partnerIdentifier;
@property (nonatomic, readonly) NSArray<SWRLFloorplan*> *floorplans;
@property (nonatomic, readonly) NSArray<SWRLBeacon_Config*> *beacons;

- (instancetype)initWithDictionary:(NSDictionary *)properties;

- (SWRLFloorplan *)floorplan:(NSString *)floorplanId;

- (SWRLBeacon_Config *) findBeaconByIdentifier:(NSString *)identifier;
- (SWRLBeacon_Config *) findBeaconBySerial:(NSString *)serial;

- (double)distance;
- (NSString *)locationName;
- (NSString *)locationDescription;
- (NSString *)addressDescription;

- (void) createBeacon:(SWRLBeacon *)beacon placement:(SWRLPlacement *)placement completion:(void (^)(SWRLBeacon_Config *, NSError *))completion;

- (void) load:(void (^)(NSError *))completion;

@end

#define Location_Config(l)  ((SWRLLocation_Config *)(l))

// =====================================================================================================================
// Beacon (Configuration)
// =====================================================================================================================

/**
 * SWRLBeacon_Config 
 *
 * A SWRLBeacon_Config object represents a configurable beacon registered with the Swirl management
 * platform and provides a single point for coordinating server-side and device-side configuration
 * changes.
 *
 * This class is not yet released as part of a public API.
 */

@interface SWRLBeacon_Config : SWRLBeacon

- (instancetype)initWithDictionary:(NSDictionary *)properties location:(SWRLLocation_Config *)location;
- (void) load:(void (^)(NSError *))completion;

- (NSString *) mac_address;
- (double) battery;
- (BOOL) needsUpdate;

- (void) beginConfiguration;
- (void) abortConfiguration;
- (void) commitConfiguration:(BOOL)force completion:(void (^)(NSError *))completion;

+ (void) connectForConfiguration:(SWRLBeacon *)beacon timeout:(NSTimeInterval)timeout completion:(void (^)(SWRLBeacon *, NSError *))completion;

- (void) setFirmware:(SWRLBeaconFirmware *)firmware;

- (SWRLLocation *)location;
- (void) setLocation:(SWRLLocation_Config *)location;

- (SWRLPlacement *)placement;
- (void) setPlacement:(SWRLPlacement *)placement;

- (SWRLFloorplan *)floorplan;
- (SWRLImageMarker *)floorplanMarker;

- (void) setFloorplanLocation:(SWRLFloorplan *)floorplan marker:(SWRLImageMarker *)marker;

- (void) setFarImage:(UIImage *)image;
- (void) setNearImage:(UIImage *)image;
- (UIImage *) farImage;
- (UIImage *) nearImage;
- (void) farImageWithCompletion:(void (^)(UIImage *, NSError *)) completion;
- (void) nearImageWithCompletion:(void (^)(UIImage *, NSError *)) completion;

- (void) setFarImageMarker:(SWRLImageMarker *)marker;
- (void) setNearImageMarker:(SWRLImageMarker *)marker;
- (SWRLImageMarker *)farImageMarker;
- (SWRLImageMarker *)nearImageMarker;

- (NSDictionary *)deviceConfigurationState;
- (NSDictionary *)serverConfigurationState;
- (void) setServerConfigurationState:(NSDictionary *)serverState;

+ (void) commitFirmware:(SWRLBeaconFirmware *)firmware beacon:(SWRLBeacon *)beacon urn:(NSString *)upgradeURN completion:(void (^)(NSError *))completion;

@end

@interface SWRLBeacon (Config)
- (void) connectWithTimeout:(NSTimeInterval)timeout queue:(dispatch_queue_t)queue
                 completion:(void (^)(SWRLPeripheral *, NSError *))completion;
- (void) clearPeripheral;
@end

@interface SWRLBluetoothScanner (Config)
- (void) startScanning;
- (void) stopScanning;
- (void) removePeripheralWithIdentifier:(NSUUID *)identifier;
@end

@interface SWRLBeaconManager (Config)
- (SWRLBeacon *) beaconWithIdentifier:(NSString *)identifier serial:(NSString *)serial urn:(NSString *)urn peripheral:(BOOL)peripheral;
- (void) beaconWithIdentifier:(NSString *)identifier serial:(NSString *)serial urn:(NSString *)urn peripheral:(BOOL)peripheral timeout:(NSTimeInterval)timeout queue:(dispatch_queue_t)queue
				   completion:(void (^)(SWRLBeacon *, NSError *))completion;
@end

// =====================================================================================================================
// Beacon Handler
// =====================================================================================================================

extern id const SWRLBeaconHandler_InvalidConfig;

@interface SWRLBeaconHandler : NSObject
- (void) unlockBeacon:(SWRLBeacon *)beacon completion:(void (^)(NSError *error))completion;
- (NSDictionary<NSString *,id> *) bodyForCreateBeacon:(SWRLBeacon *)beacon;
- (void) postCreateBeacon:(SWRLBeacon_Config *)configBeacon peripheralBeacon:(SWRLBeacon *)peripheralBeacon completion:(void (^)(NSError *error))completion;
- (NSArray<NSDictionary<NSString *,id> *> *) gattForBeacon:(SWRLBeacon_Config *)beacon firmwareVersion:(NSString *)firmwareVersion config:(NSDictionary *)config;
- (NSString *) firmwareVersion:(SWRLBeacon *)beacon;
@end

#endif
