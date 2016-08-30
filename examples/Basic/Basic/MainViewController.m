// =====================================================================================================================
// Basic - Sample
// MainViewController.m
//
// Copyright 2015-2016, Swirl Networks, Inc.  All Rights Reserved..
// =====================================================================================================================

#import <Swirl/Swirl.h>
#import "MainViewController.h"

@implementation MainViewController

// =====================================================================================================================
#pragma mark - View Configuration
// =====================================================================================================================

- (BOOL) shouldAutorotate {
    return NO;
}

- (UIInterfaceOrientationMask)supportedInterfaceOrientations {
    return UIInterfaceOrientationMaskPortrait;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    // configure navigation items
    self.title = stringForKey([NSBundle mainBundle].infoDictionary, @"CFBundleName", @"Basic");

    // add state label (center)
	UILabel *statusLabel = [[UILabel alloc] initWithFrame:CGRectMake(0, 140, self.view.bounds.size.width, 40)];
	statusLabel.text = @"Hello World!";
    statusLabel.textAlignment = NSTextAlignmentCenter;
    statusLabel.numberOfLines = 2;
    statusLabel.font = [UIFont systemFontOfSize:20];
    statusLabel.textColor = [UIColor blackColor];
	[self.view addSubview:statusLabel];
}

@end
