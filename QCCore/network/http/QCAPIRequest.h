//
//  QCBaseRequest.h
//  QCCore
//
//  Created by Chen on 15/4/1.
//  Copyright (c) 2015年 Quancheng-ec. All rights reserved.
//

#import "QCHttpRequest.h"

/**
 网络数据的缓存策略
 */
typedef NS_OPTIONS(short, CacheStrategy) {
    /// 网络数据的缓存策略：不缓存
    CacheStrategyNone               = 0,
    /// 网络数据的缓存策略：5分钟
    CacheStrategyNormal,
    /// 网络数据的缓存策略：1小时
    CacheStrategyHourly,
    /// 网络数据的缓存策略：1天
    CacheStrategyDaily,
    /// 网络数据的缓存策略：永久
    CacheStrategyPersist,
    /// 网络数据的缓存策略：优先读取缓存，请求结束刷新缓存
    CacheStrategyCachePrecedence
};

@class QCAPIRequest;

typedef void (^APISuccessBlock)(QCAPIRequest * _Nonnull request);
typedef void (^APIFailedBlock)(QCAPIRequest * _Nonnull request);

@interface QCAPIRequest : QCHttpRequest

//Whether response data is from cache or not
@property (nonatomic, assign, readonly) BOOL isFromCache;

//The strategy of how to use cache
@property (nonatomic, assign) CacheStrategy cacheStrategy;

//Response data in dictionary format
@property (nonatomic, strong, readonly, nullable) NSDictionary *responseDict;

//已将responseModel替换为只读属性访问

/// API返回状态码
@property (readonly) int status;
/// API返回数据内容
@property (readonly, nullable) NSDictionary *data;
/// API返回附加信息
@property (readonly, nullable) NSString *message;

/**
 创建请求
 @param apiName 只需要传入API名即可，无需填入完整URL
 @param requestMethod 即HTTPMethod
 @return QCAPIRequest对象
*/
- (nullable id)initWithAPIName:(nonnull NSString *)apiName
                 requestMethod:(RequestMethod)requestMethod;

- (void)startWithAPISuccessBlock:(nullable APISuccessBlock)successBlock
                  APIFailedBlock:(nullable APISuccessBlock)failedBlock;


#pragma mark - 失效函数

/// @deprecated 使用
- (nullable id)initWithUrl:(nonnull NSString *)url DEPRECATED_ATTRIBUTE;
- (nullable id)initWithUrl:(nonnull NSString *)url requestMethod:(RequestMethod)requestMethod DEPRECATED_ATTRIBUTE;
- (nullable id)initWithUrl:(nonnull NSString *)url requestMethod:(RequestMethod)requestMethod timeoutInterval:(NSTimeInterval)timeoutInterval DEPRECATED_ATTRIBUTE;

/// @unavailable 弃用父类函数
- (void)startWithSuccessBlock:(nullable SuccessBlock)successBlock failedBlock:(nullable FailedBlock)failedBlock NS_UNAVAILABLE;

/// @deprecated 为保证入口统一，弃用start函数，统一使用startWithAPISuccessBlock:APIFailedBlock:函数
- (void)start DEPRECATED_ATTRIBUTE;

@end


