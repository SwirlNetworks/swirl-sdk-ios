/*
 * SWRLPeripheral.h
 * Copyright 2015-2017 Swirl Networks, Inc. All Rights Reserved.
 */

#ifndef __SWRLPERIPHERAL__
#define __SWRLPERIPHERAL__

#import <Foundation/Foundation.h>
#import <Swirl/SWRLAsync.h>

@class CBCentralManager, CBPeripheral;

@interface SWRLPeripheral : SWRLAsync
@property (nonatomic, readonly) NSString *name;
@property (nonatomic, readonly) NSUUID *identifier;
@property (nonatomic, readonly) NSNumber *rssi;
@property (nonatomic, readonly) NSArray<CBCharacteristic*> *characteristics;
@property (nonatomic, readonly) NSMutableDictionary<NSString*,NSData*> *changes;

- (instancetype)initWithPeripheral:(CBPeripheral *)peripheral central:(CBCentralManager *)central;

- (BOOL) disconnected;
- (BOOL) connecting;
- (BOOL) connected;

- (void) updateRSSI;

- (void) connectWithTimeout:(NSTimeInterval)timeout queue:(dispatch_queue_t)queue completion:(void (^)(NSError *))completion;
- (void) discoverServices:(NSArray<NSString*>*)services descriptors:(BOOL)descriptors timeout:(NSTimeInterval)timeout completion:(void (^)(NSError *))completion;
- (void) discoverAndReadValues:(NSArray<NSString*>*)keyStrings descriptors:(BOOL)descriptors timeout:(NSTimeInterval)timeout completion:(void (^)(NSError *))completion;
- (void) connectDiscoverAndReadAll:(BOOL)descriptors force:(BOOL)force timeout:(NSTimeInterval)timeout queue:(dispatch_queue_t)queue completion:(void (^)(NSError *))completion;

- (void) readValuesForKeys:(NSArray<NSString*>*)valueKeys timeout:(NSTimeInterval)timeout completion:(void (^)(NSError *))completion;
- (void) readValueForKey:(NSString *)key timeout:(NSTimeInterval)timeout completion:(void (^)(CBCharacteristic *, NSData *, NSError *))completion;
- (void) readValueForCharacteristic:(CBCharacteristic *)characteristic timeout:(NSTimeInterval)timeout completion:(void (^)(NSError *))completion;

- (void) notifyValue:(BOOL)notify forKey:(NSString *)key completion:(void (^)(CBCharacteristic *, NSData *, NSError *))completion;

- (void) writeValues:(NSArray<NSDictionary<NSString *,id> *> *)values timeout:(NSTimeInterval)timeout completion:(void (^)(NSError *))completion;
- (void) writeValue:(NSData *)value forKey:(NSString *)key timeout:(NSTimeInterval)timeout completion:(void (^)(NSError *))completion;
- (void) writeValue:(NSData *)value forCharacteristic:(CBCharacteristic *)characteristic timeout:(NSTimeInterval)timeout completion:(void (^)(NSError *))completion;

- (void) disconnectAndWait:(NSTimeInterval)timeout completion:(void (^)(NSError *))completion;

- (void) wait:(NSTimeInterval)timeout completion:(void (^)(NSError *))completion;

- (CBService *)serviceForKey:(NSString *)serviceKey;
- (CBCharacteristic *) characteristicForKey:(NSString *)characteristicKey;
- (NSString *)keyForCharacteristic:(CBCharacteristic *)characteristic;
- (void) clearCharacteristics;

- (void) setValue:(NSData *)value forKey:(NSString *)key;
- (NSData *) valueForKey:(NSString *)key;

- (uint8_t) byteForKey:(NSString *)key;
- (uint16_t) shortForKey:(NSString *)key;
- (void) setByte:(uint8_t)value forKey:(NSString *)key;

+ (SWRLPeripheral *)activePeripheral:(CBPeripheral *)peripheral;
+ (SWRLPeripheral *)peripheralWithPeripheral:(CBPeripheral *)peripheral central:(CBCentralManager *)central;

// call from CBCentralManager delegate callbacks
+ (void) didFailToConnectPeripheral:(CBPeripheral *)peripheral error:(NSError *)error;
+ (void) didDisconnectPeripheral:(CBPeripheral *)peripheral error:(NSError *)error;
+ (void) didConnectPeripheral:(CBPeripheral *)peripheral;

@end

OBJC_EXTERN NSString *__attribute__((overloadable)) description(CBCharacteristic *ch);

#endif
