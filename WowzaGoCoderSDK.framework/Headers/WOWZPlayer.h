//
//  WOWZPlayer.h
//  WOWZPlayer
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
#import "WOWZDataEvent.h"
#import "WOWZDataSink.h"
#import "WOWZStatusCallback.h"


/*!
 @class WOWZPlayer
 @discussion WOWZPlayer is a class used for playing a WOWZ stream from Engine or Cloud. WOWZPlayer handles decompressing audio and video, playing audio through the device speaker and displaying video frames in a UIView.
 */
@interface WOWZPlayer : NSObject

/*!
 *  @typedef WOWZPlayerViewGravityResizeAspect
 *  @constant WOWZPlayerViewGravityResizeAspect Preserve aspect ratio; fit within layer bounds.
 *  @constant WOWZPlayerViewGravityResizeAspectFill Preserve aspect ratio; fill layer bounds.
 *  @discussion Describes how the video in the player view should fill the view frame.
 */
typedef NS_ENUM(NSUInteger, WOWZPlayerViewGravity) {
    WOWZPlayerViewGravityResizeAspect = 0,
    WOWZPlayerViewGravityResizeAspectFill
};

/*!
 *  The gravity to use for displaying the video in the host view; describes
 *  how the prview will fill the given view bounds
 */
@property (nonatomic, assign) WOWZPlayerViewGravity playerViewGravity;

/*!
 *  The UIView to which the video player will be added.
 */
@property (nonatomic, unsafe_unretained, nonnull) UIView *playerView;

/*!
 *  The current play state of the WOWZPlayer instance.
 */
@property (nonatomic, assign, readonly) BOOL playing;

/*!
 *  The volume at which to play the audio. Allowed values are 0.0 (silent) to 1.0 (full volume).
 *  Any value outside this range is ignored. Default is 1.0.
 */
@property (nonatomic, assign) Float32 volume;

/*!
 *  The sync offset to scrub video to sync. Allowed values are -1.0  to 3.0 Seconds.
 *  Any value outside this range is ignored. Default is 1.0.
 */
@property (nonatomic, assign) Float32 syncOffset;


/*!
 *  Mute/unmute audio. Default is NO.
 */
@property (nonatomic, assign) BOOL muted;

/*!
 *  The amount of time to pre-roll (buffer) the video before playing. The default is 0 seconds. Max 60 seconds.
 */
@property (nonatomic, assign) Float64 prerollDuration;

/*!
 *  The stream metadata for an actively playing stream
 */
@property (nonatomic, readonly, nullable) WOWZDataMap *metaData;


/*!
 *  The timecode of the most recent frame displayed by the player, relative to the starting timecode.
    Returns kCMTimeInvalid if the player is not currently playing, or if no frames have yet been received.
 */
@property (nonatomic, readonly) CMTime currentTime;

/*!
 *  Allow the use of HLS fallback if the socket based conection is not successful, this will add latency to the stream for the user playing back.
 */
@property (nonatomic, assign) BOOL useHLSFallback;

/*!
 *  Start playing the video stream.
 *
 *  @param config The WowzaConfig specifying the host, port, app name and stream name to play
 *  @param statusCallback A callback that will be invoked with playback session status updates and errors.
 *
 */
- (void) play:(nonnull WowzaConfig *)config callback:(nullable id<WOWZStatusCallback>)statusCallback;

/*!
 *  Stop playing the video stream
 */
- (void) stop;

-(void)updateViewLayouts;

/*!
 *  Setup HLS Fallback
 */
-(void)setupHLSWithView:(UIView *_Nullable)viewToAttachTo;

/*!
 *  Start HLS Fallback
 */
-(void)startHLSPlayback;

/*!
 *  Stop HLS Fallback
 */
-(void)stopHLSPlayback;

/*!
 *  Pause HLS Fallback
 */
-(void)pauseHLSPlayback;

/*!
 * Reset the playback error count to 0
 */
-(void)resetPlaybackErrorCount;


/*!
 *  Registers an object that conforms to the WOWZDataSink protocol with WOWZPlayer.
 *  The WOWZDataSink protocol methods will be called when video player
 *  is active and a data event is received from the server.
 *
 *  @param sink An object conforming to the WOWZAudioEncoderSink protocol
 *  @param eventName The name of the data event the client wishes to listen for
 */
- (void) registerDataSink:(nonnull id<WOWZDataSink>)sink eventName:(nonnull NSString *)eventName;

/*!
 *  Unregisters an object that conforms to the WOWZDataSink protocol with WOWZPlayer.
 *
 *  @param sink An object conforming to the WOWZDataSink protocol
 */
- (void) unregisterDataSink:(nonnull id<WOWZDataSink>)sink eventName:(nonnull NSString *)eventName;

@end
