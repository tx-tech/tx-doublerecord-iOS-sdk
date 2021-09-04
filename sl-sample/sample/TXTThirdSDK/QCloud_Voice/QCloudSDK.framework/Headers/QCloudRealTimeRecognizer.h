//
//  QCloudRealTimeRecognizer.h
//  QCloudSDK
//
//  Created by Sword on 2019/3/28.
//  Copyright © 2019 Tencent. All rights reserved.
//

#import "QCloudSDK.h"

NS_ASSUME_NONNULL_BEGIN

@class QCloudRealTimeResponse;
@protocol QCloudAudioDataSource;
@protocol QCloudRealTimeRecognizerDelegate;

@interface QCloudRealTimeRecognizer : QCloudBaseRecognizer

@property (nonatomic, assign, readonly) QCloudASRRealTimeRecognizeState state;
@property (nonatomic, weak) id<QCloudRealTimeRecognizerDelegate>delegate;

/**
 * 初始化方法，调用者传递语音数据调用此初始化方法
 * @param config 配置参数，详见QCloudConfig定义
 * @param dataSource 语音数据数据源，必须实现QCloudAudioDataSource协议
 */
- (instancetype)initWithConfig:(QCloudConfig *)config dataSource:(id<QCloudAudioDataSource>)dataSource;

// 按设备授权需求: 开始
/**
 * 第三方设备的初始化方法，调用者传递语音数据、授权序列号及设备的唯一标识，调用此初始化方法
 * @param config 配置参数，详见QCloudConfig定义
 * @param dataSource 语音数据数据源，必须实现QCloudAudioDataSource协议
 * @param sn 授权序列号 
 * @param deviceId 第三方设备的唯一标识mac
 */
- (instancetype)initWithConfig:(QCloudConfig *)config dataSource:(nullable id<QCloudAudioDataSource>)dataSource sn:(NSString *)sn deviceId:(NSString *)deviceId;

/**
 * 第三方设备的初始化方法，调用者传递语音数据及授权序列号，调用此初始化方法
 * @param config 配置参数，详见QCloudConfig定义
 * @param dataSource 语音数据数据源，必须实现QCloudAudioDataSource协议
 * @param sn 授权序列号
 */
- (instancetype)initWithConfig:(QCloudConfig *)config dataSource:(nullable id<QCloudAudioDataSource>)dataSource sn:(NSString *)sn;
// 按设备授权需求: 结束

/**
 * 通过内置录音器采集音频开始实时语音识别，配合stop使用
 */
- (void)start;
/*
 * 停止实时语音识别
 */
- (void)stop;

/*
 * 关闭麦克风
 * keepMicrophoneRecording 开启后 调用此方法关闭麦克风
 */
- (void)stopMicrophone;

@end

/**
 * 一次实时录音识别，分为多个flow，每个flow可形象的理解为一句话，一次识别中可以包括多句话。
  * 每个flow包含多个seq语音数据包，每个flow的seq从0开始
 */
@protocol QCloudRealTimeRecognizerDelegate <NSObject>

@required
/**
 * 每个语音包分片识别结果
 * @param response 语音分片的识别结果
 */
- (void)realTimeRecognizerOnSliceRecognize:(QCloudRealTimeRecognizer *)recognizer response:(QCloudRealTimeResponse *)response;

@optional
/**
 * 一次识别成功回调
 @param recognizer 实时语音识别实例
 @param result 一次识别出的总文本
 */
- (void)realTimeRecognizerDidFinish:(QCloudRealTimeRecognizer *)recognizer result:(NSString *)result;
/**
 * 一次识别失败回调
 * @param recognizer 实时语音识别实例
 * @param error 错误信息
 */
- (void)realTimeRecognizerDidError:(QCloudRealTimeRecognizer *)recognizer error:(NSError *)error;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * 开始录音回调
 * @param recognizer 实时语音识别实例
 * @param error 开启录音失败，错误信息
 */
- (void)realTimeRecognizerDidStartRecord:(QCloudRealTimeRecognizer *)recognizer error:(NSError *)error;
/**
 * 结束录音回调
 * @param recognizer 实时语音识别实例
 */
- (void)realTimeRecognizerDidStopRecord:(QCloudRealTimeRecognizer *)recognizer;
/**
 * 录音音量实时回调用
 * @param recognizer 实时语音识别实例
 * @param volume 声音音量，取值范围（-40-0)
 */
- (void)realTimeRecognizerDidUpdateVolume:(QCloudRealTimeRecognizer *)recognizer volume:(float)volume;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * 语音流的开始识别
 * @param recognizer 实时语音识别实例
 * @param voiceId 语音流对应的voiceId，唯一标识
 * @param seq flow的序列号
 */
- (void)realTimeRecognizerOnFlowRecognizeStart:(QCloudRealTimeRecognizer *)recognizer voiceId:(NSString *)voiceId seq:(NSInteger)seq;
/**
 * 语音流的结束识别
 * @param recognizer 实时语音识别实例
 * @param voiceId 语音流对应的voiceId，唯一标识
 * @param seq flow的序列号
 */
- (void)realTimeRecognizerOnFlowRecognizeEnd:(QCloudRealTimeRecognizer *)recognizer voiceId:(NSString *)voiceId seq:(NSInteger)seq;
/**
 * 语音流的识别结果
 * @param recognizer 实时语音识别实例
 * @param response 语音分片的识别结果 
 */
- (void)realTimeRecognizerOnSegmentSuccessRecognize:(QCloudRealTimeRecognizer *)recognizer response:(QCloudRealTimeResponse *)response;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * 语音流开始识别
 * @param recognizer 实时语音识别实例
 * @param voiceId 语音流对应的voiceId，唯一标识
 * @param seq flow的序列号
 */
- (void)realTimeRecognizerOnFlowStart:(QCloudRealTimeRecognizer *)recognizer voiceId:(NSString *)voiceId seq:(NSInteger)seq;
/**
 * 语音流结束识别
 * @param recognizer 实时语音识别实例
 * @param voiceId 语音流对应的voiceId，唯一标识
 * @param seq flow的序列号
 */
- (void)realTimeRecognizerOnFlowEnd:(QCloudRealTimeRecognizer *)recognizer voiceId:(NSString *)voiceId seq:(NSInteger)seq;


/**
 * 录音停止后回调一次，再次开始录音会清空上一次保存的文件
 * @param recognizer 实时语音识别实例
 * @param audioFilePath 音频文件路径
 */
- (void)realTimeRecognizerDidSaveAudioDataAsFile:(QCloudRealTimeRecognizer *)recognizer
                                   audioFilePath:(NSString *)audioFilePath;

@end

NS_ASSUME_NONNULL_END
