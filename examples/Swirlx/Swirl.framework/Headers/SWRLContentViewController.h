//
//  SWRLContentViewController.h
//  Swirl
//
//  Created by Thomas Middleton on 5/7/16.
//
//

#import <UIKit/UIKit.h>

@interface SWRLContentViewController : UINavigationController<UIWebViewDelegate, UIGestureRecognizerDelegate>
@property (nonatomic)           UIViewController *webViewController;
@property (nonatomic)           UIWebView *       webView;
@property (nonatomic, readonly) SWRLContent *     content;
@property (nonatomic, readonly) NSArray *         toolbarItems;
@property (nonatomic, readonly) NSString *        emptyContentHtml;

- (instancetype) init;

- (void) showLoadingView;
- (void) hideLoadingView;

- (void) loadContent:(SWRLContent *)content completion:(void (^)(NSError *))completion;

@end
