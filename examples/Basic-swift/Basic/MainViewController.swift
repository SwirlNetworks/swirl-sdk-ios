// =====================================================================================================================
// Basic - Sample
// MainViewController.swift
//
// Copyright 2017-2018, Swirl Networks, Inc.  All Rights Reserved..
// =====================================================================================================================

import UIKit


class MainViewController : UIViewController {

	override func viewDidLoad() {
		super.viewDidLoad()

		self.title = Bundle.main.object(forInfoDictionaryKey: "CFBundleName") as? String
	}
}
