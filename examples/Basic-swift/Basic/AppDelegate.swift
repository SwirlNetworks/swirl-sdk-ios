// =====================================================================================================================
// Basic - Sample
// AppDelegate.swift
//
// Copyright 2017-2018, Swirl Networks, Inc.  All Rights Reserved..
// =====================================================================================================================

import UIKit


@UIApplicationMain
class AppDelegate : UIResponder, UIApplicationDelegate, UNUserNotificationCenterDelegate {

	var window: UIWindow?
	var locationManager: CLLocationManager?


	func requestPermissions(_ application: UIApplication) {
		let locationManager = CLLocationManager.init()
		locationManager.requestAlwaysAuthorization()

		if #available(iOS 10.0, *) {
			UNUserNotificationCenter.current().requestAuthorization(options:[.alert, .sound]) { (granted, error) in
				if granted {
					NSLog("notification permissions granted=\(granted) (error=\(String(describing: error))")
					DispatchQueue.main.async {
						UIApplication.shared.registerForRemoteNotifications()
					}
				}
			}
		} else {
			let settings = UIUserNotificationSettings(types: [(application.currentUserNotificationSettings?.types)!, .alert, .sound], categories: nil)
			application.registerUserNotificationSettings(settings)
			application.registerForRemoteNotifications()
		}
	}

	func application(_ application: UIApplication, didReceive notification: UILocalNotification) {
		SWRLSwirl.shared().post(notification)
	}

	@available(iOS 10.0, *)
	func userNotificationCenter(_ center: UNUserNotificationCenter, didReceive response: UNNotificationResponse, withCompletionHandler completionHandler: @escaping () -> Void) {
		SWRLSwirl.shared().post(response);
		completionHandler();
	}

	func application(_ application: UIApplication, didRegisterForRemoteNotificationsWithDeviceToken deviceToken: Data) {
		SWRLSwirl.shared().deviceToken = deviceToken
	}

	func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplicationLaunchOptionsKey: Any]?) -> Bool {
		SWRLSwirl.shared().addDelegate(ContentManager.init())

		var API_KEY = nil	// REPLACE-WITH-YOUR-API-KEY
		SWRLSwirl.shared().start([SWRLSettingApiKey: API_KEY]);

		requestPermissions(application)
		return true
	}
}
