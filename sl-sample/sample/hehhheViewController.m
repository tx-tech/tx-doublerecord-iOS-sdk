//
//  hehhheViewController.m
//  txWhiteBoardSample
//
//  Created by 洪青文 on 2020/9/3.
//  Copyright © 2020 洪青文. All rights reserved.
//

#import "hehhheViewController.h"

//#import <TXTWhiteBoard/TXTManage.h>
//#import <TXTWhiteBoard/TXTCustomConfig.h>
#import "NSString+TXTAES.h"
#import "BRPickerView.h"
#import "settingViewController.h"

#import <HuiJinSDK/TXTManage.h>
#import <HuiJinSDK/testManage.h>
#import <HuiJinSDK/TXTCustomConfig.h>
#import <HuiJinSDK/txRecordDetailViewController.h>
#import <HuiJinSDK/txBaseViewController.h>



//微信appID 自行配置
#define WECHAT_APPID @""
#define UniversalLink @""
#define WechatUserName @""
#define PSW_AES_KEY @""
#define AES_IV_PARAMETER @""

@interface hehhheViewController ()
@property (weak, nonatomic) IBOutlet UITextField *agentCode;//代理人姓名
@property (weak, nonatomic) IBOutlet UITextField *agentFlowid;//业务单号
@property (weak, nonatomic) IBOutlet UITextField *agentName;//代理人编码
@property (weak, nonatomic) IBOutlet UITextField *orgName;
@property (weak, nonatomic) IBOutlet UILabel *smalllab;
@property (weak, nonatomic) IBOutlet UILabel *phonelab;
@property (weak, nonatomic) IBOutlet UIButton *smallbtn;
@property (weak, nonatomic) IBOutlet UIButton *appbtn;
@property (weak, nonatomic) IBOutlet UIButton *actionBtn;

@property (strong, nonatomic) TXTCustomConfig *config;

@end

@implementation hehhheViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.title = @"账号登录";
    [self.smallbtn setTitle:@" 测试环境" forState:UIControlStateNormal];
    [self.appbtn setTitle:@" 测试环境" forState:UIControlStateNormal];
    self.phonelab.text = @"app是生产环境";
    self.smallbtn.layer.borderWidth = 0.5;
    self.smallbtn.layer.borderColor = [UIColor lightGrayColor].CGColor;
    self.smallbtn.layer.cornerRadius = 3;
    self.smallbtn.layer.masksToBounds = YES;
    self.appbtn.layer.borderWidth = 0.5;
    self.appbtn.layer.borderColor = [UIColor lightGrayColor].CGColor;
    self.appbtn.layer.cornerRadius = 3;
    self.appbtn.layer.masksToBounds = YES;
    UIBarButtonItem *rightBarItem = [[UIBarButtonItem alloc] initWithTitle:@"设置" style:UIBarButtonItemStylePlain target:self action:@selector(setting)];
    self.navigationItem.rightBarButtonItem = rightBarItem;
    self.config = [TXTCustomConfig sharedInstance];
    self.config.appid = WECHAT_APPID;
    self.config.universalLink = UniversalLink;
    self.config.userName = WechatUserName;
    self.config.miniprogramTitle = @"";
    self.config.miniprogramCard = @"";
    self.config.isShowInviteButton = YES;
    self.config.isShowTemporaryButton = YES;
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(listenEvent:) name:@"txVideoBtClickListener" object:nil];
    
    [[testManage sharedInstance] test];
}

- (void)viewWillAppear:(BOOL)animated{
    [super viewWillAppear:animated];
    if ([self.route isEqualToString:@"creat"]) {
        [self.actionBtn setTitle:@"预约会议" forState:UIControlStateNormal];
    }else{
        [self.actionBtn setTitle:@"开始会议" forState:UIControlStateNormal];
    }
   
    if ([self.route isEqualToString:@"creat"]) {
        
    }else if ([self.route isEqualToString:@"detail"]){
        
    }else if ([self.route isEqualToString:@"list"]){
       
    }
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(textTTsAction:) name:@"" object:nil];
}

- (void)listenEvent:(NSNotification *)notification{
    NSLog(@"listenEvent == %@",notification);
}


