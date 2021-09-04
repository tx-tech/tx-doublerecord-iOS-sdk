//
//  TXTManage.h
//  HuiJinSDK
//
//  Created by 洪青文 on 2021/7/20.
//

#import <Foundation/Foundation.h>
#import "TXTCustomConfig.h"

NS_ASSUME_NONNULL_BEGIN

typedef void (^TXTCallback)(int code, NSString *desc);

@interface TXTManage : NSObject

@property (strong, nonatomic) TXTCallback callback;
//@property (assign, nonatomic) UIViewController *mainVC;
//初始化
+ (instancetype)sharedInstance;

- (void)setEnvironment:(NSString *)environment wechat:(TXTCustomConfig *)txtCustomConfig;
//跳到工单详情页面
- (void)gotoOrderDetailsPage:(NSString *)account FullName:(NSString *)fullName TaskId:(NSString *)taskId Address:(NSString *)adr Organization:(NSString *)org Sign:(NSString *)sign CallBack:(TXTCallback)callback;

//跳到工单列表页面
-(void)gotoOrderListPage:(NSString *)account FullName:(NSString *)fullName Address:(NSString *)adr Organization:(NSString *)org Sign:(NSString *)sign CallBack:(TXTCallback)callback;
//跳转到待上传视频页面
-(void)gotoVideoUploadPage:(NSString *)taskId Account:(NSString *)account FullName:(NSString *)fullName Organization:(NSString *)org Sign:(NSString *)sign CallBack:(TXTCallback)callback;

//跳转到待上传视频页面
-(void)gotoAppPage:(NSString *)account FullName:(NSString *)fullName TaskId:(NSString *)taskId Address:(NSString *)adr Organization:(NSString *)org Sign:(NSString *)sign CallBack:(TXTCallback)callback;
@end

NS_ASSUME_NONNULL_END
