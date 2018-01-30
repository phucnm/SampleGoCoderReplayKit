//
//  WowzaGoCoder.h
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

#import <UIKit/UIKit.h>
#import "WowzaConfig.h"
#import "WOWZStatusCallback.h"
#import "WOWZVideoSink.h"
#import "WOWZAudioSink.h"
#import "WOWZVideoEncoderSink.h"
#import "WOWZAudioEncoderSink.h"
#import "WOWZDataEvent.h"
#import "WOWZDataSink.h"

@class WOWZCameraPreview;

/*!
 *  @class WowzaGoCoder
 *  @discussion The WowzaGoCoder class is the primary API interface for the GoCoder SDK. It provides methods for both device and streaming configuration and control
 */
@interface WowzaGoCoder : NSObject <WOWZStatusCallback>


/*!
 *  @typedef WowzaGoCoderLogLevel
 *  @constant WowzaGoCoderLogLevelOff Disable logging.
 *  @constant WowzaGoCoderLogLevelDefault Emit a minimum of log statements from the SDK.
 *  @constant WowzaGoCoderLogLevelVerbose Emit a verbose amount of log statements from the SDK.
 *  @discussion Settings for the desired log level for the GoCoder SDK.
 */
typedef NS_ENUM(NSUInteger, WowzaGoCoderLogLevel) {
    WowzaGoCoderLogLevelOff,
    WowzaGoCoderLogLevelDefault,
    WowzaGoCoderLogLevelVerbose
};

/*!
 *  @typedef WowzaGoCoderNetworkLogLevel
 *  @constant WowzaGoCoderNetworkLogLevelVerbose Output all log messages.
 *  @constant WowzaGoCoderNetworkLogLevelDebug Log debug, informational, warning, and error messsges.
 *  @constant WowzaGoCoderNetworkLogLevelInfo Log informational, warning, and error messsges.
 *  @constant WowzaGoCoderNetworkLogLevelWarn Log warning and error messages.
 *  @constant WowzaGoCoderNetworkLogLevelError Log error messages.
 *  @discussion Settings for the desired network log level for the GoCoder SDK.
 */
typedef NS_ENUM(NSUInteger, WowzaGoCoderNetworkLogLevel) {
    WowzaGoCoderNetworkLogLevelVerbose  = 1,
    WowzaGoCoderNetworkLogLevelDebug    = 2,
    WowzaGoCoderNetworkLogLevelInfo     = 3,
    WowzaGoCoderNetworkLogLevelWarn     = 4,
    WowzaGoCoderNetworkLogLevelError    = 5
};

#if ! WGC_TARGET_EXTENSION

/*!
 *  @typedef WowzaGoCoderCapturePermission
 *  @constant WowzaGoCoderCapturePermissionAuthorized Access to a particular capture device has been authorized user.
 *  @constant WowzaGoCoderCapturePermissionDenied Access to a particular capture device has been denied by the user.
 *  @constant WowzaGoCoderCapturePermissionNotDetermined Access to a particular capture device has yet to be determined.
 *  @discussion Permissions for either an audio or video capture device.
 */
typedef NS_ENUM(NSUInteger, WowzaGoCoderCapturePermission) {
    WowzaGoCoderCapturePermissionAuthorized,
    WowzaGoCoderCapturePermissionDenied,
    WowzaGoCoderCapturePermissionNotDetermined
};

/*!
 *  @typedef WowzaGoCoderPermissionType
 *  @constant WowzaGoCoderPermissionTypeCamera The device camera permission type
 *  @constant WowzaGoCoderPermissionTypeMicrophone The device microphone permission type.
 *  @discussion Permission types that are availble in the SDK.
 */
typedef NS_ENUM(NSUInteger, WowzaGoCoderPermissionType) {
    WowzaGoCoderPermissionTypeCamera,
    WowzaGoCoderPermissionTypeMicrophone
};

/*!
 *  @typedef WOWZPermissionBlock A callback block that is used with requestCameraPermission and requestMicrophonePermission
 */
typedef void (^WOWZPermissionBlock)(WowzaGoCoderCapturePermission permission);

#endif


// Class methods
/*!
 *  Register and validate the GoCoder SDK license key
 *
 *  @param licenseKey The license key
 *
 *  @return An NSError describing the license validation error, or nil if no error
 */
