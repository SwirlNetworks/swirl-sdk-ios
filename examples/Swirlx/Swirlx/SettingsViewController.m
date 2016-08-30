// =====================================================================================================================
// Swirlx - Sample
// SettingsViewController.m
//
// Copyright 2015-2016, Swirl Networks, Inc.  All Rights Reserved..
// =====================================================================================================================

#import <Swirl/Swirl.h>
#import "AppDelegate.h"
#import "SettingsViewController.h"

@interface SettingsValueViewContoller : UIViewController<UITextFieldDelegate>
@property (nonatomic) UITextField *field;
@property (nonatomic) UISwitch *toggle;
@property (nonatomic) NSString *value;
@property (nonatomic) NSString *type;
@property (nonatomic, copy) void (^onchange)(NSString *value);
@end

@implementation SettingsValueViewContoller

- (instancetype)initWithTitle:(NSString *)title value:(NSString *)value type:(NSString *)type onchange:(void(^)(NSString *value))onchange {
    if ((self = [super init]) != nil) {
        self.title = title;
        self.value = value ? value : @"";
		self.type = type;
        self.onchange = onchange;
        
        self.edgesForExtendedLayout = UIRectEdgeNone;
        self.view.backgroundColor = [UIColor groupTableViewBackgroundColor];

		if ([type isEqualToString:@"text"]) {
			self.field = [[UITextField alloc] initWithFrame:CGRectMake(10, 10, self.view.bounds.size.width-20, 40)];
			self.field.borderStyle = UITextBorderStyleRoundedRect;
			self.field.backgroundColor = [UIColor whiteColor];
			self.field.text = value;
			self.field.keyboardType = UIKeyboardTypeDefault;
			self.field.returnKeyType = UIReturnKeyDone;
			self.field.autocorrectionType = UITextAutocorrectionTypeNo;
			self.field.autocapitalizationType = UITextAutocapitalizationTypeNone;
			self.field.delegate = self;
			
			[self.view addSubview:self.field];
		} else if ([type isEqualToString:@"bool"]) {
			self.toggle = [[UISwitch alloc] initWithFrame:CGRectMake(0, 20, 0, 0)];
			self.toggle.on = [value isEqualToString:@"1"];

			CGPoint center = self.toggle.center;
			center.x = self.view.center.x;
			self.toggle.center = center;

			[self.view addSubview:self.toggle];
		}
    }
    return self;
}

- (BOOL)textFieldShouldReturn:(UITextField *)textField {
    [[self navigationController ] popViewControllerAnimated:YES];
    return YES;
}

- (void) viewDidAppear:(BOOL)animated {
    [self.field becomeFirstResponder];
}

- (void) viewWillDisappear:(BOOL)animated {
	if ([self.type isEqualToString:@"text"]) {
		if (![self.value isEqualToString:self.field.text]) {
			self.onchange(self.field.text);
		}
	} else if ([self.type isEqualToString:@"bool"]) {
		NSString *new_value = @(self.toggle.isOn).stringValue;
		if (![self.value isEqualToString:new_value]) {
			self.onchange(new_value);
		}
	}
}

@end

@interface SettingsViewController() <UIAlertViewDelegate>
@property (strong, nonatomic) SettingsMetadata  *metadata;
@property (strong, nonatomic) NSMutableDictionary *settings;
@property (copy, nonatomic) void (^onchange)(NSDictionary *, NSDictionary *);
@property (nonatomic) BOOL changed;
@property (strong, nonatomic) UIAlertView *locationLocksAlertView;
@end

@implementation SettingsViewController 

- (instancetype) initWithMetadata:(SettingsMetadata *)meta settings:(NSDictionary *)settings onchange:(void (^)(NSDictionary *, NSDictionary *))onchange {
    if ((self = [super initWithStyle:UITableViewStyleGrouped]) != nil) {
        self.metadata = meta;
        self.settings = [settings mutableCopy];
        self.onchange = onchange;
        self.title = @"Settings";
        self.tableView.dataSource = self;
        self.tableView.delegate = self;
    }
    return self;
}

