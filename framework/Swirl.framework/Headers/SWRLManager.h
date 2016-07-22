//
//  SWRLManager.h
//  Swirl
//
//  Created by Thomas Middleton on 11/20/15.
//
//

#ifndef SWRLManager_h
#define SWRLManager_h

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
