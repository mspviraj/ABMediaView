//
//  ABMediaView.h
//  Pods
//
//  Created by Andrew Boryk on 1/4/17.
//
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import <QuartzCore/QuartzCore.h>
#import <AVFoundation/AVFoundation.h>
#import "ABUtils.h"
#import "VideoTrackView.h"

typedef void (^ImageCompletionBlock)(UIImage *image, NSError *error);
typedef void (^VideoDataCompletionBlock)(NSString *video, NSError *error);

@protocol ABMediaViewDelegate;

extern const NSNotificationName ABMediaViewWillRotateNotification;
extern const NSNotificationName ABMediaViewDidRotateNotification;

@interface ABMediaView : UIImageView <VideoTrackDelegate, UIGestureRecognizerDelegate>

@property (weak, nonatomic) id<ABMediaViewDelegate> delegate;

//@property (strong, nonatomic) NSString *ABMediaViewWillRotateNotification;
//@property (strong, nonatomic) NSString *ABMediaViewDidRotateNotification;

/// Track which shows the progress of the video being played
@property (strong, nonatomic) VideoTrackView *track;

/// URL endpoint for image
@property (strong, nonatomic) NSString *imageURL;

/// URL endpoint for video
@property (strong, nonatomic) NSString *videoURL;

/// Theme color which will show on the play button and progress track for videos
@property (strong, nonatomic) UIColor *themeColor;

/// Determines whether the video playerLayer should be set to aspect fit mode
@property BOOL videoAspectFit;

/// Determines whether the progress track should be shown for video
@property BOOL showTrack;

/// Determines if the video is already loading
@property BOOL isLoadingVideo;

/// Determines if the video should be looped when it reaches completion
@property BOOL allowLooping;

/// Determines whether or not the mediaView is being used in a reusable view
@property BOOL imageViewNotReused;

/// Determines whether the mediaView can be minimized into the bottom right corner, and then dismissed by swiping right on the minimized version
@property BOOL isMinimizable;

/// Recognizer which keeps track of whether the user taps the view to play or pause the video
@property (strong, nonatomic) UITapGestureRecognizer *playRecognizer;

/// Indicator which shows that the video is being loaded
@property (strong, nonatomic) UIActivityIndicatorView *loadingIndicator;

/// Play button imageView which shows in the center of the video, notifies the user that a video can be played
@property (strong, nonatomic) UIImageView *videoIndicator;

/// AVPlayer which will handle video playback
@property (strong, nonatomic) AVPlayer *player;

/// AVPlayerLayer which will display video
@property (strong, nonatomic) AVPlayerLayer *playerLayer;

/// Timer for animating the videoIndicator, to show that the video is loading
@property (strong, nonatomic) NSTimer *animateTimer;

/// Allows functionality to change the videoGravity to aspectFit on the fly
- (void) changeVideoToAspectFit: (BOOL) videoAspectFit;

/// Download the image, display the image, and give completion block
- (void) setImageURL:(NSString *)imageURL withCompletion: (ImageCompletionBlock) completion;

/// Set the url for the image
- (void) setVideoURL:(NSString *)videoURL;

/// Loads the video, saves to disk, and decides whether to play the video
- (void) loadVideoWithPlay: (BOOL)play withCompletion: (VideoDataCompletionBlock) completion;

/// Show that the video is loading with animation
- (void) loadVideoAnimate;

/// Stop video loading animation
- (void) stopVideoAnimate;

/// Update the frame of the playerLayer
- (void) updatePlayerFrame;

/// Remove observers for player
- (void) removeObservers;

/// Selector to play the video from the playRecognizer
- (void) playVideoFromRecognizer;

/// Returns whether the view has a video
- (BOOL) hasVideo;

/// Returns whether the view is already playing video
- (BOOL) isPlayingVideo;

/// Toggle functionality for remaining time to show on right track label rather than showing total time
- (void) setShowRemainingTime: (BOOL) showRemainingTime;

/// Determines whether the mediaView can be minimized into the bottom right corner, and then dismissed
- (void) setCanMinimize: (BOOL) canMinimize;

@end

@protocol ABMediaViewDelegate <NSObject>

@optional

- (void) selection;

- (void) playVideo;

- (void) stopVideo;

- (void) pauseVideo;

- (void) openContent;

@end\
