// =====================================================================================================================
// Swirlx - Sample
// MainViewController.m
//
// Copyright 2015-2016, Swirl Networks, Inc.  All Rights Reserved..
// =====================================================================================================================

#import <Swirl/Swirl.h>
#import "AppDelegate.h"
#import "MainViewController.h"
#import "MapViewController.h"
#import "VisitViewController.h"
#import "SettingsViewController.h"

#define RESET_DELAY     10.0    /* reset delay allows backgrounding before start */
#define DISPLAY_DELAY   1.0     /* display delay allows fast state transitions to be seen */

@interface MainViewController () <SWRLSwirlDelegate,SWRLVisitManagerDelegate, SWRLContentManagerDelegate>
@property (nonatomic) NSString *    contentAttributes;
@property (nonatomic) UILabel *     statusLabel;        // swirl running state display
@property (nonatomic) UILabel *     locationStatus;     // current 'closest' location label
@property (nonatomic) UILabel *     deviceStatus;       // current 'device status' as of last update
@property (nonatomic) UIButton *    activeVisits;
@property (nonatomic) int           startPending;       // seconds til reset or 0
@end

@implementation MainViewController

// =====================================================================================================================
#pragma mark - Status Labels
// =====================================================================================================================

- (void) updateDeviceStatus:(SWRLStatus)status {
    NSRange     xx0, xx1, xx2;
    NSString *  text = @"Location: XX0 / Bluetooth: XX1 / Network: XX2";
    
    #define S_ON_OFF(b)   (b ? @"On " : @"Off")
    text = [text stringByReplacingCharactersInRange:(xx0=[text rangeOfString:@"XX0"]) withString:S_ON_OFF(status & SWRLStatusLocation)];
    text = [text stringByReplacingCharactersInRange:(xx1=[text rangeOfString:@"XX1"]) withString:S_ON_OFF(status & SWRLStatusBluetooth)];
    text = [text stringByReplacingCharactersInRange:(xx2=[text rangeOfString:@"XX2"]) withString:S_ON_OFF(status & SWRLStatusNetwork)];
    
    NSMutableAttributedString *attrText = [[NSMutableAttributedString alloc] initWithString:text];
    
    #define C_ON_OFF(b) (b ? [UIColor grayColor] : [UIColor redColor])
    [attrText addAttribute:NSForegroundColorAttributeName value:C_ON_OFF(status & SWRLStatusLocation)  range:xx0];
    [attrText addAttribute:NSForegroundColorAttributeName value:C_ON_OFF(status & SWRLStatusBluetooth) range:xx1];
    [attrText addAttribute:NSForegroundColorAttributeName value:C_ON_OFF(status & SWRLStatusNetwork)   range:xx2];
    
    self.deviceStatus.attributedText = attrText;
}

- (void) updateStatus:(NSString *)status {
    static NSTimeInterval last = 0; if (last == 0) last = now();
    
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (DISPLAY_DELAY-(now()-last)) * NSEC_PER_SEC), dispatch_get_main_queue(), ^{
        self.statusLabel.textAlignment = NSTextAlignmentCenter;
        self.statusLabel.numberOfLines = 2;
        self.statusLabel.text = status;
        [self.statusLabel sizeToFit];
        CGRect frame = self.statusLabel.frame;
        frame.size.width = self.view.bounds.size.width;
        self.statusLabel.frame = frame;
        [self updateDeviceStatus:[Swirl shared].status];
    });
    last = now();
}

- (void) updateLocationStatus:(SWRLLocation *)location {
    if (location && ([Swirl shared].status & SWRLStatusSwirlMask) == SWRLStatusRunning) {
        self.locationStatus.text = [NSString stringWithFormat:@"%@\n%@\n%@\n", location.description, location.signal.description,
                                    self.contentAttributes ? self.contentAttributes : @""];
        CGSize size = [self.locationStatus sizeThatFits:CGSizeMake(CGRectGetWidth(self.locationStatus.frame), CGFLOAT_MAX)];
        CGRect frame = self.locationStatus.frame; frame.size.height = size.height;
        self.locationStatus.frame = frame;
    } else {
        self.locationStatus.text = @"No Signal Detected";
        CGSize size = [self.locationStatus sizeThatFits:CGSizeMake(CGRectGetWidth(self.locationStatus.frame), CGFLOAT_MAX)];
        CGRect frame = self.locationStatus.frame; frame.size.height = size.height;
        self.locationStatus.frame = frame;
    }
	[self updateDeviceStatus:[Swirl shared].status];
}

- (void) updateActiveVisits:(NSArray<SWRLVisit*> *)visits {
    [self updateLocationStatus:visits.firstObject.location];
    if (visits.count > 0) {
        self.activeVisits.hidden = NO;
        [self.activeVisits sizeToFit];
        self.activeVisits.center = CGPointMake(self.view.center.x, CGRectGetMaxY(self.locationStatus.frame)+15);
    } else {
        self.activeVisits.hidden = YES;
    }
}

