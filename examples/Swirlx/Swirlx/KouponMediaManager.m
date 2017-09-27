//
//  KouponMediaManager.m
//  Swirl
//
//  Created by Thomas Middleton on 7/26/17.
//
//
#import <Swirl/Swirl.h>
#import "KouponMediaManager.h"

#define KM_SUCCESS                  200
#define KM_BASE_URL                 @"https://consumer.sandbox1.kouponmedia.com/v2"
//#define KM_DEFAULT_VIEWER_URL       @"https://offer-sandbox1.kou.pn/OfferViewer/Redirect.aspx?property_code=swirl_mobilecapture&offers=%@&primary=%@"
#define KM_DEFAULT_VIEWER_URL       @"https://offer-sandbox1.kou.pn/OfferViewer/Redirect.aspx?property_code=swirl_mobilecapture&offers=%@"

@interface KouponMediaManager()
@property (nonatomic) NSString *apiKey;
@property (nonatomic) NSString *apiSecret;
@property (nonatomic) NSString *user;
@end

@implementation KouponMediaManager

- (NSString *)offerViewerURL:(NSString *)offer {
    return [NSString stringWithFormat:_offerViewerURL, offer, _user];
}

- (BOOL)offer:(NSDictionary *)offer isValid:(NSTimeInterval)now {
    return YES;
//    NSDateFormatter *format = [NSDateFormatter new];
//    [format setDateFormat:@"MM-dd-YY hh:mm:ss a"];    
//    NSTimeInterval start = [[format dateFromString:offer[@"offerStart"]] timeIntervalSince1970];
//    NSTimeInterval end   = [[format dateFromString:offer[@"offerEnd"]] timeIntervalSince1970];
//    return (now >= start && now <= end);
}

- (BOOL)offer:(NSDictionary *)offer hasIdentifier:(NSString *)identifier {
    return [identifier isEqual:[NSString stringWithFormat:@"%@", offer[@"offerId"]]];
}

- (void) kmRequest:(NSString *)requestURL body:(NSData *)body completion:(void (^)(int status, NSDictionary *result, NSError *error))completion {
    long timestamp = (long)now();
    requestURL = [requestURL stringByAppendingFormat:@"%@timestamp=%ld&identifier=%@", [requestURL hasSuffix:@"?"] ? @"" : @"&", timestamp, _apiKey];
    requestURL = [requestURL stringByAppendingFormat:@"&authSignature=%@", [SWRLCrypt hexDigest:[SWRLCrypt hmac_sha1:requestURL key:[_apiSecret dataUsingEncoding:NSUTF8StringEncoding]]]];
    [[SWRLAPI shared] jsonRequest:requestURL headers:nil data:body  completion:completion];
}

- (void) kmAddOffer:(NSString *)offer completion:(void (^)(NSDictionary *result, NSError *error))completion {
    NSString *addOfferURL = [NSString stringWithFormat:@"%@/%@/offers/%@?", KM_BASE_URL, _user, offer];
    [self kmRequest:addOfferURL body:[NSData data] completion:^(int status, NSDictionary *result, NSError *error) {
        if ([result[@"code"] intValue] == KM_SUCCESS) {
            NSString *offersURL = [NSString stringWithFormat:@"%@/%@/offers?", KM_BASE_URL, _user];
            [self kmRequest:offersURL body:nil completion:^(int status, NSDictionary *result, NSError *error) {
                if ([result[@"code"] intValue] == KM_SUCCESS) {
                    for (NSDictionary *info in result[@"Offers"]) {
                        if ([self offer:info hasIdentifier:offer] && [self offer:info isValid:now()]) {
                            completion(info, nil);
                            return;
                        }
                    }
                    completion(nil, SWRLErrorNotFound());
                } else
                    completion(nil, SWRLErrorUnknown());
            }];
        } else
            completion(nil, SWRLErrorUnknown());
    }];
}

- (void) contentManager:(SWRLContentManager *)manager didReceiveContentCustom:(SWRLContent *)content completion:(void (^)(SWRLContent *))completion {
    NSString *offer;
    
    if (![content.customType isEqualToString:@"koupon_media"] || (offer = content.attributes[@"offer_id"]) == nil)
        return; // do nothing
    
    [self kmAddOffer:offer completion:^(NSDictionary *result, NSError *error) {
        if (error == nil && result != nil) {
            NSDictionary *info = @{
                   @"type"            : @"url",
                   @"impression_id"   : content.identifier,
                   @"url"             : [self offerViewerURL:offer],
                   @"notification"    : @{
                           @"title"       : result[@"offerTitle"],
                           @"subtitle"    : result[@"offerSubtitle"],
                           @"text"        : result[@"offerDisclaimer"]
                           }
                   };
            completion([[SWRLContent alloc] initWithContent:info visit:content.visit fromNotification:content.fromNotification]);
        }
    }];
}

- (void) start {
    Log_d(@"start");
}

- (instancetype)initWithKey:(NSString *)key secret:(NSString *)secret user:(NSString *)user {
    if ((self = [super init]) != nil) {
        _apiKey         = key;
        _apiSecret      = secret;
        _user           = user;
        _offerViewerURL = KM_DEFAULT_VIEWER_URL;
    }
    return self;
}

@end