+ (nullable NSError *) registerLicenseKey:(nonnull NSString *)licenseKey;

/*!
 *  Set the SDK log level
 *
 *  @param level The desired log level
 */
+ (void) setLogLevel:(WowzaGoCoderLogLevel)level;

/*!
 *  Set the SDK network layer log level
 *
 *  @param level The desired network layer logging level
 */
+ (void) setNetworkLogLevel:(WowzaGoCoderNetworkLogLevel)level;

#if ! WGC_TARGET_EXTENSION

/*!
 *  Explicitly request permission to use the camera or microphone.
 *
 *  @param type The WowzaGoCoderPermissionType for which permission is being requested.
 *  @param response The WOWZPermissionBlock to be executed once the user responds to the
 *  the device access request.
 */
+ (void) requestPermissionForType:(WowzaGoCoderPermissionType)type response:(nullable WOWZPermissionBlock)response;

/*!
 *  Get the current permission status for a given WowzaGoCoderPermissionType
 *
 *  @param type The WowzaGoCoderPermissionType to query
 */
+ (WowzaGoCoderCapturePermission) permissionForType:(WowzaGoCoderPermissionType)type;

#endif

/*!
 Get the WowzaGoCoder shared instance
 @result
    An instance of the top level GoCoder SDK API interface, or nil if licensing failed
 */
+ (nullable instancetype) sharedInstance;

// Properties

/*!
 *  The video, audio and stream configuration settings
 */
@property (nonatomic, nonnull, copy) WowzaConfig *config;


#if ! WGC_TARGET_EXTENSION
/*!
 *  The view that the caller wants to use for the camera preview
 */
@property (nonatomic, nullable) UIView *cameraView;

/*!
 *  The WOWZCameraPreview object (created when the cameraView is set)
 */
@property (nonatomic, nullable, readonly) WOWZCameraPreview *cameraPreview;

#endif

/*!
 @property status
 @discussion Reflects the current live streaming session status
 */
@property (nonatomic, nonnull, readonly) WOWZStatus *status;


#if ! WGC_TARGET_EXTENSION

/*!
 *  The muted state of the audio encoder
 */
@property (nonatomic, assign, getter=isAudioMuted) BOOL audioMuted;

#endif

/*!
 *  The AVAudioSessionCategoryOptions to use if streaming with audio. Default is AVAudioSessionCategoryOptionAllowBluetooth.
 *  Note that this property must be set before starting a preview session.
 */
@property (nonatomic, assign) AVAudioSessionCategoryOptions audioSessionOptions;

/*!
 *  Returns true if a live streaming broadcast is active
 */
@property (nonatomic, readonly) BOOL isStreaming;

/*!
 *  The stream metadata for the broadcasted stream
 */
@property (nonatomic, readonly, nullable) WOWZDataMap *metaData;

// Instance methods
+ (nonnull instancetype) alloc __attribute__((unavailable("alloc not available, call the sharedInstance class method instead")));
- (nonnull instancetype) init __attribute__((unavailable("init not available, call the sharedInstance class method instead")));
+ (nonnull instancetype) new __attribute__((unavailable("new not available, call the sharedInstance class method instead")));
- (nonnull instancetype) copy __attribute__((unavailable("copy not available, call the sharedInstance class method instead")));



/*!
 Starts a live streaming session
 @param statusCallback
    A callback that will be invoked with streaming session status updates and errors.
 */
- (void) startStreaming:(nullable id<WOWZStatusCallback>)statusCallback;

/*!
 Starts a live streaming session
 @param statusCallback
 A callback that will be invoked with streaming session status updates and errors.
 @param aConfig
 The configuration settings for the live streaming session.
 */
- (void) startStreamingWithConfig:(nullable id<WOWZStatusCallback>)statusCallback config:(nonnull WowzaConfig *)aConfig;

/*!
 Starts a live streaming session
 @param statusCallback
 A callback that will be invoked with streaming session status updates and errors.
 @param aPreset
 The WOWZFrameSizePreset for the live streaming session.
 */
- (void) startStreamingWithPreset:(nullable id<WOWZStatusCallback>)statusCallback preset:(WOWZFrameSizePreset)aPreset;

