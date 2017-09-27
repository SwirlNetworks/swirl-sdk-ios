/*
 * SWRLContentViewController.h
 * Copyright 2015-2016 Swirl Networks, Inc. All Rights Reserved.
 */

#ifndef __SWRLCONTENTVIEWCONTROLLER__
#define __SWRLCONTENTVIEWCONTROLLER__

#import <UIKit/UIKit.h>

/**
 *  The SWRLContentViewController class defines the view controller used for presenting interstitial content.
 *  This class can be subclassed in order to customize some of its look and feel and behavior.
 */

@interface SWRLContentViewController : UINavigationController<UIWebViewDelegate, UIGestureRecognizerDelegate>
/**
 * @name Acessing Attributes
 */

/**
 * The UIViewController that contains the webView
 */
@property (nonatomic)           UIViewController *webViewController;
/**
 * The UIWebView for rendering html content.
 */
@property (nonatomic)           UIWebView *       webView;
/**
 * The SWRLContent object that is being loaded.  If this is nil, then the most recent content in the content
 * history will be used.  If there is not such content, then the emptyContentHtml will be used.
 */
@property (nonatomic, readonly) SWRLContent *     content;
/**
 * The current array of toolbar items for the webview
 */
@property (nonatomic, readonly) NSArray *         toolbarItems;
/**
 * The html string to display when there is no content to show.  The default screen is white page with
 * gray text that says *No Content*.
 */
@property (nonatomic, readonly) NSString *        emptyContentHtml;
/**
 * The current loading view.  This can be overridden if different behavior is desired.  The 
 * default loading view displays a 20% black mask with a white spinner.
 */
@property (nonatomic, readonly) UIView *          loadingView;

/**
 * The close handler is called when the user hits the 'X' and during the completion for
 * dismissViewControllerAnimated:
 */
@property (nonatomic, copy)     void            (^closeHandler)(void);

- (instancetype) init;

/**
 * loadContent is called by the SWRLContentManager when content is received.
 *
 * @param content The content to load.
 * @param wait Amount of time to wait for pre-load..completion will be called when load complete or this time expires
 * @param completion The block that is executed with the content load completes (or fails).
 *
 */
- (void) loadContent:(SWRLContent *)content wait:(NSTimeInterval)wait completion:(void (^)(NSError *))completion;

/**
 * Called before the loading view is shown.
 * @param loadingView By default this is the maskView.
 */
- (void) willShowLoadingView:(UIView *)loadingView;
/**
 * Called after the loading view has been hidden.
 * @param loadingView By default this is the maskView.
 */
- (void) didHideLoadingView:(UIView *)loadingView;

/**
 * Called to close the view.
 * @param sender The button
 */
- (void)close:(id)sender;

@end

#endif
