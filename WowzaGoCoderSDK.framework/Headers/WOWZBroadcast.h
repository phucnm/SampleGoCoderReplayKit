//
//  WOWZBroadcast.h
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
#import "WOWZStatusCallback.h"
#import "WOWZStreamConfig.h"
#import "WOWZBroadcastComponent.h"
#import "WOWZDataEvent.h"
#import "WOWZDataSink.h"

/*!
 @class WOWZBroadcast
 @discussion The WOWZBroadcast class is used to configure and control a live streaming broadcast. Under normal circumstances, you do not need to access this class directly unless you are extending the GoCoder SDK.
 

 */
@interface WOWZBroadcast : NSObject

#pragma mark - Properties

/*!
 *  The status of the broadcast
 */
@property (nonatomic, readonly, nonnull) WOWZStatus *status;

/*!
 *  A callback that will be invoked with streaming session status updates and errors.
 */
@property (nonatomic, unsafe_unretained, nullable) id<WOWZStatusCallback> statusCallback;

/*!
 *  An object that adopts the WOWZBroadcastComponent protocol that will be
 *  used as the video encoder for this broadcast session.
 */
@property (nonatomic, strong, nullable) id<WOWZBroadcastComponent> videoEncoder;

/*!
 *  An object that adopts the WOWZBroadcastComponent protocol that will be
 *  used as the audio encoder for this broadcast session.
 */
@property (nonatomic, strong, nullable) id<WOWZBroadcastComponent> audioEncoder;

/*!
 *  An object that adopts the WOWZBroadcastComponent protocol that will be
 *  used as the audio capture device for this broadcast session.
 */
@property (nonatomic, strong, nullable) id<WOWZBroadcastComponent> audioDevice;

/*!
 *  The stream metadata for the broadcasted stream
 */
@property (nonatomic, readonly, nullable) WOWZDataMap *metaData;

#pragma mark - Instance Methods

/*!
 *  Start a live streaming broadcast using the specified configuration
 *
 *  @param config A WOWZStreamConfig describing the broadcast settings
 *  @param statusCallback A callback that will be invoked with streaming session status updates and errors.
 *
 *  @return A WOWZStatus object
 */
- (nonnull WOWZStatus *) startBroadcast:(nonnull WOWZStreamConfig *)config statusCallback:(nullable id<WOWZStatusCallback>)statusCallback;

/*!
 *  Stop the active live streaming broadcast
 *
 *  @param statusCallback A callback that will be invoked with streaming session status updates and errors.
 *
 *  @return A WOWZStatus object
 */
- (nonnull WOWZStatus *) endBroadcast:(nullable id<WOWZStatusCallback>)statusCallback;

/*!
 *  Send user-defined metadata within the current broadcast stream.
 *
 *  @param scope A WOWZDataScope defining the scope of the event to be sent.
 *  @param eventName The name of the event to be sent.
 *  @param params The parameters for the event to be sent.
 *  @param callback The callback to be called with the result of a WOWZDataScopeModule call.
 *  Should be nil for WOWZDataScopeStream.
 *
 */
- (void) sendDataEvent:(WOWZDataScope)scope eventName:(nonnull NSString *)eventName params:(nonnull WOWZDataMap *)params callback:(nullable WOWZDataCallback)callback;

/*!
 *  Registers an object that conforms to the WOWZDataSink protocol.
 *  The WOWZDataSink protocol methods will be called when video encoding
 *  is active and a data event is received from the server.
 *
 *  @param sink An object conforming to the WOWZAudioEncoderSink protocol
 *  @param eventName The name of the data event the client wishes to listen for
 */
- (void) registerDataSink:(nonnull id<WOWZDataSink>)sink eventName:(nonnull NSString *)eventName;

/*!
 *  Unregisters an object that conforms to the WOWZDataSink protocol.
 *
 *  @param sink An object conforming to the WOWZDataSink protocol
 */
- (void) unregisterDataSink:(nonnull id<WOWZDataSink>)sink eventName:(nonnull NSString *)eventName;

/*!
 *  Sends a ping request to the server and returns the result to the specified callback
 *
 *  @param statusCallback A callback to be invoked with the results of the request. The "responseTime" property of the result parameters passed to the callback will contain the response time, in milliseconds.
 * */
- (void) sendPingRequest:(nullable id<WOWZStatusCallback>)statusCallback;

@end
