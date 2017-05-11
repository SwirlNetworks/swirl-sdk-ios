/*
 * SWRLSignal.h
 * Copyright 2015-2016 Swirl Networks, Inc. All Rights Reserved.
 */

#ifndef __SWRLSIGNAL__
#define __SWRLSIGNAL__

#import <Foundation/Foundation.h>
#import <Swirl/SWRLObject.h>

NS_ASSUME_NONNULL_BEGIN

@class SWRLLocation;

/***** Signal Types ****/

typedef NS_ENUM(int, SWRLSignalType) {
    /** Signal is Beacon */
    SWRLSignalTypeBeacon    = 1,
    /** Signal is a WifiInfo */
    SWRLSignalTypeWifi      = 2,
    /** Signal is a Region */
    SWRLSignalTypeGeofence  = 3
};

/**
 * SWRLAttachement is a class which encapsulates namespace-type/data attachements made to a signal.
 */
@interface SWRLAttachment : NSObject
/**
 * Attachment namespace/type
 */
@property (nonatomic, readonly) NSString *  type;
/**
 * Attachment data
 */
@property (nonatomic, readonly) NSData *    data;
/**
 * Return an object as interpreted by type
 */
@property (nonatomic, readonly) id          object;

- (instancetype) initWithDictionary:(NSDictionary *)info;

@end

/**
 * SWRLSignal is an abstract base class for any presence signal object.  Concrete subclasses are Beacon, WifiInfo and Region.
 * A signal is tied to a logical placement and location.
 */

@interface SWRLSignal : SWRLObject

/** ====================================================================================================================
 * @name Accessing Attributes
 *  ====================================================================================================================
 */

/** 
 * Protocol specific identifier derived from detection attributes lat/long; beacon advertisement or wifi mac-address 
 */
@property (nonatomic, readonly) NSString *          urn;

/** 
 * Type of signal. 
 */
@property (nonatomic, readonly) SWRLSignalType      type;

/** 
 * This is the approximate range to the beacon.  This is a rough approximation. 
 */
@property (nonatomic, readonly) double              range;

/** 
 * Timestamp of last detection of this signal.
 */
@property (nonatomic, readonly) NSTimeInterval      lastDetected;

/** 
 * Error (set if there is a problem with this signal)
 */
@property (nonatomic, readonly) NSError *           error;

/**
 * A logical Location and Placement associated to this georegion through the platform.
 */
@property (nonatomic, readonly) SWRLLocation *      location;

/** ====================================================================================================================
 *  @name Accessing Custom Labels and Attributes
 *  ====================================================================================================================
 */

/**
 * A set of property value pairs associated to this Location-Placement through the platform.
 */
@property (nonatomic, readonly) NSDictionary *      attributes;
/**
 * A set of labels assigned to this Location-Placement through the platform.
 */
@property (nonatomic, readonly) NSArray<NSString*>* labels;

/**
 * The set of attachments associated with this signal 
 */
@property (nonatomic, readonly) NSArray<SWRLAttachment*> *attachments;

/**
 * The set of attachments that have a given namespace or type.  Specify string/ to match namespace
 * and specify /string to match type.
 *
 * @param type namespace/type, namespace/ or /type
 */
- (NSArray<SWRLAttachment*>*)attachmentsWithType:(NSString *)type;

- (instancetype) initWithDictionary:(nullable NSDictionary *)info urn:(nullable NSString *)urn;
- (void) setError:(NSError *)error;

@end

NS_ASSUME_NONNULL_END

#endif

