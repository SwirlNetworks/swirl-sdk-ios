//
//  SWRLContentManager.h
//  Swirl
//
//  Created by Thomas Middleton on 12/28/15.
//
//

#import <Foundation/Foundation.h>
#import <Swirl/SWRLManager.h>
#import <Swirl/SWRLVisitManager.h>
#import <Swirl/SWRLContent.h>
#import <Swirl/SWRLContentViewController.h>

/**
 * A component which consumes Visit objects and events and requests content through the API. If content is returned, then depending upon application state and SD
 * settings, it is responsible for displaying OS notifications and launching a content view or an application deep link. This component is not part of the default 
 * set of managers that are loaded and users who want content services will add this object or a subclass of this object to the bus at startup.
 */

@interface SWRLContentManager : SWRLManager<SWRLVisitManagerDelegate>
@property (nonatomic, readonly) SWRLVisit *                   recent;                   // current or last context
@property (nonatomic, readonly) SWRLContent *                 lastContent;              // last piece of content
@property (nonatomic, readonly) UIViewController *            contentViewPresenter;     // override
@property (nonatomic, readonly) SWRLContentViewController *   contentViewController;    // override

- (BOOL) shouldShowURLContent:(SWRLContent *)content;
- (BOOL) shouldShowContentView:(SWRLContent *)content;
- (BOOL) shouldShowNotification:(UILocalNotification *)note content:(SWRLContent *)content;

- (void) didReceiveContentURL:(SWRLContent *)content;
- (void) didReceiveContentSwirl:(SWRLContent *)content;
- (void) didReceiveContentCustom:(SWRLContent *)content;
- (void) didReceiveContent:(SWRLContent *)content notify:(BOOL)notify;

- (void) showContentURL:(SWRLContent *)content;
- (void) showContentViewController:(SWRLContent *)content;
- (void) showContentViewController;

+ (SWRLContentManager *)shared;

@end

/**
 * Callbacks from the ContentManager
 */
@protocol SWRLContentManagerDelegate <NSObject>
- (void) contentManager:(SWRLContentManager *)manager didReceiveContentURL:(SWRLContent *)content;
- (void) contentManager:(SWRLContentManager *)manager didReceiveContentSwirl:(SWRLContent *)content;
- (void) contentManager:(SWRLContentManager *)manager didReceiveContentCustom:(SWRLContent *)content;

@end