// =====================================================================================================================
#pragma mark - ACTIONS
// =====================================================================================================================

- (void) startAfterCountdown {
    if (_startPending > 0) {
        [self updateStatus:[NSString stringWithFormat:@"Starting in %d", _startPending--]];
        [self updateActiveVisits:nil];
        dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(1 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
            [self startAfterCountdown];
        });
    } else {
        [[Swirl shared] start:[[NSUserDefaults standardUserDefaults] objectForKey:@"swirl_options"]];
    }
}

- (void) showContent:(UIButton *)unused {
    [[SWRLContentManager shared] showContentViewController];
}

- (void) showMap:(UIButton *)unused {
    [[self navigationController] pushViewController:[[MapViewController alloc] init] animated:YES];
}

- (void) showActiveVisits:(UIButton *)unused {
    [[self navigationController] pushViewController:[[VisitViewController alloc] init] animated:YES];
}

- (void) reset {
    if (_startPending == 0) {
        _startPending = RESET_DELAY;
        self.locationStatus.text = nil;
        [self updateStatus:@"Resetting"];
        [[Swirl shared] reset];
        [self startAfterCountdown];
    }
}

- (void) editSettings {
    SettingsMetadata *meta = @[
        @[  @{ @"title" : @"Domain",                @"key" : SWRLSettingApiHost,       @"type" : @"text",  @"user" : @NO,  },
            @{ @"title" : @"Content Code",          @"key" : SWRLSettingContentCode,   @"type" : @"text",  @"user" : @NO,  },
            @{ @"title" : @"Beacon Filter",         @"key" : SWRLSettingBeaconFilter,  @"type" : @"text",  @"user" : @NO,  },
			@{ @"title" : @"Field 1",               @"key" : @"field_1",               @"type" : @"text",  @"user" : @YES, },
			@{ @"title" : @"Field 2",               @"key" : @"field_2",               @"type" : @"text",  @"user" : @YES, },
			@{ @"title" : @"Clear Location Locks",  @"key" : @"clear_locks",           @"type" : @"bool",  @"user" : @NO,  },
		]
    ];
    NSMutableDictionary *settings = [[[NSUserDefaults standardUserDefaults] objectForKey:@"swirl_options"] mutableCopy];
    SettingsViewController *vc = [[SettingsViewController alloc]
        initWithMetadata:meta settings:settings
                onchange:^(NSDictionary *updated, NSDictionary *user_info) {
                    [settings addEntriesFromDictionary:updated];
                    [[NSUserDefaults standardUserDefaults] setObject:settings forKey:@"swirl_options"];
                    [[NSUserDefaults standardUserDefaults] synchronize];
					[self reset];
					[[Swirl shared] setUserInfo:user_info];
                }];
    [[self navigationController] pushViewController:vc animated:YES];
}

// =====================================================================================================================
#pragma mark - SWIRL DELEGATE
// =====================================================================================================================

- (void) swirlDidUpdateStatus:(SWRLStatus)status {
    switch (status & SWRLStatusSwirlMask) {
        case SWRLStatusNone:                        [self updateStatus:@"Stopped"];     break;
        case SWRLStatusPending:                     [self updateStatus:@"Starting"];    break;
        case SWRLStatusRunning:                     [self updateStatus:@"Running"];     break;
        case SWRLStatusRunning|SWRLStatusPending:   [self updateStatus:@"Stopping"];    break;
        default: {
            [self updateStatus:[NSString stringWithFormat:@"Error\n%@",
                                [Swirl shared].error.localizedDescription]];
            break;
        }
    }
}

- (void) visitManager:(SWRLVisitManager *)manager didBeginVisit:(SWRLVisit *)visit {
    [self updateActiveVisits:manager.activePlacementVisits];
}

- (void) visitManager:(SWRLVisitManager *)manager didUpdateDwellForVisit:(SWRLVisit *)visit {
    [self updateActiveVisits:manager.activePlacementVisits];
}

- (void) visitManager:(SWRLVisitManager *)manager didEndVisit:(SWRLVisit *)visit {
    [self updateActiveVisits:manager.activePlacementVisits];
}

- (void) contentManager:(SWRLContentManager *)manager didReceiveContentURL:(SWRLContent *)content fromNotification:(BOOL)fromNotification {
    self.contentAttributes = content.attributes ? [NSString stringWithFormat:@"Content Attributes: %@", content.attributes] : @"";
}

- (void) contentManager:(SWRLContentManager *)manager didReceiveContentSwirl:(SWRLContent *)content fromNotification:(BOOL)fromNotification {
    self.contentAttributes = content.attributes ? [NSString stringWithFormat:@"Content Attributes: %@", content.attributes] : @"";
}

- (void) contentManager:(SWRLContentManager *)manager didReceiveContentCustom:(SWRLContent *)content fromNotification:(BOOL)fromNotification {
    self.contentAttributes = content.attributes ? [NSString stringWithFormat:@"Content Attributes: %@", content.attributes] : @"";
}

