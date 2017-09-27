//
//  KouponMediaManager.h
//  Swirl
//
//  Created by Thomas Middleton on 7/26/17.
//
//

#import <Swirl/Swirl.h>

NS_ASSUME_NONNULL_BEGIN

@interface KouponMediaManager : SWRLManager <SWRLContentManagerDelegate>
@property (nonatomic) NSString *offerViewerURL;    // can have a single %@ for <offer>

- (instancetype)initWithKey:(NSString *)key secret:(NSString *)secret user:(NSString *)user;

@end

NS_ASSUME_NONNULL_END
