/////////////////////////////////////////////////////////////////////////
///@author 中泰证券股份有限公司
///@file xtp_algox_api.h
///@brief 定义客户端交易接口
/////////////////////////////////////////////////////////////////////////

#ifndef _XTP_ALGOX_API_H_
#define _XTP_ALGOX_API_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "algox_api_struct.h"

#if defined(ISLIB) && defined(WIN32)
#ifdef LIB_ALGOX_API_EXPORT
#define ALGOX_API_EXPORT __declspec(dllexport)
#else
#define ALGOX_API_EXPORT __declspec(dllimport)
#endif
#else
#define ALGOX_API_EXPORT 
#endif

/*!
* \class XTPX::API::AlgoXSpi
*
* \brief 交易接口响应类
*
* \author 中泰证券股份有限公司
* \date 十一月 2025
*/

namespace XTPX {
	namespace API {

		class AlgoXSpi
		{
		public:
			///algo业务中报送策略单的响应
			///@param strategy_info 用户报送的策略单的具体信息
			///@param error_info 报送策略单发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
			///@param user_name 资金账户
			///@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
			virtual void OnInsertAlgoOrder(XTPStrategyInfoStruct* strategy_info, XTPARI *error_info, char* user_name) {};

			///algo业务中撤销策略单的响应
			///@param strategy_info 用户撤销的策略单的具体信息
			///@param error_info 撤销策略单发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
			///@param user_name 资金账户
			///@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
			virtual void OnCancelAlgoOrder(XTPStrategyInfoStruct* strategy_info, XTPARI *error_info, char* user_name) {};

			///algo业务中查询策略列表的响应
			///@param strategy_info 策略具体信息
			///@param strategy_param 此策略中包含的参数，如果error_info.error_id为0时，有意义
			///@param error_info 查询查询策略列表发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
			///@param request_id 此消息响应函数对应的请求ID
			///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
			///@param user_name 资金账户
			///@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
			virtual void OnQueryStrategy(XTPStrategyInfoStruct* strategy_info, char* strategy_param, XTPARI *error_info, int32_t request_id, bool is_last, char* user_name) {};

			///algo业务中报送母单创建时的推送消息(包括其他客户端创建的母单)
			///@param strategy_info 策略具体信息
			///@param strategy_param 此策略中包含的参数
			///@param user_name 资金账户
			///@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
			virtual void OnNewStrategyCreateReport(XTPStrategyInfoStruct* strategy_info, char* strategy_param, char* user_name) {};

			///algo业务中策略运行时策略状态通知
			///@param strategy_state 用户策略运行情况的状态通知
			///@param user_name 资金账户
			///@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
			virtual void OnStrategyStateReport(XTPStrategyStateReport* strategy_state, char* user_name) {};

			///algo业务中用户建立算法通道的消息响应
			///@param user 用户名
			///@param error_info 建立算法通道发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误，即算法通道成功
			///@param user_name 资金账户
			///@remark 算法通道建立成功后，才能对用户创建策略等操作，一个用户只能拥有一个算法通道，如果之前已经建立，则无需重复建立
			virtual void OnALGOUserEstablishChannel(char* user_name, XTPARI* error_info) {};

			///当客户端与AlgoBus通信连接断开时，该方法被调用。
			///@param reason 错误原因，请与错误代码表对应
			///@remark 请不要堵塞此线程，否则会影响algo的登录
			virtual void OnAlgoDisconnected(int reason) {};

			///当客户端与AlgoBus断线连接时，该方法被调用，仅在断线重连成功后会被调用。
			virtual void OnAlgoConnected() {};

			///algo业务中策略运行时策略指定证券执行状态通知
			///@param strategy_symbol_state 用户策略指定证券运行情况的状态通知
			///@param user_name 资金账户
			///@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
			virtual void OnStrategySymbolStateReport(XTPStrategySymbolStateReport* strategy_symbol_state, char* user_name) {};

			///algo业务中算法推荐的响应
			///@param basket_flag 是否将满足条件的推荐结果打包成母单篮的标志，与请求一致，如果此参数为true，那么请以返回的strategy_param为准
			///@param recommendation_info 推荐算法的具体信息，当basket_flag=true时，此结构体中的market和ticker将没有意义，此时请以strategy_param为准
			///@param strategy_param 算法参数，可直接用来创建母单，如果error_info.error_id为0时，有意义
			///@param error_info 请求推荐算法发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
			///@param request_id 此消息响应函数对应的请求ID
			///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
			///@param user_name 资金账户
			///@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
			virtual void OnStrategyRecommendation(bool basket_flag, XTPStrategyRecommendationInfo* recommendation_info, char* strategy_param, XTPARI *error_info, int32_t request_id, bool is_last, char* user_name) {};
		};
	}
}

#ifndef WINDOWS
#if __GNUC__ >= 4
#pragma GCC visibility push(default)
#endif
#endif

/*!
* \class XTPX::API::AlgoXApi
*
* \brief 算法交易类接口类
*
* \author 中泰证券股份有限公司
* \date 十一月 2025
*/
namespace XTPX {
	namespace API {

		class ALGOX_API_EXPORT AlgoXApi
		{
		public:
			///创建AlgoXApi
			///@param client_id （必须输入）客户端id，用于区分同一用户的不同客户端，由用户自定义
			///@param save_file_path （必须输入）存贮订阅信息文件的目录，请设定一个真实存在的有可写权限的路径
			///@param log_level 日志输出级别
			///@return 创建出的UserApi
			///@remark 只能创建一次，系统不支持过夜，请确保每天开盘前重新启动
			static AlgoXApi *CreateAlgoXApi(uint8_t client_id, const char *save_file_path, XTP_ALGO_LOG_LEVEL log_level = XTP_ALGO_LOG_LEVEL_DEBUG);

