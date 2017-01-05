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

@interface SettingsViewController()
@property (strong, nonatomic) SettingsMetadata  *metadata;
@property (strong, nonatomic) NSMutableDictionary *settings;
@property (copy, nonatomic) void (^onchange)(NSDictionary *);
@property (nonatomic) BOOL changed;
@end

@implementation SettingsViewController 

- (instancetype) initWithMetadata:(SettingsMetadata *)meta settings:(NSDictionary *)settings onchange:(void (^)(NSDictionary *))onchange {
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
        Log_d(@"values changed: values = %@", _settings);
        _onchange(_settings);
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
	UIAlertController *alert = [UIAlertController alertControllerWithTitle:@"Clear Location Locks" message:@"Clearing Swirl location locks for device, please wait...\n\n\n" preferredStyle:UIAlertControllerStyleAlert];
	[alert addAction:[UIAlertAction actionWithTitle:@"Dismiss" style:UIAlertActionStyleDefault handler:nil]];

	UIActivityIndicatorView *spinner = [[UIActivityIndicatorView alloc] initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleWhiteLarge];
	spinner.color = [UIColor blackColor];
	[spinner setTranslatesAutoresizingMaskIntoConstraints:false];
	[alert.view addSubview:spinner];

	NSLayoutConstraint *vertConstraint = [NSLayoutConstraint constraintWithItem:spinner attribute:NSLayoutAttributeCenterX relatedBy:NSLayoutRelationEqual toItem:alert.view attribute:NSLayoutAttributeCenterX multiplier:1 constant:0];
	NSLayoutConstraint *horizConstraint = [NSLayoutConstraint constraintWithItem:spinner attribute:NSLayoutAttributeCenterY relatedBy:NSLayoutRelationEqual toItem:alert.view attribute:NSLayoutAttributeCenterY multiplier:1 constant:15];
	[alert.view addConstraints:@[vertConstraint, horizConstraint]];
	[spinner setUserInteractionEnabled:false];
	[spinner startAnimating];

	[self presentViewController:alert animated:true completion:nil];

	[[SWRLAPI shared] clearLocationLocks:^(NSError *error) {
		dispatch_async( dispatch_get_main_queue(), ^{
			[spinner stopAnimating];

			if (error) {
				[alert setMessage:@"Failed to clear Swirl location locks for this device. Please check the Internet connection and try again."];
			} else {
				[alert setMessage:@"Successfully cleared Swirl location locks for this device."];
			}
		});
	}];
}

@end
