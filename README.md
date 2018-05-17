# Swirl Proximity Framework
The Swirl platform is designed as a complete proximity platform detecting a variety of proximity signals like geofence, wifi and beacons and managing presence tracking, notification and content delivery.  The Swirl framework is a component of this system which enables signal detection and content delivery on mobile devices.

![](./docs/images/sdk3-overview.png)

### Features
* Simple Interface, Easy to integrate
* Small footprint, native implementations
* Geofence: circular and arbitrary polygons
* Wifi: Enables access points to be used like beacons or geofences
* Beacon: SecureCast™, Eddystone (URL, UID, EID, TLM) and iBeacon, easy to extend
* Content: Support for interstitials, deep links and custom content types (optional)

## Documentation and Resources
There are a number of additional documents and resources available to facilitate the integration and use of the Swirl Proximity Framework.

#### For Implementation
* [Swirl Proximity Developer Guide for iOS](./docs/swirl-developer-guide-ios.md)
* [Swirl Proximity Framework Reference for iOS](https://swirlnetworks.github.io/swirl-sdk-ios/docs/reference-guide/html/index.html)
* [Example Source Code for iOS](./examples/)

#### For Testing
* [BeaconManager in the App Store](https://itunes.apple.com/us/app/swirl-beacon-manager/id855322103?mt=8) which can be used to configure and deploy beacons.
* [Explorer in the App Store](https://itunes.apple.com/us/app/swirl-in-store-explorer/id781067361?mt=8) which can be used for testing signals and content.
* [Customer Supoprt: support@swirl.com](mailto:support@swirl.com) 
  Support and Testing Services. Swirl appreciates publishers willing to share their integrated application for Swirl testing. This is an added service that we provide you to ensure that your app has been properly integrated with our SDK. Please contact your Swirl Account Manager to schedule this testing.

## Release Notes
**Version:** `3.7.1` &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;**Date:** `5/20/18`
<p>
Fixed a bug with application state tracking.  Removed specific latitude/longitude on all API calls (now under options control).

**Version:** `3.7` &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;**Date:** `4/27/18`
<p>
Enhancements for streaming events, post visit campaigns.

**Version:** `3.6.1` &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;**Date:** `2/23/18`
<p>
Fixed an issue that could cause creatives with 3rd party URLs to fail to display when coming from a notification.

**Version:** `3.6` &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;**Date:** `12/20/17`
<p>
Added support for rich notifications, scheduled push notifications.  Added ability to intercept all openURL requests even
from tap area widgets in content.  Added custom event logging.  Bug fixes and further hardening.

**Version:** `3.5` &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;**Date:** `09/15/17`
<p>
Bug fixes, custom event streaming, custom content integrations and samples.

**Version:** `3.4` &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;**Date:** `05/15/17`
<p>
Improved support for eddystone, proximity beacon api integration and attachements, Toast first mode. 

**Version:** `3.3` &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;**Date:** `02/01/17`
<p>
Replaced up-front device registration with just-in-time device registration (scalability).

**Version:** `3.2.1` &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;**Date:** `01/13/17`
<p>
Added ability to set log level. Minor bug fixes.

**Version:** `3.2` &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;**Date:** `01/06/17`
<p>
Adds support for realtime streaming or events; improved support for eddystone; added improved security for API requests; added support for enter/exit zone signals, other bug fixes.  

**Version:** `3.1` &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;**Date:** `12/19/16`
<p>
Fixes a crash that can occur during background launches on some devices.  

**Version:** `3.0` &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;**Date:** `9/16/16`
<p>
This version of the SDK represents a completely rearchitected and rewritten code base for iOS.  

## License
We have included our standard commercial [license](LICENSE.md), but this repository is public currently for technical reasons ONLY and its accessibility should not be considered a grant of any rights.  Please see [Swirl](https://www.swirl.com) for more details or email us at [sales@swirl.com](mailto:sales@swirl.com) if you are interested in using our products.

