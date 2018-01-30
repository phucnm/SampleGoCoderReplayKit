//
//  ViewController.swift
//  SampleGoCoder
//
//  Created by Tony Nguyen on 1/29/18.
//  Copyright © 2018 Tony Nguyen. All rights reserved.
//

import UIKit
import AVKit
import WowzaGoCoderSDK
import ReplayKit

class ViewController: UIViewController {
    
    @IBOutlet weak var button: UIButton!
    var broadcaster: WOWZBroadcast!
    var vc: AVPlayerViewController!
    var player: AVPlayer!
    var config: WowzaConfig!
    var encoder = WOWZH264Encoder()
    var audioDevice = WOWZAudioDevice()
    var audioEncoder = WOWZAACEncoder()

    @IBOutlet weak var container: UIView!
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        setupGoCoder()
        setupVideo()
    }
    
    func setupGoCoder() {
        WowzaGoCoder.registerLicenseKey("GOSK-5E44-010C-6599-462A-8CD8")
        WowzaGoCoder.setLogLevel(.verbose)
        broadcaster = WOWZBroadcast()
        broadcaster.videoEncoder = encoder
//        audioDevice.register(self as WOWZAudioSink)
//        audioEncoder.register(self as WOWZAudioEncoderSink)
        audioDevice.register(self as WOWZAudioSink)
        broadcaster.audioDevice = self.audioDevice
        config = WowzaConfig()
        config.videoWidth = UInt(view.frame.width)
        config.videoHeight = UInt(view.frame.height)
        config.hostAddress = "138.68.30.47"
        config.portNumber = 1935
        config.streamName = "myStream"
        config.applicationName = "tesuji_livestreaming"
        config.broadcastVideoOrientation = .alwaysPortrait
        config.audioEnabled = true
        config.username = "tesuji_publisher"
        config.password = "T3suj1I0Pul13h3r"
        config.audioBitrate = 0
        config.audioSampleRate = 44100
        config.audioChannels = 1
    }
    
    @IBAction func broadcastTap(_ sender: UIButton) {
        if broadcaster.status.state == WOWZState.running {
            broadcaster.end(self)
        } else {
            broadcaster.start(config, statusCallback: self)
        }
        
    }
    
    private func setupVideo() {
        if let url = Bundle.main.url(forResource: "Bunny", withExtension: "mp4") {
            player = AVPlayer(url: url)
            vc = AVPlayerViewController()
            vc.videoGravity = AVLayerVideoGravity.resizeAspect.rawValue
            vc.player = player
            vc.view.backgroundColor = UIColor.clear
            vc.showsPlaybackControls = false
            addChildViewController(vc)
            vc.view.frame = container.bounds
            container.addSubview(vc.view)
            didMove(toParentViewController: self)
            player.play()
            NotificationCenter.default.addObserver(self, selector: #selector(playVideoFinished(_:)), name: Notification.Name.AVPlayerItemDidPlayToEndTime, object: nil)
        }
    }
    
    @objc func playVideoFinished(_ notification: Notification) {
        player.seek(to: kCMTimeZero)
        player.play()
        print("Play finished")
    }


}

extension ViewController: WOWZStatusCallback {
    func onWOWZStatus(_ status: WOWZStatus!) {
        switch status.state {
        case .running:
            button.setTitle("Stop", for: .normal)
            RPScreenRecorder.shared().startCapture(handler: { (buffer, type, error) in
                switch type {
                case .video:
                    if let imgBuffer = CMSampleBufferGetImageBuffer(buffer) {
                        let pts = CMSampleBufferGetPresentationTimeStamp(buffer)
                        let newPts = CMTimeMake(pts.value / 1000, pts.timescale)
                        print(pts.seconds)
                        self.encoder.videoFrameWasCaptured(imgBuffer, framePresentationTime: pts, frameDuration: kCMTimeInvalid)
                    }
                    break
//                case .audioApp:
//                    var audioBufferList = AudioBufferList()
////                    var data = Data()
//                    var blockBuffer : CMBlockBuffer?
//
//                    CMSampleBufferGetAudioBufferListWithRetainedBlockBuffer(buffer, nil, &audioBufferList, MemoryLayout<AudioBufferList>.size, nil, nil, 0, &blockBuffer)
//
////                    let buffers = UnsafeBufferPointer<AudioBuffer>(start: &audioBufferList.mBuffers, count: Int(audioBufferList.mNumberBuffers))
//
////                    var pts = kCMTimeInvalid
//                    //var duration = kCMTimeInvalid
//                    let pts = CMSampleBufferGetPresentationTimeStamp(buffer)
//                    let formateDesc = CMSampleBufferGetFormatDescription(buffer)
//                    let asbd = CMAudioFormatDescriptionGetStreamBasicDescription(formateDesc!)
////                    print(audioBufferList.mBuffers.mDataByteSize)
//                    let sampleRate = asbd!.pointee.mSampleRate
//                    print(formateDesc)
//                    //duration = CMSampleBufferGetDuration(buffer)
////                    print("AudioPTS: \(pts.seconds)")
//                    self.audioEncoder.audioPCMFrameWasCaptured(asbd!, bufferList: &audioBufferList, time: pts, sampleRate: sampleRate)
////                    self.audioEncoder.audioFrameWasCaptured(sampleBytes, size: UInt32(length), time: pts, sampleRate: sampleRate)
                default:
                    break
                }
            }, completionHandler: nil)
        default:
            button.setTitle("Start", for: .normal)
            RPScreenRecorder.shared().stopCapture(handler: nil)
        }
    }
    
    func checkStatus(_ status: OSStatus, message: String) -> Bool {
        // See: https://www.osstatus.com/
        assert(kCMBlockBufferNoErr == noErr)
        if status != noErr {
            debugPrint("Error: \(message) [\(status)]")
        }
        return status == noErr
    }
    
    func onWOWZError(_ status: WOWZStatus!) {
        print(status.error!)
    }
}

extension ViewController: WOWZVideoSink, WOWZAudioSink {
    func videoFrameWasCaptured(_ imageBuffer: CVImageBuffer, framePresentationTime: CMTime, frameDuration: CMTime) {
//        print("capturing")
    }
    
    func audioFrameWasCaptured(_ data: UnsafeMutableRawPointer, size: UInt32, time: CMTime, sampleRate: Float64) {
        print("AUdiopts \(time.seconds)")
    }
}

