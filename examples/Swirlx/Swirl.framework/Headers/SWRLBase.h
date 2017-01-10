/*
 * SWRLBase.h
 * Copyright 2015-2016 Swirl Networks, Inc. All Rights Reserved.
 */

#ifndef __SWRLBASE__
#define __SWRLBASE__

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import <CoreBluetooth/CoreBluetooth.h>
#import <PassKit/PassKit.h>

#define SWRLSwirlDomain                 @"com.swirl"
#define SWRLSwirlVersion                @"3.2.1"
#define SWRLCachePath                   @"~/Library/Caches/"

#define NSErrorFromException(d, e)      [NSError errorWithDomain:d code:-1 userInfo:\
@{  NSLocalizedDescriptionKey : [NSString stringWithFormat:@"Exception: %@", exception.name], \
NSLocalizedFailureReasonErrorKey : exception.reason }]

#define NSError(d,ecode,msg)            [NSError errorWithDomain:d code:ecode userInfo:@{NSLocalizedDescriptionKey:msg}]

#define SWRLError(ecode,msg)            NSError(SWRLSwirlDomain,ecode,msg)
#define SWRLErrorFromException(e)       NSErrorFromException(SWRLSwirlDomain, e)
#define SWRLErrorUnknown()              NSError(SWRLSwirlDomain, -1, @"unknown")
#define SWRLErrorDisabled()             NSError(SWRLSwirlDomain, -2, @"API disabled")

#define weak_self_t                     typeof(self) __weak


// =====================================================================================================================
// DEBUG DEFINES
// =====================================================================================================================

#if DEBUG
#define if_dbg(X)						X
#define if_not_dbg(X)
#define assert_dbg(x, fmt, args...)     if (!(x)) { NSLog(@"%s (%d) " fmt, __PRETTY_FUNCTION__, __LINE__, ##args); assert(x); }
#define assert_main_thread()			assert_dbg([NSThread isMainThread], @"not main thread")
#else
#define if_dbg(X)
#define if_not_dbg(X)					X
#define assert_dbg(x, fmt, args...)
#define assert_main_thread()
#endif

// =====================================================================================================================
// LOG
// =====================================================================================================================

#define Log_a
#define Log_e(fmt, args...)             SWRLLog(@(__FILE__), @"E", fmt, ##args)
#define Log_w(fmt, args...)             SWRLLog(@(__FILE__), @"W", fmt, ##args)
#define Log_i(fmt, args...)             SWRLLog(@(__FILE__), @"I", fmt, ##args)
#if DEBUG
#define Log_d(fmt, args...)             SWRLLog(@(__FILE__), @"D", fmt, ##args)
#define Log_v(fmt, args...)             SWRLLog(@(__FILE__), @"V", fmt, ##args)
#define Log_t(fmt, args...)             SWRLLog_toast(@(__FILE__), fmt, ##args)
#else
#define Log_d(fmt, args...)
#define Log_v(fmt, args...)
#define Log_t(fmt, args...)
#endif

void SWRLLog(NSString *tag, NSString *level, NSString *const fmt, ...) NS_FORMAT_FUNCTION(3,4);
void SWRLLog_toast(NSString *tag, NSString *const fmt, ...) NS_FORMAT_FUNCTION(2,3);

// =====================================================================================================================
// TIME
// =====================================================================================================================

#define now()                           [[NSDate date] timeIntervalSince1970]
#define ISO8601BASIC                    @"yyyyMMdd'T'HHmmssZ"
#define SECONDS(x)                      ((x))
#define MINUTES(x)                      (SECONDS(x)*60.0)
#define HOURS(x)                        (MINUTES(x)*60.0)
#define END_OF_TIME                     DBL_MAX
#define format_ts(t)                    [SWRLUtil dateStringWithFormat:ISO8601BASIC interval:t]
#define format_timestamp(t)             [NSString stringWithFormat:@"%.3f", t]

#define empty_if_nil(s)                 (s?s:@"")

// =====================================================================================================================
// DESCRIPTION
// =====================================================================================================================

#define EXTERN_DESCRIPTION(T)			OBJC_EXTERN NSString *__attribute__((overloadable)) description(T V)

// =====================================================================================================================
// DICTIONARY
// =====================================================================================================================

NS_INLINE id objectForKey(NSDictionary *d, NSString *kp, id dv)                 { id v = [d valueForKeyPath:kp]; return v ? v : dv; }
NS_INLINE NSString *stringForKey(NSDictionary *d, NSString *kp, NSString *dv)   { id v = [d valueForKeyPath:kp]; return v ? v : dv; }
NS_INLINE BOOL boolForKey(NSDictionary *d, NSString *kp, BOOL dv)               { id v = [d valueForKeyPath:kp]; return v ? [v boolValue] : dv; }
NS_INLINE int intForKey(NSDictionary *d, NSString *kp, int dv)                { id v = [d valueForKeyPath:kp]; return v ? [v intValue] : dv; }
NS_INLINE double doubleForKey(NSDictionary *d, NSString *kp, double dv)         { id v = [d valueForKeyPath:kp]; return v ? [v doubleValue] : dv; }
NS_INLINE NSTimeInterval intervalForKey(NSDictionary *d, NSString *kp, NSTimeInterval dv) { id v = [d valueForKeyPath:kp]; return v ? [v doubleValue] : dv; }

NS_INLINE NSArray *arrayForKey(NSDictionary *d, NSString *k) { id value = objectForKey(d,k,nil);
    if ([value isKindOfClass:[NSArray class ]]) return value;
    if ([value isKindOfClass:[NSString class]]) return [value componentsSeparatedByString:@","];
    return [NSArray array];
}

#endif
