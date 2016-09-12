/*
 * SWRLToastView.h
 * Copyright 2015-2016 Swirl Networks, Inc. All Rights Reserved.
 */

#ifndef __SWRLTOASTVIEW__
#define __SWRLTOASTVIEW__

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * A SWRLToastView is a floating notification view that allows the user to delete it from the screen,
 * to move up and down and to slide it way to the right to get it out of the way.  It is used
 * by the SWRLContentManager to provide a default return to content button when the user dismisses content.
 */
@interface SWRLToastView : UIView
/** @name Accessing Information Attributes */
/** The toast title text.  Displays as the first line. If nil, it will collapse and take up no space. */
@property (nonatomic, nullable) NSString  *           title;
/** The toast message.  Displays under the title and if nil, will collapse to nothing */
@property (nonatomic, nullable) NSString *            message;
/** The toast timestamp.  Displays to the right of the title.  If nil, will not display */
@property (nonatomic, nullable) NSDate    *           time;

/** @name Controlling the Appearance */
/** The font to use for all text.  By default uses the systemFont */
@property (nonatomic) UIFont *              font;
/** The text color for all labels. By default is nill and will derive an approriate color based on the background */
@property (nonatomic) UIColor *             textColor;
/** The background of the toast.  The default is black with a .60 alpha */
@property (nonatomic) UIColor *             backgroundColor;
/** The time to display.  Currently this field has no effect. */
@property (nonatomic) NSTimeInterval        displaySeconds;
/** The view to display when the toast is in its parked right position. The default is a tab. */
@property (nonatomic) UIView *              tabAccessoryView;
/** The view to display when the toast is in its swiped left or delete mode.  The default is an X on red background */
@property (nonatomic) UIView *              deleteAccessoryView;
/** Boolean to control whether the user can swipe left to delete in a single motion. Default is NO */
@property (nonatomic) BOOL                  swipeToDelete;

/** Background view of the toast */
@property (nonatomic, readonly) UIView *    contentView;
/** Default titleLabel */
@property (nonatomic, readonly) UILabel *   titleLabel;
/** Default timeLabel */
@property (nonatomic, readonly) UILabel *   timeLabel;
/** Default messageLabel */
@property (nonatomic, readonly) UILabel *   messageLabel;

/**
 * Construct and initialise a toastView with title, message and timestamp.
 * 
 * @param title The toast view title
 * @param message The toast view message
 * @param time  The toast view timestamp (optional)
 * @param actionHandler The completion block that is called when the user activates the toast or deletes it.
 */
- (instancetype) initWithTitle:(NSString *)title message:(NSString *)message time:(NSDate *)time
                 actionHandler:(void (^)(SWRLToastView *view, BOOL))actionHandler;

/**
 * Present a toast view from a controller.
 *
 * @param vc The viewController to use as the host of the toast view.
 */
- (void) presentFromViewController:(UIViewController *)vc;

@end

NS_ASSUME_NONNULL_END

#endif


