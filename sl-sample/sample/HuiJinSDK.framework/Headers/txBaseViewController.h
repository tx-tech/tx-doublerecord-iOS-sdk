//
//  txBaseViewController.h
//  twoRecord
//
//  Created by 洪青文 on 2020/12/2.
//  Copyright © 2020 洪青文. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface txBaseViewController : UIViewController<UIViewControllerTransitioningDelegate, UINavigationControllerDelegate,UITableViewDelegate, UITableViewDataSource>

@property (nonatomic, copy) NSString *router;
@property (nonatomic, strong) UITableView *baseGroupTableView;
@property (nonatomic, strong) UITableView *basePlainTableView;
@property (nonatomic,strong) UIButton *bottomBtn;
@property (nonatomic,assign) NSInteger page;
@property (nonatomic,assign) BOOL isDisablePanGes;//是否禁用 navigation侧滑手势

@property (nonatomic,strong) UIButton *naviRightBtn;

#pragma mark --- 列表加载函数
///下拉刷新
-(void) loadData;

///上拉加载
-(void) loadDataMore;

//设置下拉刷新
- (void)setRefreshData:(UITableView *)tableView;
// 设置上拉加载
- (void)setLoadMore:(UITableView *)tableView;

//结束刷新
- (void)endTableViewRefresh:(UITableView *)tableView;

#pragma mark 导航栏按钮
///视图的导航左边的菜单
- (UIButton*)addLeftNaviBarItem:(NSString *)leftTitle withEventBlock:(void(^)(void))block;
///设置导航栏左边按钮图片
- (UIButton *)addLeftNaviBarItemWithImage:(UIImage *)leftImage withEventBlock:(void(^)(void))block;
///视图的导航左边的菜单Button nil 为没有按钮
- (void) addLeftNaviBarItemWithButton:(UIButton * _Nullable)leftBtn withEventBlock:(void(^_Nullable)(void))block;
///视图的导航右边的菜单
- (UIButton*)addRightNaviBarItem:(NSString *)rightTitle withEventBlock:(void(^)(void))block;
///导航栏右边按钮图片
- (UIButton *)addRightNaviBarItemWithImage:(UIImage *)rightImage withEventBlock:(void(^_Nullable)(void))block;
///视图的导航右边的菜单Button nil 为没有按钮
- (void) addRightNaviBarItemWithButton:(UIButton *)btn withEventBlock:(void(^)(void))block;
///视图的导航左边-直接使用主题返回图片
- (UIButton *)addLeftNaviBarItemWithThemeBackBlock:(void(^)(void))block;
//自定义导航栏
-(void)addCustomNavigationBar:(NSString*)title;
//自定义导航栏加右侧按钮
-(void)addCustomAndRightImageBarNavigationBar:(NSString*)title RightImage:(NSString*)rightImage withEventBlock:(void(^_Nullable)(void))block;

@end

NS_ASSUME_NONNULL_END