- (IBAction)start:(id)sender {
    [self.view endEditing:YES];
    NSString *agentName = self.agentName.text;
    NSString *orgName = self.orgName.text;
    if ([agentName isEqualToString:@""] || agentName == nil) {
        
        return;
    }
    
    NSDate* date = [NSDate dateWithTimeIntervalSinceNow:0];//获取当前时间0秒后的时间
    NSTimeInterval time=[date timeIntervalSince1970];
    NSString *timeString = [NSString stringWithFormat:@"%@%.0f",orgName,time];
    //    NSString *sign = [timeString aci_encryptWithAES];
    
    
    //@"gh_9fd3da8ad9f6"
    NSString *smallstr = self.smallbtn.titleLabel.text;
    NSString *miniprogramType = @"1";
    if ([smallstr isEqualToString:@" 生产环境"]) {
        miniprogramType = @"2";
    }else if ([smallstr isEqualToString:@" 开发环境"]) {
        miniprogramType = @"0";
    }
    
    NSString *appstr = self.appbtn.titleLabel.text;
    NSString *appType = @"1";
    [[NSUserDefaults standardUserDefaults] setObject:PSW_AES_KEY forKey:@"PSW_AES_KEY"];
    [[NSUserDefaults standardUserDefaults] setObject:AES_IV_PARAMETER forKey:@"AES_IV_PARAMETER"];
    if ([appstr isEqualToString:@" 生产环境"]) {
        appType = @"2";
        [[NSUserDefaults standardUserDefaults] setObject:PSW_AES_KEY forKey:@"PSW_AES_KEY"];
        [[NSUserDefaults standardUserDefaults] setObject:AES_IV_PARAMETER forKey:@"AES_IV_PARAMETER"];
    }else if ([smallstr isEqualToString:@" 开发环境"]) {
        appType = @"0";
    }
    
    NSString *sign = [timeString aci_encryptWithAES];
    //    NSDictionary *dict = @{@"appid":@"wx8e6096173bff1149",@"universalLink":@"https://video-sells-test.ikandy.cn/txWhiteBoard/",@"userName":@"gh_9fd3da8ad9f6",@"miniprogramType":miniprogramType};
    
    NSDictionary *addressDict = @{@"adr":@"eeeeeee",@"city":@"ddd111111111",@"latitude":@11.22,@"longitude":@123.9,@"province":@"hhhhhhhhhhhhh",@"accuracy":@1};
    
    self.config.miniprogramType = miniprogramType;
    
    
    [[TXTManage sharedInstance] setEnvironment:appType wechat:self.config];
//
    if ([self.route isEqualToString:@"creat"]) {
        [[TXTManage sharedInstance] gotoAppPage:self.agentName.text FullName:self.agentCode.text TaskId:self.agentFlowid.text Address:@"" Organization:orgName Sign:sign CallBack:^(int code, NSString * _Nonnull desc) {
            NSLog(@"%d",code);
        }];
    }else if ([self.route isEqualToString:@"detail"]){
        [[TXTManage sharedInstance] gotoOrderDetailsPage:self.agentName.text FullName:self.agentCode.text TaskId:self.agentFlowid.text Address:@"" Organization:orgName Sign:sign CallBack:^(int code, NSString * _Nonnull desc) {
            NSLog(@"%d",code);
            if (code == 0) {
                
            }else{
                UIAlertController *alert = [UIAlertController alertControllerWithTitle:@"" message:desc preferredStyle:UIAlertControllerStyleAlert];
                UIAlertAction *action2 = [UIAlertAction actionWithTitle:@"确认" style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
                    //确认处理
                }];
                [alert addAction:action2];
                [self.navigationController presentViewController:alert animated:YES completion:nil];
            }
            
//            txRecordDetailViewController *classRoom = [[txRecordDetailViewController alloc] init];
//            classRoom.flowId = self.agentFlowid.text;
//            [self.navigationController pushViewController:classRoom animated:YES];
        }];
    }else if ([self.route isEqualToString:@"list"]){
        [[TXTManage sharedInstance] gotoOrderListPage:self.agentName.text FullName:self.agentCode.text Address:@"" Organization:orgName Sign:sign CallBack:^(int code, NSString * _Nonnull desc) {
            NSLog(@"%d",code);
        }];
    }else if ([self.route isEqualToString:@"upload"]){
        [[TXTManage sharedInstance] gotoVideoUploadPage:self.agentFlowid.text Account:self.agentCode.text FullName:self.agentCode.text Organization:orgName Sign:sign CallBack:^(int code, NSString * _Nonnull desc) {
            NSLog(@"%d",code);
    
        }];
    }
}

- (void)creat{
    
}

- (void)start{
    
}

- (IBAction)chooseSmall:(id)sender {
    /// 1.单列字符串选择器（传字符串数组）
    [self.view endEditing:YES];
    BRStringPickerView *stringPickerView = [[BRStringPickerView alloc]init];
    stringPickerView.pickerMode = BRStringPickerComponentSingle;
    stringPickerView.title = @"选择环境";
    stringPickerView.dataSourceArr = @[@" 测试环境", @" 生产环境",@" 开发环境"];
    stringPickerView.selectIndex = 0;
    stringPickerView.resultModelBlock = ^(BRResultModel *resultModel) {
        NSLog(@"选择的值：%@", resultModel.value);
        [self.smallbtn setTitle:resultModel.value forState:UIControlStateNormal];
        if ([resultModel.value isEqualToString:@" 生产环境"]) {
            self.smalllab.text = @"小程序是生产环境";
        }else if ([resultModel.value isEqualToString:@" 测试环境"]){
            self.smalllab.text = @"小程序是测试环境";
        }else{
            self.smalllab.text = @"小程序是开发环境";
        }
    };

    [stringPickerView show];
    
}
- (IBAction)chooseApp:(id)sender {
    [self.view endEditing:YES];
    BRStringPickerView *stringPickerView = [[BRStringPickerView alloc]init];
    stringPickerView.pickerMode = BRStringPickerComponentSingle;
    stringPickerView.title = @"选择环境";
    stringPickerView.dataSourceArr = @[@" 测试环境", @" 生产环境",@" 开发环境"];
    stringPickerView.selectIndex = 0;
    stringPickerView.resultModelBlock = ^(BRResultModel *resultModel) {
        NSLog(@"选择的值：%@", resultModel.value);
        [self.appbtn setTitle:resultModel.value forState:UIControlStateNormal];
        if ([resultModel.value isEqualToString:@" 生产环境"]) {
            self.phonelab.text = @"app是生产环境";
            self.orgName.text = @"gsc_test";
        }else if ([resultModel.value isEqualToString:@" 测试环境"]){
            self.phonelab.text = @"app是测试环境";
            self.orgName.text = @"test_org2";
        }else{
            self.phonelab.text = @"app是开发环境";
        }
    };

    [stringPickerView show];
}


-(void) touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    [self.agentName resignFirstResponder];
    [self.orgName resignFirstResponder];
}

- (void)setting{
    settingViewController *vc = [[settingViewController alloc] initWithNibName:@"settingViewController" bundle:nil];
    [self.navigationController pushViewController:vc animated:YES];
}
   
@end