			///注册回调接口
			///@param spi 派生自回调接口类的实例，请在登录之前设定
			virtual void RegisterSpi(AlgoXSpi *spi) = 0;

			///获取API的系统错误
			///@return 返回的错误信息，可以在LoginAlgo、InsertAlgoOrder返回值为0时调用，获取失败的原因
			///@remark 可以在调用api接口失败时调用，例如LoginAlgo失败时
			virtual XTPARI *GetApiLastError() = 0;

			///获取API的发行版本号
			///@return 返回api发行版本号
			virtual const char* GetApiVersion() = 0;

			///设置软件开发版本号
			///@param version 用户开发软件版本号，非api发行版本号，长度不超过15位，以'\0'结尾
			///@remark 此函数必须在LoginAlgo之前调用，标识的是客户端版本号，而不是API的版本号，由用户自定义
			virtual void SetSoftwareVersion(const char* version) = 0;

			///设置心跳检测时间间隔，单位为秒
			///@param interval 心跳检测时间间隔，单位为秒
			///@remark 此函数必须在LoginAlgo之前调用
			virtual void SetHeartBeatInterval(uint32_t interval) = 0;

			///用户登录algo服务器请求
			///@return 表明此资金账号登录是否成功，非“0”表示登录失败，可以调用GetApiLastError()来获取错误代码，“0”表示登录成功
			///@param ip algo服务器地址，类似“127.0.0.1”
			///@param port algo服务器端口号
			///@param user 登录用户名
			///@param password 登录密码
			///@param sock_type “1”代表TCP，“2”代表UDP，目前暂时只支持TCP
			///@remark 此函数为同步阻塞式，不需要异步等待登录成功，当函数返回即可进行后续操作，此api只需调用一次，所有用户共用即可
			virtual int LoginALGO(const char* ip, int port, const char* algo_user, const char* password, XTP_ALGO_PROTOCOL_TYPE sock_type) = 0;

			///algo业务中用户报算法单请求
			///@return 算法报单请求发送是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
			///@param strategy_type 需要创建的策略类型
			///@param client_strategy_id 用户自定义id，帮助用户定位
			///@param strategy_param 策略参数
			///@param user_name 资金账户
			///@remark 仅能在用户建立算法通道后使用，算法单的异步通知
			virtual int InsertAlgoOrder(uint32_t strategy_type, uint64_t client_strategy_id, char* strategy_param, const char* user_name) = 0;

			///algo业务中用户撤销算法单请求
			///@return 请求发送是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
			///@param cancel_flag 是否需要算法去处理已下的算法子单标志，true-交给算法自行处理，包括撤单、平仓等，算法处理完成后会通知客户；false-立即停止算法母单的执行，此时算法平台会对已下的子单做撤单操作，其余的平仓等操作需要客户自己处理
			///@param xtp_strategy_id 需要撤销的算法单在xtp algobus系统中的id
			///@param user_name 资金账户
			///@remark 仅能在用户建立算法通道后调用
			virtual int CancelAlgoOrder(bool cancel_flag, uint64_t xtp_strategy_id, const char* user_name) = 0;

			///algo业务中查询用户策略请求
			///@return 请求发送是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
			///@param strategy_type 需要查询的策略类型，可填0
			///@param client_strategy_id 需要查询的策略用户自定义id，可填0
			///@param xtp_strategy_id 需要查询的策略在xtp系统中的id，如果指定，就一定按指定查询，如果填0，则按其他筛选条件查询
			///@param user_name 资金账户
			///@param request_id 用于用户定位查询响应的ID，由用户自定义
			///@remark xtp_strategy_id条件的优先级最高，只有当xtp_strategy_id为0时，其他条件才生效，此条请求可能对应多条回应消息
			virtual int QueryStrategy(uint32_t strategy_type, uint64_t client_strategy_id, uint64_t xtp_strategy_id, const char* user_name, int32_t request_id) = 0;

			///用户请求使用algo服务器建立算法通道
			///@return 表明此资金账号建立算法通道请求消息发送是否成功，非“0”表示发送失败，可以调用GetApiLastError()来获取错误代码，“0”表示发送成功
			///@param algo_user 登录用户名
			///@param password 登录密码
			///@remark 此函数为异步方式，一个用户只能拥有一个算法通道，如果之前已经建立，则无需重复建立
			virtual int ALGOUserEstablishChannel(const char* user_name, const char* password) = 0;

			///algo业务中请求推荐算法
			///@return 请求发送是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
			///@param basket_flag 是否将满足条件的推荐结果打包成母单篮的标志，true-打包
			///@param basket_param 需要算法推荐的证券列表，为json字串，具体格式参考说明文档或咨询运营人员
			///@param user_name 资金账户
			///@param request_id 用于用户定位查询响应的ID，由用户自定义
			///@remark 此条请求可能对应多条回应消息，此功能上线时间视服务器后台支持情况而定，具体以运营通知时间为准
			virtual int StrategyRecommendation(bool basket_flag, char* basket_param, const char* user_name, int32_t request_id) = 0;
			
		protected:
			~AlgoXApi() {};
		};

	}
}

#ifndef WINDOWS
#if __GNUC__ >= 4
#pragma GCC visibility pop
#endif
#endif


#endif
