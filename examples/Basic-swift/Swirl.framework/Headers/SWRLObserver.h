/*
 * SWRLStore.h
 * Copyright 2015-2018 Swirl Networks, Inc. All Rights Reserved.
 */

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@protocol SWRLObserver <NSObject>
@optional
- (void) didAddToObservers:(id)observers queue:(nullable dispatch_queue_t)queue;
@end

@interface SWRLObservers : NSProxy
- (instancetype) init;

- (void) addObserver:(id)observer;
- (void) addObserver:(id)observer queue:(dispatch_queue_t)queue;
- (void) removeObserver:(id)observer;
- (id)   findObserverOfClass:(Class)aclass;

- (void) suspend;
- (void) resume;

- (void) postObject:(id)object;
- (void) postMessage:(SEL)selector;
- (void) postMessage:(SEL)selector withObject:(nullable id)object;
- (void) postMessage:(SEL)selector withObject:(nullable id)object withObject:(nullable id)object2;
- (void) postMessage:(SEL)selector observers:(NSArray *)observers;

+ (SWRLObservers *)shared;
@end

@interface SWRLDelegateObserver : NSObject
@property (weak) id target;
@property (weak) id observer;

+ (id) observerWithTarget:(id)target observer:(id)listener;
@end


NS_ASSUME_NONNULL_END
