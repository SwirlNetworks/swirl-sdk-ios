//
//  SWRLVisit.h
//  Swirl
//
//  Created by Thomas Middleton on 12/28/15.
//
//

#import <Foundation/Foundation.h>
#import <Swirl/SWRLLocation.h>


@interface SWRLVisit : NSObject
@property (nonatomic, readonly) SWRLLocation *		location;
@property (nonatomic, readonly)	NSDate *			arrivalDate;
@property (nonatomic, readonly)	NSDate *			departureDate;
@property (nonatomic, readonly) NSTimeInterval		dwellTime;
@property (nonatomic, readonly) NSTimeInterval      elapsedTime;
@property (nonatomic, readonly) NSDictionary *      userInfo;

- (instancetype) initWithLocation:(SWRLLocation *)location visit:(SWRLVisit *)visit;
- (instancetype) parentVisit;

- (NSTimeInterval) intervalSinceDeparture;

@end
