/*
 * SWRLContentManager.h
 * Copyright 2015-2016 Swirl Networks, Inc. All Rights Reserved.
 */

#ifndef __SWRLCONTENTMANAGER__
#define __SWRLCONTENTMANAGER__

#import <Foundation/Foundation.h>
#import <Swirl/SWRLManager.h>
#import <Swirl/SWRLVisitManager.h>
#import <Swirl/SWRLContent.h>
#import <Swirl/SWRLContentViewController.h>

/**
 *  A SWRLContentManager component if loaded, will consume Visit events using the SWRLVisitManagerDelegate protocol and use
 *  those events to trigger content requests through the API.  If content is returned, then depending upon the application state
 *  and settings, it is responsible for displaying local notifications (if the application is in the background) and launching
 *  a content view (full screen interstitial view controller) or opening an application deep link or exterunal URL.
 *
 *  This component is not loaded by default, so it must be loaded explicitly at startup or whenever content experiences
 *  are needed.
 *
 *  If you need to be informed of content delivery event, then you can subscribe to the delegate interfaces which provide
 *  callbacks when various types of content is delivered.  However, since the multi-cast delegate system is a one way
 *  broadcast of information, if you need to customize the details of the flow, block certain creatives from launching at
 *  runtime, you will need to subclass this component and override various methods to alter its default behavior.
 */

@interface SWRLContentManager : SWRLManager<SWRLVisitManagerDelegate>
/** @name Accessing Attributes */
/** The most recent visit object.  This is either the current visit or a recently exited one. */
@property (nonatomic, readonly) SWRLVisit *                   recent;
/** The last piece of content received */
@property (nonatomic, readonly) SWRLContent *                 lastContent;
/** @name Customizing the Content View */
/** 
 *  The UIViewController from which to present the SWRLContentViewController.  Override this property to
 *  change which controller is used.  By default, the implementation searches for the top most UIViewController
 *  and returns that.
 */
@property (nonatomic, readonly) UIViewController *            contentViewPresenter;
/**
 *  The UIViewController which is the default presentation view for content.  You
 *  can override viewControllerForContent to change the default.
 */
@property (nonatomic, readonly) SWRLContentViewController *   contentViewController;

/**
 * The UIView which represents the current toast view (if displayed).
 */
@property (nonatomic, readonly) UIView *contentToastView;

/** @name Receiving Content Events */
/**
 *  Called when content of type URL is received.
 *
 *  @param content  The content that was just received.
 *  @discussion The default implementation just forwards the event via the delegate interface.
 */
- (void) didReceiveContentURL:(SWRLContent *)content;

/**
 *  Called when content of type Swirl is received.
 *
 *  @param content  The content that was just received.
 *  @discussion The default implementation just forwards the event via the delegate interface.
 */
- (void) didReceiveContentSwirl:(SWRLContent *)content;
/**
 *  Called when content of type Custom is received.
 *
 *  @param content  The content that was just received.
 *  @discussion The default implementation just forwards the event via the delegate interface.
 */
- (void) didReceiveContentCustom:(SWRLContent *)content;
/**
 *  Called when content of any type is received.
 *
 *  @param content  The content that was just received.
 *
 *  @discussion This is the first method called when content is received.  Note that content can be received
 *  from the platform or it can be received as part of processing a notificaton. The default implementation of this method sets `lastContent`
 *  and its timestamp, switches on content type to call the type specific variants of `didReceiveContent...` and
 *  starts the display process for either a background notification or foreground content experience.
 *
 *  @warning This method is critical to the proper operation of the SWRLContentManager. If you override this
 *  method, you must pass this message to `super`.
 */
- (void) didReceiveContent:(SWRLContent *)content;

/** @name Controlling Content Display */
/**
 *  Called before content is shown in foreground.
 *
 *  @param content  The content that is about to be opened.
 *  @return YES if you want to display only the toast view and not the full interstitial
 *
 *  @discussion The default implementation returns the value of the SWRLSettingContentShowToastFirst setting which 
 *  defaults to NO.
 **/
- (BOOL) shouldShowToastFirst:(SWRLContent *)content;

/**
 *  Called before a deep-link or external URL is activated.
 *
 *  @param content  The content that is about to be opened.
 *  @return YES if you want to display the content, NO if you do not.
 *
 *  @discussion If you need to control the display of certain content items, you can override this method and inspect
 *  the content parameter and either return YES to continue the action or NO to suppress it.
 *  The default implementation always returns YES.
 **/
- (BOOL) shouldShowURLContent:(SWRLContent *)content;
/**
 *  Called before a web interstitial is about to be displayed.
 *
 *  @param content  The content that is about to be displayed.
 *  @return YES if you want to display the content, NO if you do not.
 *
 *  @discussion If you need to control the display of certain content items, you can override this method and inspect
 *  the content parameter and either return YES to continue the action or NO to suppress it.
 *  The default implementation always returns YES.
 */