/*!
 End the active streaming session
 @param statusCallback
    A callback that will be invoked with streaming session status updates and errors.
 */
- (void) endStreaming:(nullable id<WOWZStatusCallback>)statusCallback;

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
 *  Sends a ping request to the server and returns the result to the specified callback
 *
 *  @param callback A callback to be invoked with the results of the request. The "responseTime" property of the result parameters passed to the callback will contain the response time, in milliseconds.
 * */
- (void) sendPingRequest:(nonnull WOWZDataCallback)callback;

#pragma mark -

#if ! WGC_TARGET_EXTENSION

/*!
 *  Registers an object that conforms to the WOWZVideoSink protocol with WowzaGoCoder.
 *  the WOWZVideoSink protocol methods will be called when video capture and/or encoding
 *  are active.
 *
 *  @param sink An object conforming to the WOWZVideoSink protocol
 */
- (void) registerVideoSink:(nonnull id<WOWZVideoSink>)sink;

/*!
 *  Unregisters an object that conforms to the WOWZVideoSink protocol with WowzaGoCoder.
 *
 *  @param sink An object conforming to the WOWZVideoSink protocol
 */
- (void) unregisterVideoSink:(nonnull id<WOWZVideoSink>)sink;

/*!
 *  Registers an object that conforms to the WOWZAudioSink protocol with WowzaGoCoder.
 *  the WOWZAudioSink protocol methods will be called when audio capture and/or encoding
 *  are active.
 *
 *  @param sink An object conforming to the WOWZAudioSink protocol
 */
- (void) registerAudioSink:(nonnull id<WOWZAudioSink>)sink;

/*!
 *  Unregisters an object that conforms to the WOWZAudioSink protocol with WowzaGoCoder.
 *
 *  @param sink An object conforming to the WOWZAudioSink protocol
 */
- (void) unregisterAudioSink:(nonnull id<WOWZAudioSink>)sink;

/*!
 *  Registers an object that conforms to the WOWZVideoEncoderSink protocol with WowzaGoCoder.
 *  The WOWZVideoEncoderSink protocol methods will be called when video encoding
 *  is active.
 *
 *  @param sink An object conforming to the WOWZVideoEncoderSink protocol
 */
- (void) registerVideoEncoderSink:(nonnull id<WOWZVideoEncoderSink>)sink;

/*!
 *  Unregisters an object that conforms to the WOWZVideoEncoderSink protocol with WowzaGoCoder.
 *
 *  @param sink An object conforming to the WOWZVideoEncoderSink protocol
 */
- (void) unregisterVideoEncoderSink:(nonnull id<WOWZVideoEncoderSink>)sink;

/*!
 *  Registers an object that conforms to the WOWZAudioEncoderSink protocol with WowzaGoCoder.
 *  The WOWZAudioEncoderSink protocol methods will be called when video encoding
 *  is active.
 *
 *  @param sink An object conforming to the WOWZAudioEncoderSink protocol
 */
- (void) registerAudioEncoderSink:(nonnull id<WOWZAudioEncoderSink>)sink;

/*!
 *  Unregisters an object that conforms to the WOWZAudioEncoderSink protocol with WowzaGoCoder.
 *
 *  @param sink An object conforming to the WOWZAudioEncoderSink protocol
 */
- (void) unregisterAudioEncoderSink:(nonnull id<WOWZAudioEncoderSink>)sink;

/*!
 *  Registers an object that conforms to the WOWZDataSink protocol with WowzaGoCoder.
 *  The WOWZDataSink protocol methods will be called when video encoding
 *  is active and a data event is received from the server.
 *
 *  @param sink An object conforming to the WOWZAudioEncoderSink protocol
 *  @param eventName The name of the data event the client wishes to listen for
 */
- (void) registerDataSink:(nonnull id<WOWZDataSink>)sink eventName:(nonnull NSString *)eventName;

/*!
 *  Unregisters an object that conforms to the WOWZDataSink protocol with WowzaGoCoder.
 *
 *  @param sink An object conforming to the WOWZDataSink protocol
 */
- (void) unregisterDataSink:(nonnull id<WOWZDataSink>)sink eventName:(nonnull NSString *)eventName;

#endif // #if ! WGC_TARGET_EXTENSION

@end
