//
//  BDWalletSDKMainManager.h
//  BaiduWalletSDK
//
//  Created by lushuang on 14-3-13.
//  Copyright (c) 2014年 baidu. All rights reserved.
//

/******************************************************/
/******************* 百度钱包标准SDK ********************/
/******************************************************/

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <CoreLocation/CoreLocation.h>

@class BDWalletSchemePayInfo;

// 进入SDK返回的错误类型
typedef enum BDWalletSDK_Error_Type {
    BDWalletSDK_Error_None              = 0,    // 无错
    BDWalletSDK_Error_Net               = 1,    // 网络异常
    BDWalletSDK_Error_OrderInfo         = 2,    // orderInfo异常
    BDWalletSDK_Error_InvalidDelegate   = 3,    // 传入无效Delegate
    BDWalletSDK_Error_Unlogin           = 4,    // 未登录
    BDWalletSDK_Error_Other             = 5,    // 其他未知错误
    BDWalletSDK_Error_InvalidParameters = 6,    // 无效参数
    BDWalletSDK_Error_InvalidLogin      = 5003, // 无效登录状态
} BDWalletSDKErrorType;

@protocol BDWalletSDKMainManagerDelegate <NSObject>

@required

//! 支付回调接口
- (void)BDWalletPayResultWithCode:(int)statusCode payDesc:(NSString *)payDescs;

@end

@interface BDWalletSDKMainManager : NSObject

#pragma mark - 必须设置的Delegate

//! 优先设置rootVC，如果delegate是一个UIViewController 可以将rootVC设置为nil或与delegate一致
@property (nonatomic, weak) UIViewController *rootViewController;

//! delegate 与 rootViewController需要匹配设置
@property (nonatomic, weak) id<BDWalletSDKMainManagerDelegate> delegate;

//! app的Scheme，必须传
@property(nonatomic, copy) NSString *sourceAppScheme;

//! app的名字，必须传
@property(nonatomic, copy) NSString *sourceAppName;


#pragma mark - 百度钱包标准SDK接口

+ (BDWalletSDKMainManager *)getInstance;

#pragma mark - 百度钱包收银台接口

//! 支付接口,delegateT需要是一个viewController
- (BDWalletSDKErrorType)doPayWithOrderInfo:(NSString *)orderInfo
                                   params:(NSDictionary *)params
                                 delegate:(id<BDWalletSDKMainManagerDelegate>)delegateT;


/*
 通过钱包sdk打开网页
 url        :   url
 rootVC     :   宿主传递VC
 params     :   扩展字段
 */
- (BDWalletSDKErrorType)openWebPageByWalletSDKWithDelegate:(id<BDWalletSDKMainManagerDelegate>)delegateT
                                                       url:(NSString*)url
                                                    rootVC:(UIViewController*)rootVC
                                                    params:(NSDictionary *)params;

/*
 宿主需在AppDelegate中实现
 */
- (BOOL)application:(UIApplication *)application
            openURL:(NSURL *)url
  sourceApplication:(NSString *)sourceApplication
         annotation:(id)annotation;

@end
