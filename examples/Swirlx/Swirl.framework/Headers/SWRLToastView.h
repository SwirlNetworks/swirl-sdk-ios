// =====================================================================================================================
// SWRLToastView.h
// Copyright 2015-2016, Swirl Networks, Inc.  All Rights Reserved.
// =====================================================================================================================

#import <UIKit/UIKit.h>

@interface SWRLToastView : UIView
@property (nonatomic) NSString  *           title;                  // if nil, the titleLabel will collapse
@property (nonatomic) NSString *            message;                // if nil, the messageLabel will collapse
@property (nonatomic) NSDate    *           time;                   // if nil, the timeLabel will collapse

@property (nonatomic) UIFont *              font;                   // default is nil, uses the systemFont
@property (nonatomic) UIColor *             textColor;              // default is nil, will derive a white or black color from the background color
@property (nonatomic) UIColor *             backgroundColor;        // default is black with .60 alpha
@property (nonatomic) NSTimeInterval        displaySeconds;         // default is 0 or no-limit

@property (nonatomic) UIView *              tabAccessoryView;       // default is pull-tab label
@property (nonatomic) UIView *              deleteAccessoryView;    // default is red X
@property (nonatomic) BOOL                  swipeToDelete;          // default is NO

@property (nonatomic, readonly) UIView *    contentView;            // background view
@property (nonatomic, readonly) UILabel *   titleLabel;             // default title label
@property (nonatomic, readonly) UILabel *   timeLabel;              // default time label
@property (nonatomic, readonly) UILabel *   messageLabel;           // default message label

- (instancetype) initWithTitle:(NSString *)title message:(NSString *)message time:(NSDate *)time
                 actionHandler:(void (^)(SWRLToastView *view, BOOL))actionHandler;
- (void) presentFromViewController:(UIViewController *)vc;

@end


