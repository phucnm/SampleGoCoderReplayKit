//
//  WOWZCamera
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
#import "WowzaConfig.h"

/*!
 @class WOWZCamera
 @discussion The WOWZCamera class provides an interface for accessing and controlling a camera device. The 'cameras' property of WOWZCameraPreview can be used to retrieve a list of all cameras.
 */
@interface WOWZCamera : NSObject


/*!
*  @typedef WOWZCameraDirection
*  @constant WOWZCameraDirectionBack The back-facing camera.
*  @constant WOWZCameraDirectionFront The front-facing camera.
*  @discussion A camera direction, either front or back.
*/
typedef NS_ENUM(NSUInteger, WOWZCameraDirection) {
    WOWZCameraDirectionBack = 0,
    WOWZCameraDirectionFront
};

/*!
 *  @typedef WOWZCameraFocusMode
 *  @constant WOWZCameraFocusModeLocked Indicates that the camera focus is locked at the lens' current position.
 *  @constant WOWZCameraFocusModeAuto Indicates that the camera will autofocus, and then switch to WOWZCameraFocusModeLocked.
 *  @constant WOWZCameraFocusModeContinuous Indicates that the camera will automatically focus as needed.
 *  @discussion A camera focus mode.
 */
typedef NS_ENUM(NSUInteger, WOWZCameraFocusMode) {
    WOWZCameraFocusModeLocked = 0,
    WOWZCameraFocusModeAuto,
    WOWZCameraFocusModeContinuous
};

/*!
 *  @typedef WOWZCameraExposureMode
 *  @constant WOWZCameraExposureModeLocked Indicates that the camera exposure is locked at it's current value.
 *  @constant WOWZCameraExposureModeAuto Indicates that the camera will automatically adjust exposure once, and then switch to WOWZCameraExposureModeLocked.
 *  @constant WOWZCameraExposureModeContinuous Indicates that the camera will automatically adjust exposure as needed.
 *  @discussion A camera exposure mode.
 */

typedef NS_ENUM(NSUInteger, WOWZCameraExposureMode) {
    WOWZCameraExposureModeLocked = 0,
    WOWZCameraExposureModeAuto,
    WOWZCameraExposureModeContinuous
};

/*!
 *  A unique identifier for this camera
 */
@property (readonly) NSUInteger cameraId;

/*!
 *  The facing direction of this camera
 */
@property (readonly) WOWZCameraDirection direction;

/*!
 *  The AVCaptureDevice represented by this camera
 */
@property (nonatomic, readonly, nonnull) AVCaptureDevice *iOSCaptureDevice;

/*!
 *  The supported frame sizes for this camera, as an array of CGSize values
 */
@property (nonatomic, nonnull, readonly) NSArray<NSValue *> *frameSizes;

/*!
 *  The supported WOWZMediaConfigs for this camera
 */
@property (nonatomic, nonnull, readonly) NSArray<WOWZMediaConfig *> *supportedPresetConfigs;

/*!
 *  Returns whether or not this camera has a torch (flash)
 */
@property (nonatomic, readonly) BOOL hasTorch;

/*!
 *  Set the torch (flash) on or off
 */
@property (nonatomic, getter=isTorchOn) BOOL torchOn;

/*!
 *  The focus mode for this camera
 */
@property (nonatomic) WOWZCameraFocusMode focusMode;

/*!
 *  The exposure mode for this camera
 */
@property (nonatomic) WOWZCameraExposureMode exposureMode;

#pragma mark - Instance Methods

/*!
 *  Initialize a WOWZCamera from a given AVCaptureDevice
 *
 *  @param captureDevice the AVCaptureDevice
 *
 *  @return An instance of WOWZCamera
 */
- (nonnull instancetype) initWithCaptureDevice:(nonnull AVCaptureDevice *)captureDevice;

- (nonnull instancetype) init __attribute__((unavailable("initWithCaptureDevice must be used")));

/*!
 *  Does the camera support the given frame width
 *
 *  @param width The width
 *
 *  @return YES if the width is supported by the camera, otherwise NO
 */
- (BOOL) supportsWidth:(NSUInteger)width;

/*!
 *  Does the camera support the given focus mode
 *
 *  @param mode the focus mode
 *
 *  @return YES if the camera supports the focus mode, otherwise no
 */
- (BOOL) supportsFocusMode:(WOWZCameraFocusMode)mode;

/*!
 *  Does the camera support the given exposure mode
 *
 *  @param mode the exposure mode
 *
 *  @return YES if the camera supports the exposure mode, otherwise no
 */
- (BOOL) supportsExposureMode:(WOWZCameraExposureMode)mode;

/*!
 *  Is this the back-facing camera
 *
 *  @return YES if this is the back-facing camera, otherwise NO
 */
- (BOOL) isBack;

/*!
 *  Is this the front-facing camera
 *
 *  @return YES if this is the front-facing camera, otherwise NO
 */
- (BOOL) isFront;

/*!
 *  Sets the focus mode for this camera at a given point of interest.
 *
 *  @param focusMode the focus mode
 *  @param point     the point of interest, with a value between (0,0) and (1,1);
 *  a value of (0,0) indicates the camera should focus at the top left corner of the image, while
 *  a value of (1,1) indicates that the camera should focus at the bottom right.
 */
- (void) setFocusMode:(WOWZCameraFocusMode)focusMode focusPoint:(CGPoint)point;

/*!
 *  Sets the exposure mode for this camera at a given point of interest.
 *
 *  @param exposureMode the exposure mode
 *  @param point     the point of interest, with a value between (0,0) and (1,1);
 *  a value of (0,0) indicates the camera should focus at the top left corner of the image, while
 *  a value of (1,1) indicates that the camera should focus at the bottom right.
 */
- (void) setExposureMode:(WOWZCameraExposureMode)exposureMode exposurePoint:(CGPoint)point;

@end
