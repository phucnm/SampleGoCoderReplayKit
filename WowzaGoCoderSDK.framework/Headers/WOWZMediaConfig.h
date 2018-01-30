//
//  WOWZMediaConfig.h
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

#import <AVFoundation/AVFoundation.h>




/*!
 @class WOWZMediaConfig
 @discussion The WOWZMediaConfig class provides configuration properties for the capture and encoding of video and audio
 */
@interface WOWZMediaConfig : NSObject <NSMutableCopying, NSCopying, NSCoding>

/*!
 *  @typedef WOWZFrameSizePreset
 *  @constant WOWZFrameSizePreset352x288 352 x 288 frame size.
 *  @constant WOWZFrameSizePreset640x480 640 x 480 frame size.
 *  @constant WOWZFrameSizePreset1280x720 1280 x 720 frame size (720p).
 *  @constant WOWZFrameSizePreset1920x1080 1920 x 1080 frame size (1080p).
 *  @constant WOWZFrameSizePreset3840x2160 3840 x 2160 frame size (UHD 4K).
 *  @constant WOWZFrameSizePresetCount Count of known frame sizes
 *  @discussion Frame size presets availabe at compile time. Note that not all of these
 *  presets are guarenteed to be supported by a particular device or device camera.
 */
typedef NS_ENUM(NSUInteger, WOWZFrameSizePreset) {
    WOWZFrameSizePreset352x288,
    WOWZFrameSizePreset640x480,
    WOWZFrameSizePreset1280x720,
    WOWZFrameSizePreset1920x1080,
    WOWZFrameSizePreset3840x2160,
    WOWZFrameSizePresetCount
};

/*!
 *  @typedef WOWZBroadcastOrientation
 *  @constant WOWZBroadcastOrientationAlwaysLandscape Always broadcast in landscape orientation.
 *  @constant WOWZBroadcastOrientationAlwaysPortrait Always broadcast in portrait orientation.
 *  @constant WOWZBroadcastOrientationSameAsDevice The broadcast orientation will be set according to the orientation of the device at broadcast start time.
 *  @discussion Describes the orientation of the broadcasted video.
 */
typedef NS_ENUM(NSUInteger, WOWZBroadcastOrientation) {
    WOWZBroadcastOrientationSameAsDevice,
    WOWZBroadcastOrientationAlwaysLandscape,
    WOWZBroadcastOrientationAlwaysPortrait
};

/*!
 *  @typedef WOWZBroadcastScaleMode
 *  @constant WOWZBroadcastScaleModeAspectFit Captured frames that don't fit within the requested broadcast frame size will be scaled to fit within the broadcast frame
 *  @constant WOWZBroadcastScaleModeAspectFill Captured frames that don't fit within the requested broadcast frame size will be scaled up to completely fill the broadcast frame.
 *  @discussion Describes how captured frames that don't exactly fit the requested broadcast frame size will be adjusted to fit within the requested frame size.
 */
typedef NS_ENUM(NSUInteger, WOWZBroadcastScaleMode) {
    WOWZBroadcastScaleModeAspectFit,
    WOWZBroadcastScaleModeAspectFill
};

/*!
 *  @typedef WOWZAudioChannels
 *  @constant WOWZAudioChannelsMono Mono, or single channel.
 *  @constant WOWZAudioChannels Stereo, or two-channel.
 *  @discussion Number of audio channels. Note that not all of these channel counts
 *  are guarenteed to be supported by a particular device.
 */
typedef NS_ENUM(NSUInteger, WOWZAudioChannels) {
    WOWZAudioChannelsMono     = 1,
    WOWZAudioChannelsStereo   = 2
};


#pragma mark - Public Class Methods -

/*!
 *  Converts a WOWZFrameSizePreset to an AVFoundation AVCaptureSessionPreset string.
 *
 *  @param wzPreset The WOWZFrameSizePreset to be converted.
 *
 *  @return The AVFoundation AVCaptureSessionPreset string that corresponds to the given WOWZFrameSizePreset.
 */
+ (nullable NSString *) AVCaptureSessionPresetFromPreset:(WOWZFrameSizePreset)wzPreset;

/*!
 *  Converts a WOWZFrameSizePreset to the corresponding CGSize for that preset.
 *
 *  @param preset The WOWZFrameSizePreset to be converted.
 *
 *  @return The CGSize which corresponds to the given WOWZFrameSizePreset.
 */
+ (CGSize) CGSizeFromPreset:(WOWZFrameSizePreset)preset;

