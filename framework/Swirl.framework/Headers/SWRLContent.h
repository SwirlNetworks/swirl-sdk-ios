/*
 * SWRLContent
 * Copyright 2015-2016 Swirl Networks, Inc. All Rights Reserved.
 */

#ifndef __SWRLCONTENT__
#define __SWRLCONTENT__

#import <Swirl/SWRLBase.h>
#import <Swirl/SWRLVisit.h>

NS_ASSUME_NONNULL_BEGIN

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

/**
 * The key used for the notification userInfo dictionary to encode the raw content dictionary.
 */
extern NSString *const SWRLNotificationContentKey;

/**
 * Each SWRLContent object represents a unique impression. A SWRLContent object encapsulates information about content 
 * that was received for a given visit in response to a content request made by the SWRLContentManager.  
 * Content requests are made in response to visit events like starting a visit and updating dwell time for a visit.  
 * For content that requires a dwell trigger, the server will push back that information to the client and the client will 
 * automatically delay making further content requests until the dwell triggers have been reached.
 */
@interface SWRLContent : NSObject
/**
 * @name Accessing Attributes
 */

/**
 * The unique identifier (UUID) for this impression.
 */

@property (nonatomic, readonly) NSString *           identifier;
/**
 * The visit object associated with this content, usually the visit that triggered the content request.
 */
@property (nonatomic, nullable, readonly) SWRLVisit *visit;

/**
 * This NSDictionary is a representation of the raw JSON content response.
 */
@property (nonatomic, readonly) NSDictionary *       content;

/**
 * The content type whose value will be one of SWRLContentType.
 */
@property (nonatomic, readonly) SWRLContentType      type;
/**
 * The epoch (1/1/70) timestamp that represents when this content was originally received.
 */
@property (nonatomic, readonly) NSTimeInterval       received;

/**
 * The notification associated with this content.  You can access this field at any time to get a copy
 * of the notification that was sent or would be sent. Accessing this property does not cause
 * any notifications to be sent. 
 *
 * Notification are created with a userInfo dictionary that is: 
 * `@{ @"com.swirl" : @{ SWRLNotificationContentKey: self.content }}; 
 * which enables a SWRLContent object to be recreated from a notification.
 */
@property (nonatomic, readonly) UILocalNotification *notification;

/**
 * The URL associated with this content.  For SWRLContentTypeURL this is the deep link URL, For SWRLContentTypeSwirl this
 * is a URL representing a call to format an HTML impression.
 */
@property (nonatomic, nullable, readonly) NSURL *url;
/**
 * This URL is used if there is a problem with dispatching the target url.  This is primarily used for deep link content.
 */
@property (nonatomic, nullable, readonly) NSURL *fallbackURL;
/**
 * This dictionary contains any custom attributes associated with this creative as created and assigned using the 
 * platform.
 */
@property (nonatomic, nullable, readonly) NSDictionary *attributes;

/**
 * This is a thumbnail created of the creative.  This is only available if the creative has ever
 * been rendered on the screen.
 */
@property (nonatomic, nullable, readonly) UIImage *thumbnail;

- (instancetype)initWithContent:(NSDictionary *)content visit:(nullable SWRLVisit *)visit;
- (void) setReceived:(NSTimeInterval)received;
- (void) setThumbnail:(UIImage *)thumbnail;

@end

NS_ASSUME_NONNULL_END

#endif



