/*
 * SWRLUtil.h
 * Copyright 2015-2016 Swirl Networks, Inc. All Rights Reserved.
 */

#ifndef __SWRLUTIL__
#define __SWRLUTIL__

#import <Foundation/Foundation.h>

// =====================================================================================================================
// SWRLCrypt
// =====================================================================================================================

@interface SWRLCrypt : NSObject
+ (NSData *)sha1:(NSString *)source;
+ (NSData *)hmac_sha1:(NSString *)source key:(NSData *)key;
+ (NSData *)sha256:(NSString *)source;
+ (NSData *)hmac_sha256:(NSString *)source key:(NSData *)key;
+ (NSData *)encrypt:(NSData *)input key:(NSData *)key;
+ (NSData *)decrypt:(NSData *)input key:(NSData *)key;
+ (NSData *)decrypt:(NSData *)input iv:(NSData *)iv key:(NSData *)key padding:(BOOL)padding;
+ (NSString *)hexDigest:(NSData *)data;
+ (NSString *)hexDigest:(NSData *)data offset:(int)off;
+ (NSString *)hexString:(NSData *)data;
+ (NSString *)randomString:(int)length;
@end

// =====================================================================================================================
// SWRLData
// =====================================================================================================================

@interface SWRLData : NSObject
+ (NSData *)dataWithBase64String:(NSString *)base64String;
+ (NSData *)dataWithHexString:(NSString *)hexString;
+ (NSString *)stringWithData:(NSData *)data;
+ (NSString *)hexStringWithData:(NSData *)data;
@end

// =====================================================================================================================
// SWRLJSON
// =====================================================================================================================

@interface SWRLJSON : NSObject
+ (NSData *)dataWithObject:(id)object error:(NSError **)error;
+ (id)objectWithData:(NSData *)data error:(NSError **)error;
+ (id)objectWithData:(NSData *)data key:(NSData *)key error:(NSError **)error;
+ (NSString *)stringWithObject:(id)object;
@end

// =====================================================================================================================
// SWRLUtil
// =====================================================================================================================

@interface SWRLUtil : NSObject
+ (uint32_t)crc32:(uint32_t)crc data:(const uint8_t *)data length:(size_t)length;
+ (NSString *)dateStringWithFormat:(NSString *)format interval:(NSTimeInterval)interval;
+ (NSString *)dateStringWithFormat:(NSString *)format date:(NSDate *)date;
+ (NSString *)dateStringWithFormat:(NSString *)format date:(NSDate *)date locale:(NSLocale *)locale tzoffset:(NSInteger)tzoffset;
+ (NSString *)formatSameDayTime:(NSTimeInterval)time now:(NSTimeInterval)now;
+ (NSString *)timestamp_RFC3339;
+ (NSDictionary *)dictionaryWithLocation:(CLLocation *)location;
+ (CLLocation *)locationWithDictionary:(NSDictionary *)dictionary;

+ (BOOL) hasBackgroundMode:(NSString *)mode;
@end

// =====================================================================================================================
// SWRLURL
// =====================================================================================================================

@interface SWRLURL : NSObject
+ (NSString *)portWithURL:(NSURL *)url;
+ (NSDictionary *)queryParamsWithURL:(NSURL *)url;
@end

// =====================================================================================================================
// SWRLImage
// =====================================================================================================================

@interface SWRLImage : NSObject
+ (UIImage *)scaleImage:(UIImage *)image scale:(double)scale radius:(CGFloat)radius;
+ (UIImage *)imageFromView:(UIView *)view;
@end

// =====================================================================================================================
// SWRLBackground
// =====================================================================================================================

@interface SWRLApplication : NSObject
+ (void) openURL:(NSURL *)url completion:(void (^)(BOOL))completion;
+ (void) openURL:(NSURL *)url options:(NSDictionary *)options completion:(void (^)(BOOL))completion;

+ (NSTimeInterval)  timeRemaining;
+ (void)            requestTime;
+ (BOOL)            background;
@end

#endif
