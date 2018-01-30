//
//  WOWZStreamConfig.h
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

#import "WOWZMediaConfig.h"
#import "WOWZData.h"

/*!
 @class WOWZStreamConfig
 @discussion The WOWZStreamConfig class provides configuration properties for the streaming connection
 */
@interface WOWZStreamConfig : WOWZMediaConfig <NSMutableCopying, NSCopying, NSCoding>

#pragma mark - Properties -

/*!
 *  The fully-qualified connection URL for this config
 */
@property (nonatomic, strong, nullable) NSString *hostAddress;

/*!
 *  The server connection port number. Default is 1935
 */
@property (nonatomic, assign) NSUInteger portNumber;

/*!
 *  The name of the live streaming application
 */
@property (nonatomic, strong, nullable) NSString *applicationName;

/*!
 *  The name of the live streaming stream
 */
@property (nonatomic, strong, nullable) NSString *streamName;

/*!
 *  The user name for Source Authentication
 */
@property (nonatomic, strong, nullable) NSString *username;

/*!
 *  The password for Source Authentication
 */
@property (nonatomic, strong, nullable) NSString *password;
/*!
 *  The connection parameters passed as the query string at connect time
 */
@property (nonatomic, strong, nullable) WOWZDataMap *connectionParameters;


#pragma mark - Public Instance Methods -

/*!
 *  Initializes a WOWZStreamConfig instance with a given WOWZFrameSizePreset
 *
 *  @param preset The WOWZFrameSizePreset for this config
 *
 *  @return An initialized WOWZStreamConfig instance
 */
- (nonnull instancetype) initWithPreset:(WOWZFrameSizePreset)preset;

/*!
 *  Validates that the minimum set of property values have been specified necessary to initiate a live streaming broadcast
 *
 *  @return nil if the minimum set of property values have been specified; otherwise, an NSError object describing
 *  the first encountered validation failure.
 */
- (nullable NSError *) validateForBroadcast;

/*!
 *  Copy the reciever's settings to the given WOWZStreamConfig
 *
 *  @param other The WOWZStreamConfig being copied to
 */
- (void) copyTo:(nonnull WOWZStreamConfig *)other;

@end
