# Swirl Proximity Developer Guide

## Contents
- [Understanding Swirl](#understanding-swirl)
  - [Concepts and Objects](#concepts-and-objects)
- [Technical Overview](#technical-overview)
  - [Architechture](#architecture)
- [Integration](#integration)
  - [Application Key](#get-application-key)
  - [Verify Tools and Targets](#verify-tools-and-targets)
  - [Add Framework to your Application](#add-framework-to-your-application)
  - [Make Code Changes](#make-code-changes)
  - [Push Notification Notes](#push-notification-notes)
  - [Oracle Responsys Mobile SDK Integration](#oracle-responsys-mobile-sdk-integration)
  - [KouponMedia Mobile SDK Integration](#kouponmedia-mobile-sdk-integration)
  
## Understanding Swirl
![](./images/sdk3-architecture-overview.png)

### Concepts and Objects
The Swirl platform and SDK use some key objects that are useful to define here.

**Location**: a physical street, city, state address - typically a brick-and-mortar store or venue. Locations are created and managed centrally in the Console and form the core building blocks of the platform.

**Placement**: a logical and business-friendly name given to a specific area inside a location.  For example - cosmetics, electronics department, checkout, neighborhood, parking lot, etc. Placements define the desired level of audience targeting and analytics/data collection marketers wish to achieve based on their defined marketing objectives. 

**BeaconAdvertisement**: an object which represents a single advertisement of a BLE beacon.  It contains a normalized identifier, an RSSI (signal strength) and a timestamp.  It can also contain extra information for protocols (like Eddystone) that broadcast such additional information.

**Beacon**:  an object which represents a BLE beacon.  It aggregates a stream of **BeaconAdvertisements** into a coherent object along with any server-side attributes assigned to the beacon, provided the current application has access rights to the signal.  Server-side attributes include **Location**, **Placement**, and any labels and custom-attributes assigned through the platform.

**Region**: an object representing a Geofence.  It has a GPS coordinate and a radius, or a set of points which represent a non-circular border.  Like a beacon, it also aggregates server side information like **Location**, **Placement** and any labels and custom-attributes assgned through the platform.

**WifiInfo**: an object that represents the current access point the mobile device is connected to.  It contains the BSSID, the SSID and an RSSI (if present).  Like other objects in the system, it can be associated with server-side objects like **Location**, **Placement**, and custom attributes.

**Visit**: an object which represents a higher-level of presence event.  All lower-level (Region, Beacon, Wifi) presence events are aggregated into a logical Visit event.  Visit objects contain **Location**, and **Placement** information as well as tracking location and placement dwell time and total elapsed time.  

**Content**: an object which represents targeted content selected by the platform in response to a presence event trigger (entry, dwell threshold exceeded, etc).  Content is generally a bundle containing metadata to create a notification and either a deep-link URL, an HTML creative URL or a JSON bag of custom attributes.
### User Privacy and Permissions
Earier versions of the Swirl SDK enforced a strict user opt-in policy which often complicated the host application's own attempts at user on-boarding and opt-in flows.  As a result, the current SDK has eliminated all notions of user status and state from the SDK and relies completely on the host-application to follow best practices in this area.  This SDK tracks location and should not be used unless the user has explicitly granted the application such rights.  For the most part, the OS helps enforce this best practice, but it is not universally the case and what the OS enforces varies by platform.  On Android, location permissions must be granted in order to use BLE beacons, on iOS this is not the case.  The host application is responsible for requesting the appropriate permissions and the SDK will try to run within those constraints to the best of its ability.

## Technical Overview 
### Architecture
The architecture of the Swirl SDK is similar on all platforms.  The Swirl object acts as a shell which establishes a working queue or thread, a common message bus and loads various managers into that enviorment.  The SDK glues together signal detection code that interacts with OS apis for detecting beacon, wifi and geofence signals with code that interacts with the swirl REST APIs to determine logical metadata like location, placement and other custom metadata.  In addition, the SDK tracks and accumulates dwell and can manage interaction with the platform to request and display targeted content.

![](./images/sdk3-ios-architecture.png)

#### Key components
The following is a list of the key components of the SDK and a brief description of each.  Most of these components are internal to the SDK but their description here is provided to help understand the operaiton of the SDK.  It is important to note that developers can extend the operation of the Swirl SDK by adding their own managers to the internal message bus and participate fully in its operation.
* **Swirl**:  The external wrapper for the API.  All public interfaces live here.  The ability to add delegates/listeners to the bus, post messages to components, set options, start and stop the SDK.  Establishes the private thread/queue, the message bus and loads all managers.
* **Observers**:  The internal message bus.  Implementation varies by platform, but ensure that components can message each other in a way that ensures thread safety.  Managers can subscribe to messages, post messages or both.  On iOS the implementation is a form of multicast delegate where delegates declare which queue they want to be called on.
* **BluetoothScanner**:  A component which interact with the CoreBluetooth apis for bluetooth or beacon detection and which publish normalized **BeaconAdvertisement** objects on to the bus.
* **IBeaconScanner**: A component which creates a `CLLocationManager` and registers `CLBeaconRegions` for the purpose of detecting beacons using the iBeacon protocol. This component uses various strategies to minimize the number of `CLRegions` it uses.
* **BeaconManager**:  A component which subscribes to **BeaconAdvertisement** messages and aggregates those advertisements into a **Beacon** object.  It uses the API to resolve beacons (or not) and to fetch assoicated logical location and placement information and metadata.  It monitors beacons for proximity and manages enter, exit and closest detection.  It posts BeaconEnter, BeaconExit, BeaconDwell, BeacionNearest messages onto the bus.
* **RegionManager**:  A component which manages a working set of **Region** objects (retreived using the API) that are 'near' the users location.  These regions represent both geofences and 'control' regions.  Geofences have logical location, placement and other metadata associated.  Control regions are used internally by the SDK to control other signal detection, like when to start and stop scanning for beacons or what iBeacon UUIDs are nearby.  This component either starts its own os specific location manager or depends upon the host app to post location information onto the bus.  It generates RegionEnter/RegionExit events onto the bus.
* **WifiManager**: A component which integrates with the OS interfaces for detecting current connected wifi information and tracks changes to the connection state.  It coordinates through the API with the Swirl platform to get assoicated logical location informationa and associated metadata. It posts WifiEnter, WifiExit, WifiDwell events onto the message bus and creates **WifiInfo** objects.
* **VisitManager**:  A component which consumes the various Enter/Exit/Dwell events from the signal detectors and tracks enter and exit times, accumulates dwell and elapsed times by location and placement, and generates logical **Visit** objects and events for BeginVisit,DwellVisit, and EndVisit.
* **ContentManager**: A component which consumes **Visit** objects and events and requests content through the API.  If content is returned, then depending upon application state and SDK settings, it is responsible for displaying OS notifications and launching a content view or an application deep link.  This component is not part of the default set of managers that are loaded and users who want content services will add this object or a subclass of this object to the bus at startup.
* **API**:  A singleton which wraps the REST API to the Swirl platform.  All communications with the server are secure using https and all APIs must be authenticated using the API Key assigned through the Swirl platform.  
* **Settings**: A singleton which provides property value and object storage in a local, encrypted store.  All constants in the system are reflected through this object with local, server, and default values.  Values can be pushed from the server to change the behavior of the system at runtime.

## Integration
### Get Application Key
Log in to the Swirl console using supported browser (Chrome or Safari) and using credentials you have received from your Swirl representative or Swirl administrator.
 1. Navigate to the Apps tab in the portal
 2. Create a new application.
 3. This process will generate an Application Key. This value will be needed to passed to the SDK at start.

### Verify Tools and Targets
The Swirl SDK is compatible with iOS 8.0 and above and is fully iOS 9.0 compliant and BITCODE enabled as required.  You will need to use an Xcode of at least version 7.0 to build applications with this SDK.

### Add Framework to your Application
The Swirl SDK is packaged as a statically linked framework called *Swirl.framework*.

#### Adding the Framework Manually
 1. The Swirl framework should be added to your project under the **Linked Frameworks and Libraries** section of the **General** tab of the target.  You can add this by hitting the '+' and selecting the file.  
 2. The framework depends upon *CoreLocation*, *CoreBluetooth* and *SystemConfiguration* but those files should be automatically linked for you.  
 3. It is also recommended (but not required) to add some additional frameworks: *PassKit* for better user experience when the user decides to save delivered content to their wallet and *AdSupport* for access to the AdvertisingIdentifier.

 ![](./images/sdk3-add-framework.png)

#### Adding the Framework Using Cocoapods

The Swirl framework pod is named **swirl-sdk-ios**. The initial version is **3.0**.

**Note**: There is another pod published with the name *SwirlFramework*. This pod is deprecated and should no longer be used.

To always include the latest version of the pod simply add the following line to the target in your podfile:
```ruby
pod 'swirl-sdk-ios', '>=3.0'
```

A simple podfile that always includes the latest Swirl framework would look like this:
```ruby
target 'MyApp' do
	pod 'swirl-sdk-ios', '>=3.0'
end
```

Refer to the [Using CocoaPods](https://guides.cocoapods.org/using/using-cocoapods.html) guide on [cocoapods.org](cocoapods.org) for more information.

### Make Code Changes

#### Modify the Info.plist
 **Location Services**
 Edit the Info.plist and ensure that `NSLocationAlwaysUsageDescription` or `NSLocationWhenInUseUsageDescription` exists with a user-visible usage description.  Location services will not work without one of these modes being set.  The SDK can function in either mode, but if you want to be able to receive background notifications, `NSLocationAlwaysUsageDescription` is required.
 
 ***Note*** - iOS 11 now requires 3 keys in Info.plist in order to request Always location services:
 1. `NSLocationAlwaysUsageDescription`
 2. `NSLocationAlwaysAndWhenInUseUsageDescription`
 3. `NSLocationWhenInUseUsageDescription`

 **Bluetooth Services**
 If you are requesting location tracking always permission, and you wish to detect BLE beacons in the background, then you need to include the appropriate “Background Mode” permission.  
  1. In Xcode, open your application's target and click the Capabilities tab.
  2. Expand the “Background Modes” section, ensure that the section is ON and that Uses Bluetooth LE accessories is checked.
  
  ![](./images/sdk3-capabilities.png)

#### Permission Changes
The Swirl SDK requires Location Services, Bluetooth and Local Notifications to be fully effective.  The host application is responsible for managing the opt-in flow and prompting the user for the necessary permissions.  When started, if the proper permissions have not been granted, then functionality will be limited.  If you do not already, you will need to request authorization using `requestAlwausAuthorization` or `requestWhenInUseAuthorization` on an instance of `CLLocationManager`.  You will also need to request the appropriate level of notification permissions using `registerUserNotificationSettings` on `UIApplication`.  Examples of how to do this are included in our sample application.

#### Background Launch Changes
With location services and/or Bluetooth Low Energy (BLE) scanning enabled, application launches can happen in the background in addition to the foreground.  If your application does not already handle background launches, this can be the biggest change when integrating the SDK.  Make sure to restructure the startup flow to distinguish between foreground launches and background launches and to ensure that the ***minimal*** work is done when launched into the background (like avoiding networking calls and creating the user interface).  Failing to segment this properly will result in less than optimal operation and could result in excessive battery drain.

#### Import the Framework Header
You will need to import the Swirl header any place you reference Swirl objects and methods.  If you are using Swift, then including this file in your Bridging header is a good place.
```objective-c
#import <Swirl/Swirl.h>
```
#### Initialize, Configure and Start
A lot of time and effort has been put into making the Swirl SDK as simple as possible without sacrificing functionality or power.  Due to the possibility of background launches caused by CoreLocation or CoreBluetooth services that the SDK starts, the best place to initialize and start the SDK is early in `application:didFinishLaunchingWithOptions:`
```objective-c
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)options {
    // optionally add the default content services
    [[Swirl shared] addDelegate:[SWRLContentManager new]];    
    // start the basic Swirl proximity services
    [[Swirl shared] start:@{ SWRLSettingApiKey:APIKEY }];
    // ...other application startup code...
    return YES;
}
```
### Push Notification Notes
Swirl delivers local notifications for proximity based content and remote notifications for scheduled content.  In order to use any notifications local or remote, you will need to request permissions from the user.
Below is code that supports iOS versions before and after 10.0 to handle both old and new style of notifications.  If you want to use the new style notifications (UserNotifications Framework) you must set the `SWRLSettingUseNewNotifications` to YES in order to force the SDK to use this style of notification.

```objective-c

if ([UIDevice currentDevice].systemVersion.floatValue < 10.0) {
    UIUserNotificationSettings *settings = [application currentUserNotificationSettings];
    settings = [UIUserNotificationSettings settingsForTypes:settings.types|UIUserNotificationTypeAlert|UIUserNotificationTypeSound
    categories:settings.categories];
    [application registerUserNotificationSettings:settings];
    [application registerForRemoteNotifications];
} else {
    [[UNUserNotificationCenter currentNotificationCenter] requestAuthorizationWithOptions:(UNAuthorizationOptionAlert|UNAuthorizationOptionSound)
    completionHandler:^(BOOL granted, NSError * _Nullable error) {
        dispatch_async(dispatch_get_main_queue(), ^{
            [application registerForRemoteNotifications];
        });
    }];
}
```

#### Rich Notifications
Swirl supports rich media notifications for iOS 10.0 and above.  In order to support notification attachments we require the application to add support for iOS UserNotification framework.
Since the Swirl SDK still supports older iOS versions, you must set the `SWRLSettingUseNewNotifications` to YES in order to force the SDK to use this style of notification.  Also if you want to use rich notifications
with remote notifications you will need to add a Notification Service extension.  Swirl has provided a `SWRLNotificationService` class which implements most of the needed code so that you only need to provide a stub
implementation that derives from this class.  See below.

```objective-c
#import <UserNotifications/UserNotifications.h>
#import <Swirl/Swirl.h>

@interface NotificationService : SWRLNotificationService
@end

@implementation NotificationService
@end
```
#### Local Notifications
Local notifications can cause your application to be launched if it is not running or they can be delivered to your application when it is running in the foreground or background.  In order to ensure things are working properly, you
need to make sure that Swirl is started from within the `didFinishLaunchingWithOptions` and that you implement  `didReceiveLocalNotification` and forward the notification to Swirl.

```objective-c
// =====================================================================================================================
// application:didReceiveLocalNotifications:
//
//  Need to hook this and pass notifications to the Swirl SDK.  Swirl will ignore notifications that are not Swirl notifications
//  otherwise, it will dispatch the attached content.  If you do not hook this, then notifications will not work in the
//  case where the application is being launched because the user opened a notification, but it was already running and
//  so didFinishLaunchingWithOptions is never called.
// =====================================================================================================================

- (void)application:(UIApplication *)application didReceiveLocalNotification:(UILocalNotification *)notification {
    [[Swirl shared] postObject:notification];
}

// =====================================================================================================================
// application:didReceiveLocalNotifications:
//
//  Need to hook this and pass notifications to the Swirl SDK.  Swirl will ignore notifications that are not Swirl notifications
//  otherwise, it will dispatch the attached content.  If you do not hook this, then notifications will not work in the
//  case where the application is being launched because the user opened a notification, but it was already running and
//  so didFinishLaunchingWithOptions is never called.
// =====================================================================================================================

- (void)userNotificationCenter:(UNUserNotificationCenter *)center didReceiveNotificationResponse:(UNNotificationResponse *)response
    withCompletionHandler:(void (^)(void))completionHandler {
    [[Swirl shared] postObject:response];
    completionHandler();
}
```
#### Remote Notifications
As of version 3.6, Swirl supports scheduled push notifications.  In order to use this feature, you will need to enable push notifications on your iOS build and get development and production certificates from your
Apple developer account.  You will also need to upload your keys to the Swirl console.  The procedure is documented there.  For the application you will need to implement a couple of delegate callback and you will
need to register for remote notifications and provide the deviceToken to the Swirl SDK.

```objective-c

- (void)application:(UIApplication *)application didReceiveRemoteNotification:(nonnull NSDictionary *)userInfo fetchCompletionHandler:(nonnull void (^)     (UIBackgroundFetchResult))completionHandler {
    [[Swirl shared] postObject:userInfo];
    completionHandler(UIBackgroundFetchResultNoData);
}

- (void) application:(UIApplication *)application didRegisterForRemoteNotificationsWithDeviceToken:(nonnull NSData *)deviceToken {
    [Swirl shared].deviceToken = deviceToken;
}
```

### Oracle Responsys Mobile SDK Integration
In order to integrate the Oracle Responsys Mobile SDK (formerly Push IO) with the Swirl SDK you will need to include three key-value pairs in the Swirl SDK's User Info.
 1. "oapi_key" - (required) Provides the Oracle Responsys Mobile SDK API Key used by your app.
 2. "odevice_id" - (required) An identifier used by the Oracle Responsys Mobile SDK to identify a mobile device.
 3. "oid" - (optional*) Provides a unique identifier for a mobile device user that is linked in Responsys to a known user profile. An example of an "oid" identifier could be an email address or a customer ID for example.

\* In order to utilize Responsys Programs via Swirl-mapped Responsys custom events, “oid” is required. In the absence of "oid", Swirl will utilize the "odevice_id" for direct triggering of Responsys push campaigns.

These three values should be included in a dictionary which is then set as the Swirl SDK's User Info. The following code snippet demonstrates a simple example of how to do this.

```objective-c
NSMutableDictionary *userInfo = [NSMutableDictionary new];
userInfo[@"oapi_key"] = [[PushIOManager sharedInstance] getAPIKey];
userInfo[@"odevice_id"] = [[PushIOManager sharedInstance] getDeviceID];
userInfo[@"oid"] = "<Identifier>";
[[SWRLSwirl shared] setUserInfo:userInfo];
```
### KouponMedia Mobile SDK Integration
The Swirlx sample application includes source code for a custom content handler that integrates with Koupon Media's offer system.  The sample module gets an offerId attribute from the custom content creative and uses that id in API calls to Koupon Media's servers in order to add an offer for the user and to fetch attributes about that offer for the purpose of creating a contextual notification.  The sample code modifies the content with the notification and then allows the modified content to flow through the system.

To instantiate the `KouponMediaManager` you need the API Key, API Secret and User identifier for your KouponMedia account and you need to construct the object and add it as a delegate to Swirls multi-delegate event bus.

```objective-c
// You will need an account, api key and secret from Koupon Media to use this manager
[[Swirl shared] addDelegate:[[KouponMediaManager alloc] initWithKey:@"KOUPON-API-KEY" secret:@"KOUPON-SECRET" user:@"KOUPON-USER"]];
```
You will also need to change the URLs in the KouponMediaManager source code as the ones in the sample code point to the KouponMedia sandbox environment:

```objective-c
#define KM_BASE_URL                 @"https://consumer.sandbox1.kouponmedia.com/v2"
#define KM_DEFAULT_VIEWER_URL       @"https://offer-sandbox1.kou.pn/OfferViewer/Redirect.aspx?property_code=swirl_mobilecapture&offers=%@"
```
Finally, by default the sample code pops a mobile Safari window that points to the default KouponMedia mobile offier viewer.  If you have tightly integrated the KM sdk and fuctionality into your application and have an offer inbox that you want to direct the user to when they encounter a Swirl placement tied to an offer or interact with a notification generated by such an encounter, then you will need to set the property `offerViewerURL` to a custom URL scheme that can direct the user to that inbox.










