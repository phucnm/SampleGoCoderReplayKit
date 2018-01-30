//
//  WOWZData.h
//  WowzaGoCoderSDK
//
//  Copyright 2007 – 2016, Wowza Media Systems, LLC.  All rights
//  reserved.
//
//  The above copyright notice and this permission notice shall be
//  included in all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
//  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
//  OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
//  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
//  HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
//  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
//  OTHER DEALINGS IN THE SOFTWARE.
//

#import <Foundation/Foundation.h>

@class WOWZDataMap;
@class WOWZDataList;


/*!
 *  @typedef WOWZDataType
 *  @constant WOWZDataTypeNull A Null value (NSNull)
 *  @constant WOWZDataTypeString A string (NSString).
 *  @constant WOWZDataTypeBoolean A boolean (BOOL).
 *  @constant WOWZDataTypeDate A date (NSDate).
 *  @constant WOWZDataTypeInteger An integer (NSInteger).
 *  @constant WOWZDataTypeFloat A float (Float).
 *  @constant WOWZDataTypeDouble A double (Double).
 *  @constant WOWZDataTypeMap A WOWZDataMap.
 *  @constant WOWZDataTypeList A WOWZDataList.
 *  @discussion The allowed types of a WOWZDataItem.
 */
typedef NS_ENUM(NSUInteger, WOWZDataType) {
    WOWZDataTypeNull,
    WOWZDataTypeString,
    WOWZDataTypeBoolean,
    WOWZDataTypeDate,
    WOWZDataTypeInteger,
    WOWZDataTypeFloat,
    WOWZDataTypeDouble,
    WOWZDataTypeMap,
    WOWZDataTypeList
};

/*!
 *  @typedef WOWZDataCallback
 *  @param result The result data returned from a server module function.
 *  @param isError whether the server module function returned an error.
 *  @discussion This is the callback that a client would provide when calling
 *  a Wowza server module function.
 */
typedef void (^WOWZDataCallback)( WOWZDataMap * _Nullable result, BOOL isError);

/*!
 @class WOWZDataItem
 @discussion The WOWZDataItem class provides an interface encapsulating the various data items that represent server metadata that is sent and received by GoCoder.
 */
@interface WOWZDataItem : NSObject <NSMutableCopying, NSCopying, NSCoding>

/*!
 *  The type of this data item.
 */
@property (nonatomic, assign, readonly) WOWZDataType type;

#pragma mark - Class Methods

/*!
 *  Creates a new WOWZDataItem of type WOWZDataTypeInteger
 *
 *  @param value the integer value with which to initialize the item
 *
 *  @return An instance of WOWZDataItem
 */
+ (nonnull instancetype) itemWithInteger:(NSInteger)value;

/*!
 *  Creates a new WOWZDataItem of type WOWZDataTypeDouble
 *
 *  @param value the double value with which to initialize the item
 *
 *  @return An instance of WOWZDataItem
 */
+ (nonnull instancetype) itemWithDouble:(double)value;

/*!
 *  Creates a new WOWZDataItem of type WOWZDataTypeFloat
 *
 *  @param value the float value with which to initialize the item
 *
 *  @return An instance of WOWZDataItem
 */
+ (nonnull instancetype) itemWithFloat:(float)value;

/*!
 *  Creates a new WOWZDataItem of type WOWZDataTypeBool
 *
 *  @param value the bool value with which to initialize the item
 *
 *  @return An instance of WOWZDataItem
 */
+ (nonnull instancetype) itemWithBool:(BOOL)value;

/*!
 *  Creates a new WOWZDataItem of type WOWZDataTypeString
 *
 *  @param value the string value with which to initialize the item
 *
 *  @return An instance of WOWZDataItem
 */
+ (nonnull instancetype) itemWithString:(nonnull NSString *)value;

/*!
 *  Creates a new WOWZDataItem of type WOWZDataTypeDate
 *
 *  @param value the date value with which to initialize the item
 *
 *  @return An instance of WOWZDataItem
 */
+ (nonnull instancetype) itemWithDate:(nonnull NSDate *)value;

#pragma mark - Instance Methods

/*!
 *  Initialize a WOWZDataItem
 *
 *  @return An instance of WOWZDataItem of type WOWZDataTypeNull
 */
- (nonnull instancetype) init;

/*!
 *  Get the integer value of the WOWZDataItem
 *
 *  @return the integer value of the WOWZDataItem, or 0 if the item is not of type WOWZDataTypeInteger
 */
