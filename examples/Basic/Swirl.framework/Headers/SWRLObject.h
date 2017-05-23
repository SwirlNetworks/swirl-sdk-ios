/*
 * SWRLObject.h
 * Copyright 2015-2017 Swirl Networks, Inc. All Rights Reserved.
 */

#ifndef __SWRLOBJECT__
#define __SWRLOBJECT__

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * SWRLObject is the base class for all objects returned from the platoform.  All objects
 * have an identifier, name and additional attributes.
 */
@interface SWRLObject : NSObject
/**
 * The platform assigned internal identifier.  This is globally unique.
 */
@property (nonatomic, readonly) NSString *      identifier;
/**
 * A human readable name if available.
 */
@property (nonatomic, readonly) NSString *      name;
/**
 * The collection of properties (including identifier and name) that were returned for this object from
 * the platform.
 */
@property (nonatomic, readonly) NSDictionary *  properties;


- (instancetype)initWithDictionary:(NSDictionary *)properties;

- (void) setProperties:(NSDictionary *)properties;

- (id)objectForKeyedSubscript:(NSString *)key;
- (NSString *)stringProperty:(NSString *)property;

@end

NS_ASSUME_NONNULL_END

#define IMPLEMENT_STRING_PROPERTY2(var,prop)	- (NSString *)var { return [self stringProperty:@#prop]; }
#define IMPLEMENT_STRING_PROPERTY(var)			IMPLEMENT_STRING_PROPERTY2(var, var)

#endif
