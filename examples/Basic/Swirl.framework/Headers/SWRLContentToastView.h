/*
 * SWRLContentToastView.h
 * Copyright 2015-2016 Swirl Networks, Inc. All Rights Reserved.
 */

#ifndef __SWRLCONTENTTOASTVIEW__
#define __SWRLCONTENTTOASTVIEW__

#import "SWRLContent.h"
#import "SWRLToastView.h"

/**
 * A SWRLContentToastView is used to display a 'return-to-content' control after the user has dismissed the content view.  The toast view
 * offers a convenient way for application developers integrating the framework to provide a return to content button without having
 * to put one into their current interface.
 *
 * By default, the content is rendered similarly to a notification and uses the same alertTitle, alertBody and timestamp as those
 * generated for a background push notification.
 *
 * The toast view allows the user to swipe left to expose a 'Delete' control to remove the view and to swipe right to collapse
 * it to the right side of the screen to get it out of the way, but to still have access to it.
 *
 * This is the default view created by the SWRLContentManager and stored in contentToastView when it is active.  Developers
 * can override methods in SWRLContentManager in order to alter this view or eliminate it entirely.
 * 
 * There is also a startup option (SWRLSettingContentShowToast) turn this behavior off, the default is ON.
 */

@interface SWRLContentToastView : SWRLToastView
- (instancetype) initWithContent:(SWRLContent *)content actionHandler:(void (^)(SWRLToastView *view, BOOL))actionHandler;
@end

#endif
