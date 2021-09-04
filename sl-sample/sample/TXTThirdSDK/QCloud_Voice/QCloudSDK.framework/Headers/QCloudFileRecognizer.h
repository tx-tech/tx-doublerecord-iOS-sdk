//
//  QCloudBaseRecognizer.h
//  QCloudSDK
//
//  Created by Sword on 2019/8/8.
//  Copyright © 2019 Tencent. All rights reserved.
//

#import "QCloudBaseRecognizer.h"

@protocol QCloudFileRecognizerDelegate;

@class QCloudFileRecognizeParams;

@interface QCloudFileRecognizer : QCloudBaseRecognizer

@property (nonatomic, weak) id<QCloudFileRecognizerDelegate> _Nullable delegate;

// 按设备授权需求: 开始
/**
 * 第三方设备的初始化方法
 * @param appid     腾讯云appId        基本概念见https://cloud.tencent.com/document/product/441/6194
 * @param secretId  腾讯云secretId     基本概念见https://cloud.tencent.com/document/product/441/6194
 * @param secretKey 腾讯云secretKey    基本概念见https://cloud.tencent.com/document/product/441/6194
 * @param sn 授权序列号
 * @param deviceId 第三方设备的唯一标识mac 
 */
- (instancetype _Nonnull )initWithAppId:(NSString *_Nonnull)appid secretId:(NSString *_Nonnull)secretId secretKey:(NSString *_Nonnull)secretKey sn:(NSString *_Nonnull)sn deviceId:(NSString *_Nonnull)deviceId;

/**
 * 第三方设备的初始化方法 不传deviceId
 * @param appid     腾讯云appId        基本概念见https://cloud.tencent.com/document/product/441/6194
 * @param secretId  腾讯云secretId     基本概念见https://cloud.tencent.com/document/product/441/6194
 * @param secretKey 腾讯云secretKey    基本概念见https://cloud.tencent.com/document/product/441/6194
 * @param sn 授权序列号
 */
- (instancetype _Nonnull )initWithAppId:(NSString *_Nonnull)appid secretId:(NSString *_Nonnull)secretId secretKey:(NSString *_Nonnull)secretKey sn:(NSString *_Nonnull)sn;
// 按设备授权需求: 结束

/**
 文件识别接口

 @param params 识别参数
 @return 返回请求唯一标识requestId，回调中用到
 */
- (NSInteger)recognize:(QCloudFileRecognizeParams *_Nonnull)params;

/**
 获取识别结果，走回调。该方法会轮询结果。使用场景：clear调用了之后，想获取之前的识别结果，或者识别文件太大，app关掉了，下次打开想获取上次的识别结果

 @taskId taskId 录音唯一标识
 @requestId 返回的请求唯一标识requestId
 */

- (void)pollingRecognizeResult:(NSString *_Nonnull)taskId clientRequestId:(NSString *_Nonnull)requestId;

/**
 获取所有taskId 和 requestId，只能在clear 方法调用前获取。fileRecognizerDidStart调用前为空。

 @NSArray： @[@{@"requestId":@"taskId"},...]
 */

- (NSArray *_Nullable)getAllTaskIdAndRequesId;

- (void)clear;

@end


@protocol QCloudFileRecognizerDelegate <NSObject>
@optional

/**
 录音文件识别成功回调

 @param recognizer 录音文件识别器
 @param requestId 请求唯一标识requestId,recognize:接口返回
 @param text 识别文本
 @param resultData 原始数据
 */
- (void)fileRecognizer:(QCloudFileRecognizer *_Nullable)recognizer requestId:(NSInteger)requestId text:(nullable NSString *)text resultData:(nullable NSDictionary *)resultData;
/**
 录音文件识别失败回调
 
 @param recognizer 录音文件识别器
 @param requestId 请求唯一标识requestId,recognize:接口返回
 @param error 识别错误，出现错误此字段有
 @param resultData 原始数据
 */
- (void)fileRecognizer:(QCloudFileRecognizer *_Nullable)recognizer requestId:(NSInteger)requestId error:(nullable NSError *)error resultData:(nullable NSDictionary *)resultData;


/**
 录音文件已上传服务器，正在排队识别中
 
 @param recognizer 录音文件识别器
 @param requestId 请求唯一标识requestId,recognize:接口返回
 @param taskId 向服务器查询识别结果唯一标识
 */
- (void)fileRecognizerDidStart:(QCloudFileRecognizer *_Nullable)recognizer requestId:(NSString *_Nonnull)requestId taskId:(NSString *_Nonnull)taskId;

@end
