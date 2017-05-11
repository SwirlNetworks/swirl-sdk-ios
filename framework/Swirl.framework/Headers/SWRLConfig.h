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
 *  SWRLBeaconFirmware
 */
@interface SWRLBeaconFirmware : SWRLObject
@property (nonatomic, readonly) NSString *manufacturer;
@property (nonatomic, readonly) NSString *model;
@property (nonatomic, readonly) NSString *version;
@property (nonatomic, readonly) NSString *notes;
@property (nonatomic, readonly) NSData *data;

- (void) load:(void (^)(NSError *))completion;

- (void) download:(SWRLPeripheral *)peripheral completion:(void (^)(NSError *))completion;

+ (void) firmwareAllVersions:(void (^)(NSArray<SWRLBeaconFirmware*>*, NSError *))completion;
+ (void) firmwareVersionsForManufacturer:(NSString *)manufacturer model:(NSString *)model completion:(void (^)(NSArray<SWRLBeaconFirmware*>*, NSError *))completion;
+ (void)firmwareLatestForManufaturer:(NSString *)manufacturer model:(NSString *)model completion:(void (^)(SWRLBeaconFirmware *, NSError *))completion;

@end

typedef NSDictionary<NSString*,NSDictionary*> SWRLBeaconConfigurationInfo;

@interface SWRLBeaconConfiguration : SWRLObject

+ (void) configurationsWithPartner:(SWRLPartner *)partner
                 completion:(void (^)(SWRLBeaconConfigurationInfo *, NSArray<SWRLBeaconConfiguration*>*, NSError*))completion;
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

- (instancetype)initWithX:(double)x y:(double)y radius:(double)radius;
@end

// =====================================================================================================================
// Floorplan
// =====================================================================================================================

@interface SWRLFloorplan : SWRLObject
@property (readonly) NSString *	imageIdentifier;
@property (readonly) NSString *	locationIdentifier;
@end

// =====================================================================================================================
// Location (Configuration)
// =====================================================================================================================

@interface SWRLLocation_Config : SWRLLocation
@property (nonatomic, readonly) NSString * partnerIdentfier;
@property (nonatomic, readonly) NSDictionary<NSString *,SWRLFloorplan*> *floorplans;
@property (nonatomic, readonly) NSArray<SWRLBeacon_Config*> *beacons;

- (instancetype)initWithDictionary:(NSDictionary *)properties;

- (SWRLFloorplan *)floorplan:(NSString *)floorplanId;

- (double)distance;
- (NSString *)locationDescription;
- (NSString *)addressDescription;

- (void) registerBeacon:(SWRLBeacon *)beacon placement:(SWRLPlacement *)placement force:(BOOL)force
             completion:(void (^)(SWRLBeacon_Config *, NSError *))completion;

- (void) load:(void (^)(NSError *))completion;

@end

#define Location_Config(l)  ((SWRLLocation_Config *)(l))

// =====================================================================================================================
// Beacon (Configuration)
// =====================================================================================================================

extern NSString *const SWRLImageTagNear;
extern NSString *const SWRLImageTagFar;

/**
 *  SWRLBeacon_Config
 */
@interface SWRLBeacon_Config : SWRLBeacon

- (instancetype)initWithDictionary:(NSDictionary *)properties location:(SWRLLocation_Config *)location;
- (void) load:(void (^)(NSError *))completion;

- (double) battery;

- (void) beginConfiguration;
- (void) abortConfiguration;
- (void) commitConfiguration:(BOOL)force completion:(void (^)(NSError *))completion;

- (void) setFirmware:(SWRLBeaconFirmware *)firmware;

- (SWRLLocation *)location;
- (void) setLocation:(SWRLLocation_Config *)location;

- (SWRLPlacement *)placement;
- (void) setPlacement:(SWRLPlacement *)placement;

- (SWRLFloorplan *)floorplan;
- (SWRLImageMarker *)floorplanMarker;

- (void) setFloorplanLocation:(SWRLFloorplan *)floorplan marker:(SWRLImageMarker *)marker;

- (void) setImage:(UIImage *)image tag:(NSString *)tag;
- (void) imageWithTag:(NSString *)tag completion:(void (^)(UIImage *, NSError *)) completion;

- (void) setImageMarker:(SWRLImageMarker *)marker tag:(NSString *)tag;
- (SWRLImageMarker *)imageMarkerForTag:(NSString *)tag;

+ (void) commitFirmware:(SWRLBeaconFirmware *)firmware beacon:(SWRLBeacon *)beacon urn:(NSString *)upgradeURN completion:(void (^)(NSError *))completion;

@end

@interface SWRLBeacon (Config)
- (void) connectWithTimeout:(NSTimeInterval)timeout queue:(dispatch_queue_t)queue
                 completion:(void (^)(SWRLPeripheral *, NSError *))completion;
@end



#endif
