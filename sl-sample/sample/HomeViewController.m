//
//  HomeViewController.m
//  sample
//
//  Created by 洪青文 on 2021/2/2.
//  Copyright © 2021 洪青文. All rights reserved.
//

#import "HomeViewController.h"
#import "hehhheViewController.h"

@interface HomeViewController ()
@property (weak, nonatomic) IBOutlet UILabel *roomId;
@property (weak, nonatomic) IBOutlet UIButton *roomIdCopyBtn;

@end

@implementation HomeViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.title = @"小腾讯";
    
}

- (void)viewWillAppear:(BOOL)animated{
    [super viewWillAppear:animated];
    NSString *roomid = [[NSUserDefaults standardUserDefaults] objectForKey:@"inviteNumber"];
    
    
    if ([roomid isEqualToString:@""] || roomid == nil) {
        self.roomIdCopyBtn.hidden = YES;
        self.roomId.text = @"暂无预约";
    }else{
        self.roomIdCopyBtn.hidden = NO;
        self.roomId.text = [NSString stringWithFormat:@"%@",roomid];
    }
}

//创建保单信息
- (IBAction)joinRoom:(id)sender {
    hehhheViewController *vc = [[hehhheViewController alloc] init];
    vc.route = @"creat";
    [self.navigationController pushViewController:vc animated:YES];
}
//投保中双录
- (IBAction)startRoom:(id)sender {
    hehhheViewController *vc = [[hehhheViewController alloc] init];
    vc.route = @"detail";
    [self.navigationController pushViewController:vc animated:YES];
}
//我的双录
- (IBAction)creatRoom:(id)sender {
    hehhheViewController *vc = [[hehhheViewController alloc] initWithNibName:@"hehhheViewController" bundle:nil];
    vc.route = @"list";
    [self.navigationController pushViewController:vc animated:YES];
}
- (IBAction)uploadFile:(id)sender {
    hehhheViewController *vc = [[hehhheViewController alloc] initWithNibName:@"hehhheViewController" bundle:nil];
    vc.route = @"upload";
    [self.navigationController pushViewController:vc animated:YES];
}
//配置环境信息
- (IBAction)copyRoomId:(id)sender {
    
}


@end
