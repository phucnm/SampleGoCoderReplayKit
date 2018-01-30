//
//  WOWZStatus.h
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

/*!
 @discussion WOWZStatusNewBitrateKey refers to the entry in a WOWZStatus' data member that contains the NSNumber representation
 of a new bitrate value.
 */
extern NSString * __nonnull const WOWZStatusNewBitrateKey;

/*!
 @discussion WOWZStatusPreviousBitrateKey refers to the entry in a WOWZStatus' data member that contains the NSNumber representation
 of a previous bitrate value.
 */
extern NSString * __nonnull const  WOWZStatusPreviousBitrateKey;

/*!
 @class WOWZStatus
 @discussion The WOWZStatus is a thread-safe class for working with SDK component state and error properties.
 Client applications don't normally have any need for creating a WOWZStatus object.
 */
@interface WOWZStatus : NSObject <NSMutableCopying, NSCopying>

/*!
 *  @typedef WOWZState
 *  @constant WOWZStateIdle The broadcasting ccomponent or session is idle; i.e. not broadcasting.
 *  @constant WZStateStarting The broadcasting component or session is starting up or initializing.
 *  @constant WOWZStateRunning The broadcasting component or session is broadcasting or running.
 *  @constant WOWZStateStopping The broadcasting component or session is shutting down.
 *  @constant WOWZStateBuffering The broadcasting component or session is buffering.
 *  @constant WOWZStateReady The broadcasting component or session is in a ready state or has been successfully initialized.
 *  @discussion The component state values.
 */
typedef NS_ENUM(NSUInteger, WOWZState) {
    WOWZStateIdle = 0,
    WOWZStateStarting,
    WOWZStateRunning,
    WOWZStateStopping,
    WOWZStateBuffering,
    WOWZStateReady
};

/*!
 *  @typedef WOWZEvent
 *  @constant WOWZEventNone No event.
 *  @constant WOWZEventLowBandwidth Network bandwidth was insufficient to keep up with the video broadcast settings. In this case, the encoder may attempt to recover by reducing bitrate and/or frame rate.
 *  @constant WOWZEventBitrateReduced Sent when the encoder reduces the bitrate to compensate for low bandwidth conditions. The WOWZStatus' data
 *  dictionary in this case will contain 2 keys with associated NSNumber values: WOWZStatusNewBitrateKey and WOWZStatusPreviousBitrateKey.
 *  @constant WOWZEventBitrateIncreased Sent when the encoder increases the the bitrate after having previously reduced it. The bitrate will never
 *  increase beyond the original bitrate specified in the configuration settings for the streaming session. The WOWZStatus' data dictionary in this
 *  case will contain 2 keys with associated NSNumber values: WOWZStatusNewBitrateKey and WOWZStatusPreviousBitrateKey.
 *  @constant WOWZEventEncoderPaused Sent when the encoder stops sending frames while waiting for queued frames to catch up. Typically, this would happen while the encoder is simultaneously reducing the bitrate to compensate for low bandwidth conditions.
 *  @constant WOWZEventEncoderResumed Sent when a previously paused encoder resumes.
 *  @discussion The component event values.
 */
typedef NS_ENUM(NSUInteger, WOWZEvent) {
    WOWZEventNone = 0,
    WOWZEventLowBandwidth,
    WOWZEventBitrateReduced,
    WOWZEventBitrateIncreased,
    WOWZEventEncoderPaused,
    WOWZEventEncoderResumed
};

#pragma mark - Properties

/*!
 *  The current state of the broadcast session
 */
@property (nonatomic) WOWZState state;

/*!
 *  The current state of the broadcast session
 */
@property (nonatomic) WOWZEvent event;

/*!
 *  The last error reported by the broadcast session.
 */
@property (nonatomic, strong, nullable) NSError * error;

/*!
 *  Data related to the status. May be null.
 */
@property (nonatomic, strong, nullable) NSDictionary * data;

#pragma mark - Class Methods