- (BOOL) shouldShowContentView:(SWRLContent *)content;
/**
 *  Called before a local notification is generated.
 *
 *  @param note The UILocalNotification that is about to be display.  It can be altered or modified at this point.
 *  @param content  The content from which the notification has been generated.
 *  @return YES if you want to display the notification, NO if you do not.
 *
 *  @discussion If you need to control the display of certain notifications, you can override this method and inspect
 *  the content parameter and either return YES to continue the action or NO to suppress it.
 *  The default implementation always returns YES.
 */
- (BOOL) shouldShowNotification:(id)note content:(SWRLContent *)content;

/**
 *  Called before a local notification is generated. (async)
 *
 *  @param content  The content from which the notification has been generated.
 *  @param completion The completion to call when ready to display or reject
 *
 *  @discussion If you need to control the display of certain notifications, you can override this method and inspect
 *  the content parameter and either return YES to continue the action or NO to suppress it.  The default implementation
 *  of this method calls the synchronous version above.
 */
- (void) shouldShowNotificationForContent:(SWRLContent *)content completion:(void (^)(SWRLContent *, BOOL))completion;

/**
 * Called after the SWRLContentViewController has been shown.  The default implementation of
 * this method, simply forwards the message to the delegate bus as contentManager:didShowContentViewController.
 *
 * @param controller The SWRLContentViewController
 */
- (void) didShowContentViewController:(SWRLContentViewController *)controller;

/**
 * Called after the SWRLContentViewController has been dismissed.  The default implementation of
 * this method:
 *  [self.delegate contentManager:self didDismissContentViewController:controller;
 *  [self showToastView:[self toastViewForContent:controller.content]];
 *
 * @param controller The SWRLContentViewController (.contentViewController)
 */
- (void) didDismissContentViewController:(SWRLContentViewController *)controller;

/**
 * Called to create the toastView. The default implementation creates a SWRLToastView with a title and message attributes
 * derived from the notification associated with this content.  If you just want to modify attributes of the standard
 * toastView, call the super (default) implementation, make the changes and return that view.  If you do not want to
 * show a toastView, return nil.
 *
 * @param content  The content for which to provide a toast.
 * @return the view you want to use as the toast, or nil if no toast is desired.
 */
- (UIView *)toastViewForContent:(SWRLContent *)content;

/**
 * Called to show the toastView.
 *
 * The default implementation, calls size to fit on the toastView and then attempts to align the toast right
 * under the top view controller's navigation bar.
 * 
 * @param view the view to use as the toast view, should do nothing it nil is passed
 */
- (void)showToastView:(UIView *)view;

/**
 *  Called to activate a deep or external link.
 *  
 *  @param content The content containing the link to open.
 *  @discussion The default implementation of this method first calls the `shouldShowURLContent` and depending upon
 *  its return value, either logs an event that the show was suppressed, or calls openURL.
 */
- (void) showContentURL:(SWRLContent *)content;
/**
 *  Called to present interstitial content.
 *
 *  @param content The content containing the URL to display.
 *  @param wait Show the window immediately or wait for load first
 *
 *  @discussion The default implementation of this method creates the SWRLContentViewController if it does not exist
 *  and begins asynchronously loading that content.  When the content load completes, it calls the 
 *  `shouldShowContentView` method to see if the content should be display and logs an event if the display is
 *  suppressed, otherwise it presents the SWRLContentViewController from the result of calling contentViewPresenter.
 *  @warning It is not recommended that you override this method.  If for some reason you need to, you should make sure to
 *  call the implementation in `super`.
 */
- (void) showContentViewController:(SWRLContent *)content wait:(BOOL)wait;

/**
 *  Call this method to force display of the SWRLContentToastView
 *
 *  @param content content object from which the toast will be derived
 *  @discussion This forces the display of the toast view for the content supplied
 */
- (void) showContentToastView:(SWRLContent *)content;

/**
 *  Call this method to force display of the SWRLContentViewController.
 *  
 *  @discussion You would call this method if you wanted to implement a return to content button or other interface widget that
 *  allows your users to dismiss and relaunch the content view.
 *  In order to facilitate access to the SWRLContentManager from other parts of the program, you can call `[SWRLContentManager shared]`
 *  to access the last content manager created (usually there is only one).
 */
- (void) showContentViewController;

/**
 *  Call this method to clear the content view.  
 *  @param animated Use animation when removing the view
 *
 *  @discussion It will clear the view if it is currently presented otherwise it will do nothing.
 */
- (void) dismissContentViewController:(BOOL)animated;

/** 
 * Call this method to request content with a demo-code
 *
 * @param previewCode A preview code retrieved from the platform for a given creative.
 * @param completion Called when the content has been shown or there was an error
 * @discussion Makes a request for content with a given preview code and if successful, begins the normal
 * receive content flow which results in an interstitial view.  The completion is called in either case and
 * an error is passed or nil when successful.
 */