// =====================================================================================================================
#pragma mark VIEW OVERRIDES
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
    self.title = stringForKey([NSBundle mainBundle].infoDictionary, @"CFBundleName", @"Swirlx");
    self.navigationItem.leftBarButtonItem = [[UIBarButtonItem alloc] initWithTitle:@"Reset"
            style:UIBarButtonItemStylePlain target:self action:@selector(reset)];
    self.navigationItem.rightBarButtonItem = [[UIBarButtonItem alloc] initWithTitle:@"Settings"
            style:UIBarButtonItemStylePlain target:self action:@selector(editSettings)];
    
    // add state label (center)
	self.statusLabel = [[UILabel alloc] initWithFrame:CGRectMake(0, 140, self.view.bounds.size.width, 40)];
    self.statusLabel.textAlignment = NSTextAlignmentCenter;
    self.statusLabel.numberOfLines = 2;
    self.statusLabel.font = [UIFont systemFontOfSize:20];
    self.statusLabel.textColor = [UIColor blackColor];
	[self.view addSubview:self.statusLabel];
    
    // add location label (current visit information)
	self.locationStatus = [[UILabel alloc] initWithFrame:CGRectMake(0, 220, self.view.bounds.size.width, 0)];
    self.locationStatus.textAlignment = NSTextAlignmentCenter;
    self.locationStatus.numberOfLines = 0;
    self.locationStatus.lineBreakMode = NSLineBreakByWordWrapping;
    self.locationStatus.font = [UIFont systemFontOfSize:[UIFont systemFontSize]];
    [self.view addSubview:self.locationStatus];
    
    // add all active signals...
    self.activeVisits = [UIButton buttonWithType:UIButtonTypeSystem];
    self.activeVisits.titleLabel.font = [UIFont italicSystemFontOfSize:[UIFont systemFontSize]];
    [self.activeVisits setTitleColor:[UIColor blackColor] forState:UIControlStateNormal];
    [self.activeVisits addTarget:self action:@selector(showActiveVisits:) forControlEvents:UIControlEventTouchUpInside];
    [self.activeVisits setTitle:@"[ Show All Visits ]" forState:UIControlStateNormal];
    [self.view addSubview:self.activeVisits];
    
    // add return to content
    UIButton *content = [UIButton buttonWithType:UIButtonTypeSystem];
    content.titleLabel.font = [UIFont italicSystemFontOfSize:[UIFont smallSystemFontSize]];
    [content setTitleColor:[UIColor blackColor] forState:UIControlStateNormal];
    [content setTitle:@"[ Show Content View ]" forState:UIControlStateNormal];
    [content addTarget:self action:@selector(showContent:) forControlEvents:UIControlEventTouchUpInside];
    [content sizeToFit];
    content.center = CGPointMake(self.view.center.x-CGRectGetWidth(content.bounds)/2-10, CGRectGetHeight(self.view.bounds)-75);
    [self.view addSubview:content];
    
    // add Show Map
    UIButton *map = [UIButton buttonWithType:UIButtonTypeSystem];
    map.titleLabel.font = [UIFont italicSystemFontOfSize:[UIFont smallSystemFontSize]];
    [map setTitleColor:[UIColor blackColor] forState:UIControlStateNormal];
    [map setTitle:@"[ Show Map View ]" forState:UIControlStateNormal];
    [map addTarget:self action:@selector(showMap:) forControlEvents:UIControlEventTouchUpInside];
    [map sizeToFit];
    map.center = CGPointMake(self.view.center.x+CGRectGetWidth(map.bounds)/2+20, CGRectGetHeight(self.view.bounds)-75);
    [self.view addSubview:map];
    
    // add device status label
    self.deviceStatus = [[UILabel alloc] initWithFrame:CGRectMake(0, self.view.bounds.size.height-60, self.view.bounds.size.width, 20)];
    self.deviceStatus.font = [UIFont italicSystemFontOfSize:[UIFont smallSystemFontSize]];
    self.deviceStatus.textAlignment = NSTextAlignmentCenter;
    [self.view addSubview:self.deviceStatus];
    
    // add identifier and version
    UILabel *info = [[UILabel alloc] initWithFrame:CGRectMake(0, self.view.bounds.size.height-40, self.view.bounds.size.width, 20)];
    info.font = [UIFont italicSystemFontOfSize:[UIFont smallSystemFontSize]];
    info.textAlignment = NSTextAlignmentCenter;
    info.text = [NSString stringWithFormat:@"Identifier: %@ / Version: %@",
                 [[Swirl shared].userKey substringToIndex:5], [Swirl shared].version];
    [self.view addSubview:info];
    
    // prime the display with current status
    [self swirlDidUpdateStatus:[Swirl shared].status];
    
    // hook state updates, to reflect current status
    [[Swirl shared] addDelegate:self];
}

- (void) dealloc {
    [[Swirl shared] removeDelegate:self];
}

@end