- (NSInteger) integerValue;

/*!
 *  Get the double value of the WOWZDataItem
 *
 *  @return the double value of the WOWZDataItem, or 0 if the item is not of type WOWZDataTypeDouble
 */
- (double) doubleValue;

/*!
 *  Get the float value of the WOWZDataItem
 *
 *  @return the float value of the WOWZDataItem, or 0 if the item is not of type WOWZDataTypeFloat
 */
- (float) floatValue;

/*!
 *  Get the bool value of the WOWZDataItem
 *
 *  @return the bool value of the WOWZDataItem, or 0 if the item is not of type WOWZDataTypeBoolean
 */
- (BOOL) boolValue;

/*!
 *  Get the string value of the WOWZDataItem
 *
 *  @return the string value of the WOWZDataItem, or nil if the item is not of type WOWZDataTypeString
 */
- (nullable NSString *)stringValue;

/*!
 *  Get the date value of the WOWZDataItem
 *
 *  @return the date value of the WOWZDataItem, or nil if the item is not of type WOWZDataTypeDate
 */
- (nullable NSDate *)dateValue;

/*!
 *  Get the map value of the WOWZDataItem
 *
 *  @return the map value of the WOWZDataItem, or nil if the item is not of type WOWZDataTypeMap
 */
- (nullable WOWZDataMap *)mapValue;

/*!
 *  Get the list value of the WOWZDataItem
 *
 *  @return the list value of the WOWZDataItem, or nil if the item is not of type WOWZDataTypeList
 */
- (nullable WOWZDataList *)listValue;

@end



/*!
 @class WOWZDataMap
 @discussion The WOWZDataMap class provides an interface encapsulating a map (or dictionary) of items that represent server metadata that is sent and received by GoCoder.
 */
@interface WOWZDataMap : WOWZDataItem

/*!
 *  The underlying NSMutableDictionary that stores the items in the map.
 */
@property (nonatomic, strong, readonly, nullable) NSMutableDictionary<NSString*, WOWZDataItem*> *data;

#pragma mark - Class Methods

/*!
 *  Creates a new WOWZDataMap and copies the items in dictionary to it's internal data map
 *
 *  @param dictionary the dictionary of WOWZDataItems that the caller wishes to initialize the WOWZDataMap with.
 *
 *  @return An instance of WOWZDataMap
 */
+ (nonnull instancetype) dataMapWithDictionary:(nonnull NSDictionary<NSString*, WOWZDataItem*> *)dictionary;


#pragma mark - Instance Methods

/*!
 *  Initialize a new WOWZDataMap with no items
 *
 *  @return An instance of WOWZDataMap
 */
- (nonnull instancetype) init;

/*!
 *  Initialize a new WOWZDataMap and copies the items in dictionary to it's internal data map
 *
 *  @param dictionary the dictionary of WOWZDataItems that the caller wishes to initialize the WOWZDataMap with.
 *
 *  @return An instance of WOWZDataMap
 */
- (nonnull instancetype) initWithDictionary:(nonnull NSDictionary<NSString*, WOWZDataItem*> *)dictionary;

/*!
 *  Add a integer (which will be converted to a WOWZDataItem) with given key to the internal map
 *
 *  @param value the integer value to add
 *  @param key the unique key for the new integer value
 */
- (void) setInteger:(NSInteger)value forKey:(nonnull NSString *)key;

/*!
 *  Add a double (which will be converted to a WOWZDataItem) with given key to the internal map
 *
 *  @param value the double value to add
 *  @param key the unique key for the new double value
 */
- (void) setDouble:(double)value forKey:(nonnull NSString *)key;

/*!
 *  Add a float (which will be converted to a WOWZDataItem) with given key to the internal map
 *
 *  @param value the float value to add
 *  @param key the unique key for the new float value
 */
- (void) setFloat:(float)value forKey:(nonnull NSString *)key;

/*!
 *  Add a bool (which will be converted to a WOWZDataItem) with given key to the internal map
 *
 *  @param value the bool value to add
 *  @param key the unique key for the new bool value
 */
- (void) setBool:(BOOL)value forKey:(nonnull NSString *)key;

/*!
 *  Add a string (which will be converted to a WOWZDataItem) with given key to the internal map
 *
 *  @param value the string value to add
 *  @param key the unique key for the new string value
 */
- (void) setString:(nullable NSString *)value forKey:(nonnull NSString *)key;

