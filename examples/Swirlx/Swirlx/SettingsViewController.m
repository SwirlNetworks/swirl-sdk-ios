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
@property (nonatomic) NSString *value;
@property (nonatomic, copy) void (^onchange)(NSString *value);
@end

@implementation SettingsValueViewContoller

- (instancetype)initWithTitle:(NSString *)title value:(NSString *)value onchange:(void(^)(NSString *value))onchange {
    if ((self = [super init]) != nil) {
        self.title = title;
        self.value = value ? value : @"";
        self.onchange = onchange;
        
        self.edgesForExtendedLayout = UIRectEdgeNone;
        self.view.backgroundColor = [UIColor groupTableViewBackgroundColor];
        
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
    if (![self.value isEqualToString:self.field.text])
        self.onchange(self.field.text);
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
        initWithTitle:meta[@"title"] value:_settings[meta[@"key"]] onchange:^(NSString *value) {
            _settings[meta[@"key"]] = value;
            _changed = YES;
        }];
    [[self navigationController] pushViewController:vc animated:YES];
}

@end
