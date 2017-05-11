/*
 * SWRLSwirl.h
 * Copyright 2015-2016 Swirl Networks, Inc. All Rights Reserved.
 */

#ifndef __SWRLSWIRL__
#define __SWRLSWIRL__

#import <Swirl/SWRLBase.h>
#import <Swirl/SWRLAPI.h>

NS_ASSUME_NONNULL_BEGIN

/**
 *  SWRLStatus Bit flags used to determine the running status of the framework
 */
typedef NS_OPTIONS(NSInteger, SWRLStatus) {
    /// This value indicates that the system is not running.
    SWRLStatusNone             = 0,
    /// If this bit is set, the system is either Running or if Pending is also set, Stopping.
    SWRLStatusRunning          = (1 << 0),
    /// If this bit is set, the system is transitioning from Stopped to Running or the reverse.
    SWRLStatusPending          = (1 << 1),
    /// If this bit is set, the system has reported an error, which is available in the error property.
    SWRLStatusError            = (1 << 2),
    /// If this bit is set, Location Services are authorized.
    SWRLStatusLocation         = (1 << 3),
    /// If this bit is set, Bluetooth is available.
    SWRLStatusBluetooth        = (1 << 4),
    /// If this bit is set, Network connectivity is available.
    SWRLStatusNetwork          = (1 << 5),
    /// If this bit is set, Notification are enabled.
    SWRLStatusNotifications    = (1 << 6),
    /// A mask for accessing swirl status portion.
    SWRLStatusSwirlMask        = (SWRLStatusRunning|SWRLStatusPending|SWRLStatusError),
    /// A mask for accessing device status portion.
    SWRLStatusDeviceMask       = (SWRLStatusLocation|SWRLStatusNetwork|SWRLStatusBluetooth|SWRLStatusNotifications)
};

/**
 
The Swirl class is the main entry point into the Swirl proximity sdk for delivery of proximity and content
events to your app.  
 
 You use a singleton instance of this class to start: and stop proximity detection and delivery of proximity
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
 * @name System Information
 *  ====================================================================================================================
 */

/** The current system status */
@property (nonatomic, readonly) SWRLStatus      status;
/** The current version of the framework. */
@property (nonatomic, readonly) NSString *      version;
/** The last error reported. */
@property (nonatomic, readonly) NSError *       error;
/** The frameworks currently maintained CLLocation */
@property (nonatomic, readonly) CLLocation *    location;

/** ====================================================================================================================
 * @name User Information
 *  ====================================================================================================================
 */
/** A NSUUID generated for this device. */
@property (nonatomic, readonly) NSString *      userKey;
/** A dictionary of property values that are associated with this device/user. */
@property (nonatomic)           NSDictionary *  userInfo;

/** ====================================================================================================================
 * @name Managing Delegates
 *  ====================================================================================================================
 */

/**
 * Add a delegate to the internal delegate bus
 *
 * Delegates are added to the internal multicast delegate bus and can receive messages from any of the listed
 * protocols (see x).  Delegates added via this method are added using the main queue.  This function simply
 * calls addDelegate:queue: with the result of **dispatch_get_main_queue()** as the queue argument.
 * If the existing delegate has already been added, this function takes no action.
 *
 * @param delegate The object to receive delegate callbacks. This parameter must not be `nil`.
 * @see removeDelegate:,addDelegate:queue:
 *
 */
- (void) addDelegate:(id)delegate;

/**
 * Add a delegate to the internal delegate bus, specifying a queue.
 *
 * Delegates are added to the internal multicast delegate bus and can receive messages from any of the listed
 * protocols (see x).  All messages dispatched to this delegate will be delivered on the queue specified.
 * If the existing delegate has already been added, this function takes no action.
 *
 * @param delegate The object to receive delegate callbacks. This parameter must not be `nil`.
 * @param queue The GCD dispatch queue on which messages should be delivered.  This parameter must not be `nil`.
 * @see removeDelegate:,addDelegate:
 *
 */