/*!
 *  Returns a WOWZStatus object with a given state
 *
 *  @param aState The state to initialize with
 *
 *  @return An initialized WOWZStatus object
 */
+ (nonnull instancetype) statusWithState:(WOWZState)aState;

/*!
 *  Returns a WOWZStatus object with a given state and error
 *
 *  @param aState The state to initialize with
 *  @param aError The error to initialzie with
 *
 *  @return An initialized WOWZStatus object
 */
+ (nonnull instancetype) statusWithStateAndError:(WOWZState)aState aError:(nonnull NSError *)aError;

/*!
 *  Returns a WOWZStatus object with a given event
 *
 *  @param event The WOWZEvent to initialize with
 *
 *  @return An initialized WZStatus object
 */
+ (nonnull instancetype) statusWithEvent:(WOWZEvent)event;

/*!
 *  Returns a WOWZStatus object with a given state and event
 *
 *  @param aState The state to initialize with
 *  @param event The WOWZEvent to initialize with
 *
 *  @return An initialized WOWZStatus object
 */
+ (nonnull instancetype) statusWithState:(WOWZState)aState event:(WOWZEvent)event;

#pragma mark - Instance Methods

/*!
 *  Initialize a WOWZStatus object with a given state
 *
 *  @param aState The state to initialize with
 *
 *  @return An initialized WOWZStatus object
 */
- (nonnull instancetype) initWithState:(WOWZState)aState;

/*!
 *  Initialize a WOWZStatus object with a given state and error
 *
 *  @param aState The state to initialize with
 *  @param aError The error to initialzie with
 *
 *  @return An initialized WOWZStatus object
 */
- (nonnull instancetype) initWithStateAndError:(WOWZState)aState aError:(nonnull NSError *)aError;

/*!
 *  Initialize a WOWZStatus object with a given event
 *
 *  @param event The WOWZEvent to initialize with
 *
 *  @return An initialized WOWZStatus object
 */
- (nonnull instancetype) initWithEvent:(WOWZEvent)event;

/*!
 *  Initialize a WOWZStatus object with a given state and event
 *
 *  @param aState The state to initialize with
 *  @param event The WOWZEvent to initialize with
 *
 *  @return An initialized WZStatus object
 */
- (nonnull instancetype) initWithState:(WOWZState)aState event:(WOWZEvent)event;

/*!
 *  Re-initialize a WOWZStatus object, clearing any error, event, and data values and setting the state to WOWZStateIdle
 */
- (void) resetStatus;

/*!
 *  Re-initialize a WOWZStatus object, clearing any error, event, and data values and setting the state to the specified value
 *
 *  @param aState The state to initialize with
 */
- (void) resetStatusWithState:(WOWZState)aState;

/*!
 *  Test to see if the state equals WOWZStateIdle
 *
 *  @return true if the state is WOWZStateIdle, false otherwise
 */
@property (readonly, nonatomic) BOOL isIdle;

/*!
 *  Test to see if the state equals WOWZStateStarting
 *`
 *  @return true if the state is WOWZStateStarting, false otherwise
 */
@property (readonly, nonatomic) BOOL isStarting;

/*!
 *  Test to see if the state equals WOWZStateReady
 *
 *  @return true if the state is WOWZStateReady, false otherwise
 */
@property (readonly, nonatomic) BOOL isReady;

/*!
 *  Test to see if the state equals WOWZStateRunning
 *
 *  @return true if the state is WOWZStateRunning, false otherwise
 */
@property (readonly, nonatomic) BOOL isRunning;

/*!
 *  Test to see if the state equals WOWZStateStopping
 *
 *  @return true if the state is WOWZStateStopping, false otherwise
 */
@property (readonly, nonatomic) BOOL isStopping;

/*!
 *  Test to see if the error is non-null
 *
 *  @return true if the error is non-null, false otherwise
 */
@property (readonly, nonatomic) BOOL hasError;

@end
