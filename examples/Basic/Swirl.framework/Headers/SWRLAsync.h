/*
 * SWRLAsync.h
 * Copyright 2015-2017 Swirl Networks, Inc. All Rights Reserved.
 */

#ifndef __SWRLASYNCH__
#define __SWRLASYNCH__

#import <Foundation/Foundation.h>

@class SWRLTimer;

@interface SWRLAsync : NSObject
@property (nonatomic, readonly)   dispatch_queue_t    queue;
@property (nonatomic, readonly)   NSTimeInterval      start;
@property (nonatomic, readonly)   SWRLTimer *         timeout;
@property (nonatomic, readonly)   id                  object;

- (instancetype)initWithTag:(NSString *)tag object:(id)object timeout:(NSTimeInterval)timeout queue:(dispatch_queue_t)queue
                 completion:(void (^)(NSError *))completion operation:(void (^)(void))operation;

- (void) setTag:(NSString *)tag object:(id)object timeout:(NSTimeInterval)timeout queue:(dispatch_queue_t)queue
     completion:(void (^)(NSError *))completion operation:(void (^)(void))operation;

- (void) executeWithTag:(NSString *)tag object:(id)object  timeout:(NSTimeInterval)timeout queue:(dispatch_queue_t)queue
                 completion:(void (^)(NSError *))completion operation:(void (^)(void))operation;

- (void) executeWithObject:(id)object;
- (void) execute;
- (void) cancel;

- (void) complete:(void (^)(NSError *))completion error:(NSError *)error;

- (void) completeWithError:(NSError *)error object:(id)object reset:(BOOL)reset;
- (void) completeWithError:(NSError *)error object:(id)object;
- (void) completeWithError:(NSError *)error;
- (void) completeWithObject:(id)object;
- (void) complete;

- (void) lock;
- (void) unlock;

+ (SWRLAsync *)asyncWithTag:(NSString *)tag object:(id)object timeout:(NSTimeInterval)timeout queue:(dispatch_queue_t)queue
                       completion:(void (^)(NSError *))completion operation:(void (^)(void))operation;
@end

#endif