/*!
 *  Given a width, returns the AVFoundation AVCaptureSessionPreset string that most closely matches that width.
 *
 *  @param width The width being matched.
 *
 *  @return The closest AVFoundation AVCaptureSessionPreset string matching the given width.
 */
+ (nullable NSString *) closestAVCaptureSessionPresetByWidth:(NSUInteger)width;

#pragma mark -

/*!
 *  Returns an array of NSNumber values for each WOWZFrameSizePreset
 *
 *  @return The array of NSNumber values
 */
+ (nonnull NSArray *) presets;

/*!
 *  Returns an array of WOWZMediaConfig objects for each WOWZFrameSizePreset.
 *
 *  @return The array of WOWZMediaConfig objects.
 */
+ (nonnull NSArray *) presetConfigs;


#pragma mark - Properties -

/*!
 *  Enable or disable video for the configuration.  If doing playback, this means video will not be decoded even if present in stream.
 */
@property (nonatomic, assign) BOOL videoEnabled;

/*!
 *  Enable or disable audio for the configuration.  If doing playback, this means audio will not be decoded even if present in stream.
 */
@property (nonatomic, assign) BOOL audioEnabled;

#pragma mark -

/*!
 *  The video frame width for the configuration.
 */
@property (nonatomic, assign) NSUInteger videoWidth;

/*!
 *  The video frame height for the configuration.
 */
@property (nonatomic, assign) NSUInteger videoHeight;

/*!
 *  The desired frame rate for the configuration. Note that the actual frame rate
 *  might be reduced if network bandwidth cannot keep up with the desired frame rate.
 */
@property (nonatomic, assign) NSUInteger videoFrameRate;

/*!
 *  The video key frame interval.
 */
@property (nonatomic, assign) NSUInteger videoKeyFrameInterval;

/*!
 *  The desired video bitrate. Note that the actual bitrate
 *  might be reduced if network bandwidth cannot keep up with the desired bitrate.
 */
@property (nonatomic, assign) NSUInteger videoBitrate;

/*!
 *  The factor by which to scale the desired bitrate in low bandwidth conditions.
 *  Valid range is 0.0 to 1.0; any other value will be ignored. Setting a value of
 *  0.0 indicates that the encoder should choose the best value; setting a value of
 *  1.0 indicates that bitrate will never be throttled.
 *  The default is 0.75
 */
@property (nonatomic, assign) Float32 videoBitrateLowBandwidthScalingFactor;

/*!
 *  The value by which to multiply the video frame rate to derive the number of
 *  video frames to buffer before the encoder starts to throttle bitrate 
 *  and/or frame rate.
 *  For example: if the frame rate is 30 and the videoFrameBufferSizeMultiplier is 5,
 *  the encoder will buffer 150 (5 * 30) frames before throttling.
 *  Setting a value of 0 indicates that the encoder should choose the best value.
 *  The default is 4.
 */
@property (nonatomic, assign) NSUInteger videoFrameBufferSizeMultiplier;

/*!
 *  The number of frames to skip when the encoder cannot keep up with the broadcaster.  
 *  In low bandwidth conditions the encoder will skip frames to conserve bandwidth but
 *  still send consistent frames so the encoder can produce smooth playback.
 *  The maximum number of frames that can be skipped is equal to the key frame interval
 *  minus one - i.e. setting this to 29 with a key frame interval of 30 will
 *  produce a key frame only stream, setting to 1 will never skip frames.
 *  The default is 2 meaning skip 1 of every 2 frames
 */
@property (nonatomic, assign) NSUInteger videoFrameRateLowBandwidthSkipCount;

#pragma mark -

/*!
 *  Set whether or not to rotate video frames to match the orientation of the device.
 */
@property (nonatomic, assign) BOOL capturedVideoRotates;

/*!
 *  Set whether or not the video session should rotate to match the orientation of the device.
 */
@property (nonatomic, assign) BOOL videoPreviewRotates;


/*!
 *  Set the desired broadcast orientation for a broadcast session. See WOWZBroadcastOrientation
 *  for allowed values. Default is WOWZBroadcastOrientationSameAsDevice.
 */
@property (nonatomic, assign) WOWZBroadcastOrientation broadcastVideoOrientation;


/*!
 *  Set the desired scale mode for captured frames that don't fit the requested broadcast frame size. See WOWZBroadcastScaleMode
 *  for allowed values. Default is WOWZBroadcastScaleModeAspectFit.
 */
@property (nonatomic, assign) WOWZBroadcastScaleMode broadcastScaleMode;

/*!
 *  Sets whether the front (selfie) camera mirrors captured video. Default is YES.
 */
