/*
 * SWRLManager.h
 * Copyright 2015-2016 Swirl Networks, Inc. All Rights Reserved.
 */

#ifndef __SWRLMANAGER__
#define __SWRLMANAGER__

#import <Foundation/Foundation.h>
#import <Swirl/SWRLObserver.h>

NS_ASSUME_NONNULL_BEGIN

@protocol SWRLManager <SWRLObserver>
- (void) start;
- (void) stop;
@end

@interface SWRLManager : NSObject<SWRLManager>
@property (nonatomic, readonly) dispatch_queue_t  queue;
@property (nonatomic, readonly) NSOperationQueue *opqueue;
@property (nonatomic, readonly) id                delegate;

- (void) start;
- (void) stop;

@end


NS_ASSUME_NONNULL_END

#endif /* SWRLManager_h */
