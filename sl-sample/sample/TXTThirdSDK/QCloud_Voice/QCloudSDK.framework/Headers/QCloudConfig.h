//
//  QCloudConfig.h
//  QCloudSDK
//
//  Created by Sword on 2019/3/29.
//  Copyright © 2019 Tencent. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface QCloudConfig : NSObject

//通用配置参数
@property (nonatomic, strong, readonly) NSString *appId;        //腾讯云appId     基本概念见https://cloud.tencent.com/document/product/441/6194
@property (nonatomic, strong, readonly) NSString *secretId;     //腾讯云secretId  基本概念见https://cloud.tencent.com/document/product/441/6194
@property (nonatomic, strong, readonly) NSString *secretKey;    //腾讯云secretKey 基本概念见https://cloud.tencent.com/document/product/441/6194
@property (nonatomic, assign, readonly) NSInteger projectId;    //腾讯云projectId 基本概念见https://cloud.tencent.com/document/product/441/6194

//实时语音识别相关参数

@property (nonatomic, assign) BOOL usingSSL;                                  //默认NO 是否使用https, 由于NSURLSession存在ssl内存问题，开启后内层增长严重
@property (nonatomic, assign) BOOL enableDetectVolume;                        //是否检测录音音量的变化, 开启后sdk会实时回调音量变化
@property (nonatomic, assign) BOOL endRecognizeWhenDetectSilence;             //识别到静音是否结束识别, 默认YES
@property (nonatomic, assign) float silenceDetectDuration;                    //最大静音时间阈值, 超过silenceDetectDuration时间不说话则为静音, 单位:秒
@property (nonatomic, assign) BOOL enableDebugLog;                            //是否打开调试log, 默认YES
@property (nonatomic, assign) NSInteger sliceTime;                            //分片时间, 此参数影响语音分片长度, 单位:毫秒, 默认600ms
@property (nonatomic, strong) kQCloudASRRealTimeEngineModelType engineType;   //引擎识别类型, 见kQCloudASRRealTimeEngineModelType定义
@property (nonatomic, assign) NSInteger requestTimeout;                       //网络请求超时时间，单位:秒, 取值范围[5-60], 默认20
@property (nonatomic, assign) NSInteger filterDirty;                          //是否过滤脏词（目前支持中文普通话引擎） 具体的取值见https://cloud.tencent.com/document/product/1093/35799  的filter_dirty参数
@property (nonatomic, assign) NSInteger filterModal;                          //过滤语气词(目前支持中文普通话引擎). 具体的取值见https://cloud.tencent.com/document/product/1093/35799  的filter_modal参数
@property (nonatomic, assign) NSInteger filterPunc;                           //过滤句末的句号(目前支持中文普通话引擎). 具体的取值见https://cloud.tencent.com/document/product/1093/35799  的filter_punc参数
@property (nonatomic, assign) NSInteger convertNumMode;                       //是否进行阿拉伯数字智能转换。 具体的取值见https://cloud.tencent.com/document/product/1093/35799  的convert_num_mode参数
@property (nonatomic, strong) NSString *hotwordId;                            //热词id。 具体的取值见https://cloud.tencent.com/document/product/1093/35799  的hotword_id参数
@property (nonatomic, assign) BOOL enableReportCrash;                         //默认NO, 是否开启crash捕获, 并上报

@property (nonatomic, assign) BOOL keepMicrophoneRecording;
//默认关闭 开启后 需要调用 stopMicrophone 停止麦克风。使用场景：在停止识别后 需要麦克风继续录音一段时间 （录音不会上传服务器 不会识别 也不会保存）只支持内置录音设置

@property (nonatomic, assign) BOOL shouldSaveAsFile;
//是否保存录音文件到本地 默认关闭

@property (nonatomic, assign) QCloudASRNetworkProtocol netWorkProtocol;       //默认http

@property (nonatomic, assign) NSInteger vadSilenceTime;                     
//语音断句检测阈值，静音时长超过该阈值会被认为断句（多用在智能客服场景，需配合 needvad = 1 使用），取值范围：240-2000，单位 ms，目前仅支持 8k_zh、8k_zh_finance、16k_zh 引擎模型。

@property (nonatomic, assign) NSInteger needvad;                            //默认1
//0：关闭 vad，1：开启 vad。
//如果语音分片长度超过60秒，用户需开启 vad。

@property (nonatomic, assign) NSInteger wordInfo;
//是否显示词级别时间戳。0：不显示；1：显示，不包含标点时间戳，2：显示，包含标点时间戳。
//支持引擎8k_en，8k_zh，8k_zh_finance，16k_zh，16k_en，16k_ca，16k_zh-TW，16k_ja，16k_wuu-SH，默认为0。


/**
 * 初始化方法
 * @param appid     腾讯云appId     基本概念见https://cloud.tencent.com/document/product/441/6194
 * @param secretId  腾讯云secretId  基本概念见https://cloud.tencent.com/document/product/441/6194
 * @param secretKey 腾讯云secretKey 基本概念见https://cloud.tencent.com/document/product/441/6194
 * @param projectId 腾讯云projectId 基本概念见https://cloud.tencent.com/document/product/441/6194
 */
- (instancetype)initWithAppId:(NSString *)appid
                     secretId:(NSString *)secretId
                    secretKey:(NSString *)secretKey
                    projectId:(NSInteger)projectId;

@end

NS_ASSUME_NONNULL_END