@property (nonatomic, assign) BOOL mirrorFrontCamera;

/*!
 *  Allow the fallback to HLS if the socket stream connection is not successful. Default is NO.
 */
@property (nonatomic, assign) BOOL allowHLSPlayback;

/*!
 *  Allow the fallback to HLS if the socket stream connection is not successful. Default is NO.
 */
@property (nonatomic, assign) NSString * hlsURL;

#pragma mark -

/*!
 *  Set whether or not broadcasting when the app is in the background is enabled. If enabled, the host
 *  application must support the audio background mode (this is set in your app target's Capabilities tab,
 *  in the "Background Modes" section). In this case, the app will continue to record
 *  and broadcast the live audio stream. Since the camera cannot capture in the background on iOS, a
 *  blank or frozen video frame will be broadcast while the app is in the background.
 *  The default value is NO.
 */
@property (nonatomic, assign) BOOL backgroundBroadcastEnabled;

#pragma mark -

/*!
 *  The desired number of audio channels
 */
@property (nonatomic, assign) NSUInteger audioChannels;


/*!
 *  The desired audio sample rate. Note that the actual sample rate
 *  might be different from the desired rate. Set this property to 0
 *  to have WowzaGoCoder select the optimal sample rate based on the
 *  current hardware capabilities. The default value is 0.
 */
@property (nonatomic, assign) NSUInteger audioSampleRate;

/*!
 *  The desired audio bitrate. Note that the actual bitrate
 *  might be different from the desired rate. Set this property to 0
 *  to have WowzaGoCoder select the optimal bitrate based on the
 *  current hardware capabilities. The default value is 0.
 */
@property (nonatomic, assign) NSUInteger audioBitrate;

#pragma mark -

/*!
 *  The video frame size, in CGSize format
 */
@property (nonatomic, readonly) CGSize frameSize;

/*!
 *  A human-readable string describing the video frame size
 */
@property (nonatomic, readonly, nonnull) NSString *frameSizeLabel;

#pragma mark - Public Instance Methods -

/*!
 *  Initialize a new WOWZMediaConfig with a given preset
 *
 *  @param preset The frame size preset
 *
 *  @return An instance of WOWZMediaConfig with the specified frame size and
 *  recommended bitrate for that frame size.
 */
- (nonnull instancetype) initWithPreset:(WOWZFrameSizePreset)preset;

/*!
 *  Sets the frame size of the receiver with that described by a WOWZFrameSizePreset,
 *  as well as the recommended bitrate for that frame size.
 *
 *  @param preset The frame size preset
 */
- (void) loadPreset:(WOWZFrameSizePreset)preset;

/*!
 *  Get the receiver's corresponding AVFoundation AVCaptureSessionPreset string
 *
 *  @return The corresponding AVFoundation AVCaptureSessionPreset string for this config.
 */
- (nullable NSString *) toAVCaptureSessionPreset;

/*!
 *  Get the receiver's closest corresponding AVFoundation AVCaptureSessionPreset string
 *
 *  @return The closest corresponding AVFoundation AVCaptureSessionPreset string.
 */
- (nonnull NSString *) toClosestAVCaptureSessionPreset;

#pragma mark -

/*!
 *  Get the receiver's corresponding WOWZFrameSizePreset
 *
 *  @return The corresponding WOWZFrameSizePreset
 */
- (WOWZFrameSizePreset) toPreset;

/*!
 *  Get the receiver's closest corresponding WOWZFrameSizePreset
 *
 *  @return The closest corresponding WOWZFrameSizePreset
 */
- (WOWZFrameSizePreset) toClosestPreset;

#pragma mark -

/*!
 *  Tests the reciever for equality to the given WOWZMediaConfig
 *
 *  @param other The other WOWZMediaConfig to test against
 *
 *  @return YES if both the receiver and given config are equal; otherwise NO
 */
- (BOOL) equals:(nonnull WOWZMediaConfig *)other;

/*!
 *  Determine whether the frame size for the receiver describes a portrait orientation
 *
 *  @return Yes if the receiver's frame size is portrait; otherwise NO
 */
- (BOOL) isPortrait;

/*!
 *  Determine whether the frame size for the receiver describes a landscape orientation
 *
 *  @return Yes if the receiver's frame size is landscape; otherwise NO
 */
- (BOOL) isLandscape;

/*!
 *  Copy the reciever's settings to the given WOWZMediaConfig
 *
 *  @param other The WOWZMediaConfig being copied to
 */
- (void) copyTo:(nonnull WOWZMediaConfig *)other;

@end