- (void) addDelegate:(id)delegate queue:(dispatch_queue_t)queue;

/**
 * Remove a delegate that had been previously added via addDelegate:.  
 *
 * If the delegate is not present, this method does nothing.
 *
 * @param delegate The object to receive delegate callbacks. This paramter must not be `nil`.
 * @see addDelegate:,addDelegate:queue:
 */
- (void) removeDelegate:(id)delegate;

/**
 * Find a delegate given a class.
 *
 * Finds the first delegate of a given class and returns it if found,
 * otherwise it returns nil.
 *
 * @param aclass The class of delegate to find.
 * @returns The delegate if found, or nil.
 */
- (id) findDelegateOfClass:(Class)aclass;

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
 *  Stops the sdk
 *  @discussion This method is not typically used unless you want to stop all monitoring.  If this is called
 *  all monitoring will stop, including background monitoring.  Your application will no longer receive any notifications
 *  for proximity events and will not be restarted in the background by the operating system.
 */
- (void) stop;

/**
 *  Removes all locally stored data and state.  If the sdk is currently running, it will call stop first.
 *  After calling this function, the sdk will be in a stopped state.
 *  @discussion This method is not typically used.  It is provided for testing or to be used if you need to completely
 *  remove any state stored locally on the device when a user opts-out.
 */
- (void) reset;

/** ====================================================================================================================
 * @name Passing Information to Swirl
 *  ====================================================================================================================
 */

/**
 *  Post an object to the internal message bus
 *  @param object the object to post
 *  @discussion Posting an object is a convenient short hand to calling postMessage:withObject:.  The method invoked
 *  on members of the internal bus is `on{[[object class] name]}:object`.  This method is used primarily to post
 *  UILocalNotifications to Swirl from applicaiton:didReceiveLocalNotification:, or to post CLLocation objects if
 *  you are running Swirl in a manual location mode (when the framework does not maintain its own CLLocationManager).
 *
 */
- (void) postObject:(id)object;

- (void) postMessage:(SEL)message withObject:(id)object1;
- (void) postMessage:(SEL)message withObject:(id)object1 withObject:(id)object2;

/**
 * Log event to the log stream.
 * @param event The event name (see the list of known events)
 * @param data The data for event (see the list of events)
 */
- (void) logEvent:(NSString *)event data:(NSString *)data;

- (instancetype)init;
- (instancetype)init:(NSArray<Class>*)classes;

/**
 * Control the log level.  Default level is @"W"
 * @param level @"E", @"W", @"I" for error, warning or info levels, anything else will disable.
 */
+ (void) setLogLevel:(NSString *)level;

/**
 *  Swirl is a singleton.  You use shared to get access to the shared instance.
 */
+ (instancetype) shared;

/**
 * Advanced: This initalizes the singleton with non-default array of manager classes.
 * Afterwards can access Swirl using the normal accessor [Swirl shared].
 * Default classes: SWRLVisitManager, SWRLBeaconManager, SWRLRegionManager, SWRLWifiManager,
 * SWRLIBeaconScanner, SWRLBluetoothScanner
 * @param classes An array of class objects to initialize the managers/observers can be empty
 */
+ (instancetype) with:(NSArray<Class> *)classes;

@end

typedef SWRLSwirl Swirl;

/**
 * The SWRLSwirlDelegate protocol defines messages that the Swirl framework provides about its internal state.
 */
@protocol SWRLSwirlDelegate <NSObject>
@optional
/**
 *  Tells the delegate that the status field has changed.  Swirl has transitioned states.
 *  @param status  The current system status. See SWRLStatus.
 */
- (void) swirlDidUpdateStatus:(SWRLStatus)status;
/**
 *  Tells the delegate that an error has been reported.
 *  @param error  The error that was reported.
 */
- (void) swirlDidReportError:(NSError *)error;
/**
 * Tells the delegate that the SDK updated its location
 * @param location  The updated location.
 */
- (void) swirlDidUpdateLocation:(CLLocation *)location;

@end



NS_ASSUME_NONNULL_END

#endif


