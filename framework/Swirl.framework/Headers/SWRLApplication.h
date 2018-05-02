/*
 * SWRLApplication.h
 * Copyright 2015-2018 Swirl Networks, Inc. All Rights Reserved.
 */

#ifndef __SWRLAPPLICATION__
#define __SWRLAPPLICATION__

#import <Foundation/Foundation.h>

// =====================================================================================================================
// SWRApplication
// =====================================================================================================================

@interface SWRLApplication : NSObject
@property (nonatomic, readonly) UIApplicationState  state;                  // thread safe cache of UIApplicatoinState
@property (nonatomic, readonly) BOOL                isStarting;             // true if application starting, false otherwise
@property (nonatomic, readonly) BOOL                isBackground;           // true if in background, false otherwise
@property (nonatomic, readonly) NSTimeInterval      timeRemaining;          // 999.0 if in foreground, seconds remaining otherwise
@property (nonatomic)           NSTimeInterval      backgroundTime;         // sets default time to request on background events/starts. Default: 0

- (void) extendBackgroundTime:(NSTimeInterval)delta event:(NSString *)event;

+ (void) openURL:(NSURL *)url completion:(void (^)(BOOL))completion;
+ (void) openURL:(NSURL *)url options:(NSDictionary *)options completion:(void (^)(BOOL))completion;

+ (instancetype)shared;

@end

EXTERN_DESCRIPTION(UIApplicationState);

#endif
