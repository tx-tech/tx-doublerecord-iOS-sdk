//
//  QCloudRealTimeResponse.h
//  QCloudSDK
//
//  Created by Sword on 2019/4/3.
//  Copyright © 2019 Tencent. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN
typedef NS_ENUM(NSInteger, QCloudRealTimeResponseCode) {
    QCloudRealTimeResponseCodeNone = -1,                 //未知
    QCloudRealTimeResponseCodeOk = 0,                    //成功
    QCloudRealTimeResponseCodeGetAudioSliceError = 100,  //获取语音分片信息失败
    QCloudRealTimeResponseCodeAudioSliceTooBig = 101,    //语音分片过大
    QCloudRealTimeResponseCodeInvalidParams = 102,       //参数不合法
    QCloudRealTimeResponseCodeAccessDBError = 103,       //访问数据库失败
    QCloudRealTimeResponseCodeWrongAppid = 104,          //appid未注册
    QCloudRealTimeResponseCodeTemplateNotExist = 105,    //模版不存在
    QCloudRealTimeResponseCodeUnusedTemplate = 106,      //模版停用
    QCloudRealTimeResponseCodeAuthencationError = 107,   //鉴权失败
    QCloudRealTimeResponseCodeSignError = 108,           //拼接签名串失败
    QCloudRealTimeResponseCodeGetIPPortError = 109,      //获取ip port失败
    QCloudRealTimeResponseCodeFaultNeedRealodUpload = 110, //后台识别服务器故障，请求seq=0重传
    QCloudRealTimeResponseCodeModuleDataFormatError = 111, //后台识别模块回包格式错误
    QCloudRealTimeResponseCodeNullAudio = 112,           //语音分片为空
    QCloudRealTimeResponseCodeServerTimeout = 113,       //后台识别服务超时
    QCloudRealTimeResponseCodeInvalidEngineNum = 114,    //引擎编号不合法
    QCloudRealTimeResponseCodeInvalidAudioType = 115,    //时长计算时音频类型不合法
    QCloudRealTimeResponseCodeNoFreeQuotaAvailable = 116,//无可使用的免费额度
    QCloudRealTimeResponseCodeNoAccess = 117,            //禁止访问
    QCloudRealTimeResponseCodeLimitRequest = 118,        //请求限流
    QCloudRealTimeResponseCodeAccountArrears = 119,      //账户欠费停止服务，请及时充值
    QCloudRealTimeResponseCodeGetRpcClientError = 120,   //获取 rpcClient 错误
    QCloudRealTimeResponseCodeErrorNeedRealodUpload = 121, //后台识别服务器错误，请从seq = 0重传
    QCloudRealTimeResponseCodeServerDataFormatError = 122, //后台识别服务器收到的包格式错误
    QCloudRealTimeResponseCodeAudioDecompressionError = 123,//后台识别服务器音频解压失败，请从seq = 0重传
    QCloudRealTimeResponseCodeServerRecognizeError = 124,//后台识别服务器识别失败，请从seq = 0重传
    QCloudRealTimeResponseCodeErrorNeedRetry = 125,      //后台识别服务器识别失败，请重新尝试
    QCloudRealTimeResponseCodeSliceTimeout = 126,        //后台识别服务器音频分片等待超时，请从seq = 0重传
    QCloudRealTimeResponseCodeSliceRepeat = 127,         //后台识别服务器音频分片重复
    QCloudRealTimeResponseCodeNoNetwork = -1009,         //无网络
    QCloudRealTimeResponseCodeClientTimeout = -1001,     //手机网路存在问题，请求超时
};

/**
 * 语音识别请求回包的基类
 */
@interface QCloudRealTimeResponse : NSObject

/** 任务描述代码，为retCode = 0时标示成功，其他表示为失败 */
@property (nonatomic, assign) QCloudRealTimeResponseCode code;
/** code对应的描述信息 */
@property (nonatomic, strong) NSString *message;
/** 语音流的识别id */
@property (nonatomic, strong) NSString *voiceId;          
/** 当前语音流的识别结果 */
@property (nonatomic, strong) NSString *text;
/** 语音包序列号，注意:不是语音流序列号*/
@property (nonatomic, assign) NSInteger seq;
/** 表示后面的 result_list 里面有几段结果，如果是0表示没有结果，遇到中间是静音。如果是1表示 result_list 有一个结果， 在发给服务器分片很大的情况下可能会出现多个结果，正常情况下都是1个结果。*/
@property (nonatomic, assign) NSInteger resultNumber;
/** result_list */
@property (nonatomic, copy) NSArray *resultList;
/** 识别到的总文本 */
@property (nonatomic, strong) NSString *recognizedText;
/** 语音分片请求参数 */
@property (nonatomic, strong) NSDictionary *requestParameters;

@property (nonatomic, assign) NSInteger finalN;

/** 本 message 唯一 id */
@property (nonatomic, strong) NSString *messageId;
@property (nonatomic, assign) NSInteger messageNo;
@property (nonatomic, assign) QCloudASRNetworkProtocol networkProtocol;

- (instancetype)initWithDictionary:(NSDictionary *)dic requestParameters:(NSDictionary *)requestParameters;
- (instancetype)initWithDictionary:(NSDictionary *)dic requestParameters:(NSDictionary *)requestParameters protocol:(QCloudASRNetworkProtocol)networkProtocol;

- (NSError *)getError;
- (BOOL)isEnd;

@end

/**
* 语音识别请求回包的result_list
*/
@interface QCloudRealTimeResultResponse : NSObject

/** 返回分片类型标记， 0表示一小段话开始，1表示在小段话的进行中，2表示小段话的结束 */
@property (nonatomic, assign) NSInteger sliceType;
/** 表示第几段话 */
@property (nonatomic, assign) NSInteger index;
/** 这个分片在整个音频流中的开始时间 */
@property (nonatomic, assign) NSInteger startTime;
/** 这个分片在整个音频流中的结束时间 */
@property (nonatomic, assign) NSInteger endTime;
/** 识别结果 */
@property (nonatomic, strong) NSString *voiceTextStr;

/** word_list */
@property (nonatomic, copy) NSArray *wordList;

- (instancetype)initWithDictionary:(NSDictionary *)dic;

@end

NS_ASSUME_NONNULL_END

