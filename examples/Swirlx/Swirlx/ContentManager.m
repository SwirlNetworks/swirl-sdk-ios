// =====================================================================================================================
// ContentManager,m
// Copyright 2015-2016, Swirl Networks, Inc.  All Rights Reserved..
// =====================================================================================================================

#import "ContentManager.h"

@interface ContentManager()
@property (nonatomic) SWRLToastView *toastView;
@end


@implementation ContentManager

- (BOOL) shouldShowNotification:(UILocalNotification *)note content:(SWRLContent *)content {
    // Can add custom code here to alter the notification or to suppress it
    return YES;
}

// =====================================================================================================================
// willShowContentViewController:
//  Uncomment this method to customize the content view controller before it is shown on screen
// =====================================================================================================================

//- (void) willShowContentViewController:(SWRLContentViewController *)controller {
//    controller.navigationBar.barTintColor = [UIColor redColor];
//    controller.webViewController.navigationItem.rightBarButtonItem = nil;
//    controller.webViewController.navigationItem.leftBarButtonItem = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemStop
//                                                                    target:controller action:@selector(close:)];
//    controller.webViewController.navigationItem.title = @"FOO";
//}

- (void) didShowContentViewController:(SWRLContentViewController *)controller {
    // call the super to forward this message to any other listeners
    [super didShowContentViewController:controller];
}

- (UIView *)toastViewForContent:(SWRLContent *)content {
    if (content) {
        SWRLToastView *toast = (SWRLToastView *)[super toastViewForContent:content];
        // change the color...
        //toast.textColor       = [UIColor whiteColor];
        //toast.backgroundColor = [UIColor orangeColor];
        return toast;
    }
    return nil;
}

@end