/*!
 *  Add a date (which will be converted to a WOWZDataItem) with given key to the internal map
 *
 *  @param value the date value to add
 *  @param key the unique key for the new date value
 */
- (void) setDate:(nullable NSDate *)value forKey:(nonnull NSString *)key;

/*!
 *  Add a WOWZDataItem with given key to the internal map
 *
 *  @param value the WOWZDataItem value to add
 *  @param key the unique key for the new WOWZDataItem value
 */
- (void) setItem:(nullable WOWZDataItem *)value forKey:(nonnull NSString *)key;

/*!
 *  Add a WOWZDataMap with given key to the internal map
 *
 *  @param value the WOWZDataMap value to add
 *  @param key the unique key for the new WOWZDataMap value
 */
- (void) setMap:(nullable WOWZDataMap *)value forKey:(nonnull NSString *)key;

/*!
 *  Add a WOWZDataList with given key to the internal map
 *
 *  @param value the WOWZDataList value to add
 *  @param key the unique key for the new WOWZDataList value
 */
- (void) setList:(nullable WOWZDataList *)value forKey:(nonnull NSString *)key;

/*!
 *  Remove an item from the internal map
 *
 *  @param key the key value to be removed
 */
- (void) remove:(nonnull NSString *)key;

@end

/*!
 @class WOWZDataList
 @discussion The WOWZDataList class provides an interface encapsulating a list (or array) of items that represent server metadata that is sent and received by GoCoder.
 */
@interface WOWZDataList : WOWZDataItem

/*!
 *  The underlying NSMutableArray that stores the items in the list.
 */
@property (nonatomic, strong, readonly, nullable) NSMutableArray<WOWZDataItem *> *elements;

#pragma mark - Class Methods

/*!
 *  Creates a new WOWZDataList and copies the items in array to it's internal list
 *
 *  @param array the array of WOWZDataItems that the caller wishes to initialize the WOWZDataList with.
 *
 *  @return An instance of WOWZDataList
 */
+ (nullable instancetype) dataListWithArray:(nonnull NSArray<WOWZDataItem *> *)array;

/*!
 *  Get the maximum size (number of elements) allowed in a WOWZDataList
 *
 *  @return an NSUInteger expressing the maximum size (number of elements) allowed in a WOWZDataList
 */
+ (NSUInteger) maximumSize;


#pragma mark - Instance Methods

/*!
 *  Initialize a new WOWZDataList with no elements
 *
 *  @return An instance of WOWZDataList
 */
- (nonnull instancetype) init;

/*!
 *  Initialize a new WOWZDataList and copy the items in array to it's internal list
 *
 *  @param array the array of WOWZDataItems that the caller wishes to initialize the WOWZDataList with.
 *
 *  @return An instance of WOWZDataList
 */
- (nullable instancetype) initWithArray:(nonnull NSArray<WOWZDataItem *> *)array;

/*!
 *  Add a integer (which will be converted to a WOWZDataItem) to the internal list
 *
 *  @param value the integer value to add
 */
- (void) addInteger:(NSInteger)value;

/*!
 *  Add a double (which will be converted to a WOWZDataItem) to the internal list
 *
 *  @param value the double value to add
 */
- (void) addDouble:(double)value;

/*!
 *  Add a float (which will be converted to a WOWZDataItem) to the internal list
 *
 *  @param value the float value to add
 */
- (void) addFloat:(float)value;

/*!
 *  Add a bool (which will be converted to a WOWZDataItem) to the internal list
 *
 *  @param value the bool value to add
 */
- (void) addBool:(BOOL)value;

/*!
 *  Add a string (which will be converted to a WOWZDataItem) to the internal list
 *
 *  @param value the string value to add
 */
- (void) addString:(nonnull NSString *)value;

/*!
 *  Add a date (which will be converted to a WOWZDataItem) to the internal list
 *
 *  @param value the date value to add
 */
- (void) addDate:(nonnull NSDate *)value;

/*!
 *  Add a WOWZDataItem to the internal list
 *
 *  @param value the WOWZDataItem value to add
 */
- (void) addItem:(nonnull WOWZDataItem *)value;

/*!
 *  Add a WOWZDataMap to the internal list
 *
 *  @param value the WOWZDataMap value to add
 */
- (void) addMap:(nonnull WOWZDataMap *)value;

/*!
 *  Add a WOWZDataList to the internal list
 *
 *  @param value the WOWZDataList value to add
 */
- (void) addList:(nonnull WOWZDataList *)value;


@end

