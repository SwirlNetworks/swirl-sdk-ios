// =====================================================================================================================
// Swirlx - Sample
// SettingsViewController.h
//
// Copyright 2015-2016, Swirl Networks, Inc.  All Rights Reserved..
// =====================================================================================================================

#import <UIKit/UIKit.h>

typedef NSArray<NSArray<NSDictionary*>*> SettingsMetadata;

@interface SettingsViewController : UITableViewController
- (instancetype) initWithMetadata:(SettingsMetadata *)meta
                         settings:(NSDictionary *)settings
                         onchange:(void (^)(NSDictionary *values))onchange;
@end