- (void) requestContentPreview:(NSString *)previewCode completion:(void (^)(NSError *))completion;

/** @name Other Methods */

/**
 * Override this to return a subclass of SWRLContentViewController with your own customizations.
 @ @return The view you want to use for the contentViewController. MUST be a subclass of SWRLContentViewController.
 */
- (SWRLContentViewController *)viewControllerForContent;

/**
 * Override this to handle any URLs that are opened either from a URL content or a URL widget from
 * any interstitial content.
 * @param url the url to open
 * @param completion the completion to call (with success/failure flag)
 */
- (void) openURL:(NSURL *)url completion:(void (^)(BOOL))completion;

/**
 *  Call this to access the last content manager created.  
 *  This method is provided as a convenience to save the programmer from having to keep a reference to the content manager
 *  or subclass it added when Swirl was started.
 */

+ (SWRLContentManager *)shared;

- (void)handleNotification:(id)object;

@end

/**
 *  The SWRLContentManagerDelegate protocol defines the methods used to receive beacon update from the SWRLContentManager.
 *  Upon receiving a content event, you can use the result to update your user interface or perform other actions.
 *  The methods of your delegate object are called from the thread associated with the dispatch queue that you used 
 *  when you added the delegate. See addDelegate:queue: addDelegate:queue:)
 */
@protocol SWRLContentManagerDelegate <NSObject>
@optional
/**
 *  Tells the delegate that a content request was made in response to a visit event.
 *  @param manager The SWRLContentManager reporting the event
 *  @param visit The visit object that triggered the content request.
 */
- (void) contentManager:(SWRLContentManager *)manager didRequestContentForVisit:(SWRLVisit *)visit;
/**
 *  Tells the delegate that content of type URL has been received.
 *  @param manager The SWRLContentManager reporting the event
 *  @param content The content object that was received.
 */
- (void) contentManager:(SWRLContentManager *)manager didReceiveContentURL:(SWRLContent *)content;
/**
 *  Tells the delegate that content of type Swirl has been received.
 *  @param manager The SWRLContentManager reporting the event
 *  @param content The content object that was received.
 */
- (void) contentManager:(SWRLContentManager *)manager didReceiveContentSwirl:(SWRLContent *)content;
/**
 *  Tells the delegate that content of type Custom has been received (asynch version) which allows custom content to go out to another server before completing.
 *  @param manager The SWRLContentManager reporting the event
 *  @param content The content object that was received.
 *  @param completion called when content is ready (content passed here may be different from original content)
 */
- (void) contentManager:(SWRLContentManager *)manager didReceiveContentCustom:(SWRLContent *)content completion:(void (^)(SWRLContent *content))completion;

/**
 * Tells the delegate that the content view controller has been shown
 *  @param manager The SWRLContentManager reporting the event
 *  @param controller   The SWRLContentViewController
 */
- (void) contentManager:(SWRLContentManager *)manager didShowContentViewController:(SWRLContentViewController *)controller;

/**
 * Tells the delegate that the content view controller has been closed.
 *  @param manager The SWRLContentManager reporting the event
 *  @param controller   The SWRLContentViewController
 */
- (void) contentManager:(SWRLContentManager *)manager didDismissContentViewController:(SWRLContentViewController *)controller;

@end

/**
 * The following events are produced by the ContentMnager for analytics
 */

extern NSString *const SWRLEventNotificationDisable;
extern NSString *const SWRLEventNotificationAbsent;
extern NSString *const SWRLEventNotificationRejected;
extern NSString *const SWRLEventNotificationSentBlocked;
extern NSString *const SWRLEventNotificationSentNoSound;
extern NSString *const SWRLEventNotificationSent;
extern NSString *const SWRLEventNotificationTimeout;
extern NSString *const SWRLEventNotificationOpen;
extern NSString *const SWRLEventNotificationDismiss;
extern NSString *const SWRLEventImpressionRejected;
extern NSString *const SWRLEventImpressionViewed;
extern NSString *const SWRLEventImpressionViewedMinimized;
extern NSString *const SWRLEventImpressionTouched;
extern NSString *const SWRLEventImpressionOfferRedeemed;
extern NSString *const SWRLEventImpressionWalletRedeeemed;
extern NSString *const SWRLEventImpressionTapArea;
extern NSString *const SWRLEventImpressionShared;
extern NSString *const SWRLEventImpressionSaved;
extern NSString *const SWRLEventImpressionTimeout; // content was received, but not foregrounded before 15m
extern NSString *const SWRLEventImpression1;
extern NSString *const SWRLEventImpression2;
extern NSString *const SWRLEventImpression3;
extern NSString *const SWRLEventImpression4;
extern NSString *const SWRLEventImpression5;
extern NSString *const SWRLEventImpression6;
extern NSString *const SWRLEventImpression7;
extern NSString *const SWRLEventImpression8;
extern NSString *const SWRLEventImpression9;
extern NSString *const SWRLEventImpression10;

#endif
