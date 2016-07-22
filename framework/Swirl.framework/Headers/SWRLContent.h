//
//  SWRLContent.h
//  Swirl
//
//  Created by Thomas Middleton on 5/6/16.
//
//

#import <Swirl/SWRLBase.h>
#import <Swirl/SWRLVisit.h>

/**
 * The type of content delivered
 *
 */
typedef NS_ENUM(int, SWRLContentType) {
    /**
     * Custom creative for delivering customr JSON attributes
     */
    SWRLContentTypeCustom = 0,
    /**
     * URL creative for deep-link or third party application launch
     */
    SWRLContentTypeURL,
    /**
     * Swirl create for web content displayed via interstitial
     */
    SWRLContentTypeSwirl,
};

extern NSString *const SWRLNotificationContentKey;

@interface SWRLContent : NSObject
@property (nonatomic, readonly) NSString *           identifier;            // impression identifier
@property (nonatomic, readonly) SWRLVisit *          visit;                 // visit information
@property (nonatomic, readonly) NSDictionary *       content;               // raw-content

@property (nonatomic, readonly) SWRLContentType      type;                  // content-type
@property (nonatomic, readonly) NSTimeInterval       received;              // timestamp
@property (nonatomic, readonly) UILocalNotification *notification;          // notification
@property (nonatomic, readonly) NSURL *              url;
@property (nonatomic, readonly) NSURL *              fallbackURL;
@property (nonatomic, readonly) NSDictionary *       attributes;            // custom-attributes
@property (nonatomic, readonly) UIImage *            thumbnail;

- (instancetype)initWithContent:(NSDictionary *)content visit:(SWRLVisit *)visit;
- (void) setReceived:(NSTimeInterval)received;
- (void) setThumbnail:(UIImage *)thumbnail;

@end