- (void) viewWillDisappear:(BOOL)animated {
    if (_changed) {
		NSMutableDictionary *user_info = [NSMutableDictionary new];
		for (NSArray *group in self.metadata) {
			for (NSDictionary *setting in group) {
				if ([setting[@"user"] isEqual:@YES]) {
					NSString *value = _settings[setting[@"key"]];
					if (value.length != 0) {
						user_info[setting[@"key"]] = value;
					}
				}
			}
		}

        Log_d(@"values changed: values = %@,\nuser_info = %@", _settings, user_info);
        _onchange(_settings, user_info);
    }
}

- (NSInteger) numberOfSectionsInTableView:(UITableView *)tableView {
    return _metadata.count;
}

- (NSInteger) tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return _metadata[section].count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    NSDictionary *meta = _metadata[indexPath.section][indexPath.row];
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"default"];
    if (cell == nil)
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault  reuseIdentifier:@"default"];
    
    cell.textLabel.font = [UIFont boldSystemFontOfSize:14.0];
    cell.textLabel.text = meta[@"title"];
    cell.textLabel.textColor = [UIColor blackColor];
    cell.detailTextLabel.font = [UIFont systemFontOfSize:14.0];
    cell.detailTextLabel.text = _settings[meta[@"key"]];
    cell.detailTextLabel.textColor = [UIColor grayColor];
    cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
    
    return cell;
}

- (void) tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    NSDictionary *meta = _metadata[indexPath.section][indexPath.row];
    SettingsValueViewContoller *vc = [[SettingsValueViewContoller alloc]
        initWithTitle:meta[@"title"] value:_settings[meta[@"key"]] type:meta[@"type"] onchange:^(NSString *value) {
			if ([meta[@"key"] isEqualToString:@"clear_locks"]) {
				Log_d(@"clear locks = %@", value);
				if ([value isEqualToString:@"1"]) {
					[self clearLocks];
				}
			} else {
				Log_d(@"value changed = %@", value);
            	_settings[meta[@"key"]] = value;
            	_changed = YES;
			}
        }];
    [[self navigationController] pushViewController:vc animated:YES];
}

- (void) clearLocks {
	self.locationLocksAlertView = [[UIAlertView alloc] initWithTitle:@"Clear Location Locks"
															 message:@"Clearing Swirl location locks for device, please wait..."
															delegate:self
												   cancelButtonTitle:nil
												   otherButtonTitles:@"Dismiss",nil];
	UIActivityIndicatorView *spinner = [[UIActivityIndicatorView alloc] initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleWhiteLarge];
	spinner.color = [UIColor blackColor];
	[spinner startAnimating];
	[self.locationLocksAlertView setValue:spinner forKey:@"accessoryView"]; // iOS7+ only
	[self.locationLocksAlertView show];

	[[SWRLAPI shared] clearLocationLocks:^(NSError *error) {
		dispatch_async( dispatch_get_main_queue(), ^{
			// didn't find nice/reliable way to 'update' existing alert view, so creating another
			[self.locationLocksAlertView dismissWithClickedButtonIndex:0 animated:NO];

			if (error) {
				self.locationLocksAlertView = [[UIAlertView alloc] initWithTitle:@"Clear Location Locks"
																		 message:@"Failed to clear Swirl location locks for this device. Please check the Internet connection and try again."
																		delegate:self
															   cancelButtonTitle:nil
															   otherButtonTitles:@"OK", nil];
			} else {
				self.locationLocksAlertView = [[UIAlertView alloc] initWithTitle:@"Clear Location Locks"
																		 message:@"Successfully cleared Swirl location locks for this device."
																		delegate:self
															   cancelButtonTitle:nil
															   otherButtonTitles:@"OK", nil];
			}
			[self.locationLocksAlertView show];
		});
	}];
}

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex {
	if (alertView == self.locationLocksAlertView) {
		self.locationLocksAlertView = nil;
	}
}

@end
