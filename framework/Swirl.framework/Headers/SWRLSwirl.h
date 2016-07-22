/*
 *	SWRSwirl.h
 *  Swirl framework for beacons, geofences, micro-location based content.
 *	Copyright 2015 Swirl Networks, Inc. All rights reserved.
 */

#ifndef __SWRLSWIRL__
#define __SWRLSWIRL__

#import <Swirl/SWRLBase.h>
#import <Swirl/SWRLAPI.h>

NS_ASSUME_NONNULL_BEGIN

/// @constant SWRLSwirl
/**
 * SWRLStatus Bit flags used to determine the running status of the sdk
 */
typedef NS_OPTIONS(NSInteger, SWRLStatus) {
    /// swirl-status: not-running
    SWRLStatusNone             = 0,
    /// swirl-status: running
    SWRLStatusRunning          = (1 << 0),
    /// swirl-status: changing
    SWRLStatusPending          = (1 << 1),
    /// swirl-status: error reported
    SWRLStatusError            = (1 << 2),
    /// device-status: location
    SWRLStatusLocation         = (1 << 3),
    /// device-status: bluetooth
    SWRLStatusBluetooth        = (1 << 4),
    /// device-status: network
    SWRLStatusNetwork          = (1 << 5),
    /// device-status: notifications
    SWRLStatusNotifications    = (1 << 6),
    /// mask for accessing swirl status portion
    SWRLStatusSwirlMask        = (SWRLStatusRunning|SWRLStatusPending|SWRLStatusError),
    /// mask for accessing device status portion
    SWRLStatusDeviceMask       = (SWRLStatusLocation|SWRLStatusNetwork|SWRLStatusBluetooth|SWRLStatusNotifications)
};

/**
 
The Swirl class is the main entry point into the Swirl proximity sdk for delivery of proximity and content
events to your app.  You use a singleton instance of this class to start: and stop proximity detection and delivery of proximity
events.  It supports a multi-delegate interface so you can add one or many delegate objects to recieve callbacks from any of the
protocols broadcast to the mult-delegate bus.
 
 - SWRLSwirlDelegate for state updates about sdk state
 - SWRLBeaconScannerDelegate for beacon advertisement callbacks
 - SWRLBeaconManagerDelegate for beacon calbacks (enter, exit, closest, dwell)
 - SWRLWifiManagerDelegate for wifi calbacks (enter, exit)
 - SWRLRegionManagerDelegate for region (geofence) calbacks (enter, exit)
 - SWRLVisitManagerDelegate for visit calbacks (begin, end, dwell)
 - SWRLContentManagerDelegate for content calbacks (receive content)

 */

@interface SWRLSwirl : NSObject

/** ====================================================================================================================
 * @name Properties
 *  ====================================================================================================================
 */

/** system status */
@property (nonatomic, readonly) SWRLStatus      status;
/** version */
@property (nonatomic, readonly) NSString *      version;
/** last error reported */
@property (nonatomic, readonly) NSError *       error;
/** uuid generated for this instance */
@property (nonatomic, readonly) NSString *      userKey;
/** property-values passed to server */
@property (nonatomic)           NSDictionary *  userInfo;
/** geo-location */
@property (nonatomic, readonly) CLLocation *    location;

/** ====================================================================================================================
 * @name Managing Delegates
 *  ====================================================================================================================
 */

/**
 * Add a delegate to the internal delegate bus
 *
 * @param delegate the object to receive delegate callbacks
 */
- (void) addDelegate:(id)delegate;

/*
 * Remove a delegate that had been previously added via addDelegate:.  If the delegate is not
 * present, this method does nothing.
 *
 * @param delegate the object to receive delegate callbacks
 */

- (void) removeDelegate:(id)delegate;

/** ====================================================================================================================
 * @name Managing Lifecyle
 *  ====================================================================================================================
 */

/**
 * Starts the sdk and all loaded managers
 * @param options all of the startup options (see x)
 */
- (void) start:(nullable NSDictionary *)options;

/**
 * Stops the sdk
 */
- (void) stop;

/**
 * Removes all locally stored data and state.  If the sdk is currently running, it will call stop first.
 * After calling this function, the sdk will be in a stopped state.
 */
- (void) reset;

/** ====================================================================================================================
 * @name Advanced
 *  ====================================================================================================================
 */

/**
 * Log event to the log stream.
 * @param event The event name (see the list of known events)
 * @param data The data for event (see the list of events)
 */
- (void) logEvent:(NSString *)event data:(NSString *)data;

/**
 * Post an object to the internal message bus
 * @param object the object to post
 */
- (void) postObject:(id)object;
- (void) postMessage:(SEL)message withObject:(id)object1;
- (void) postMessage:(SEL)message withObject:(id)object1 withObject:(id)object2;

- (instancetype)init;

+ (instancetype) shared;

@end

typedef SWRLSwirl Swirl;

/**
 * This protocol defines message that the Swirl SDK provides about its internal state
 *
 */
@protocol SWRLSwirlDelegate <NSObject>
@optional
- (void) swirlDidUpdateStatus:(SWRLStatus)status;
- (void) swirlDidReportError:(NSError *)error;
@end



NS_ASSUME_NONNULL_END

#endif


