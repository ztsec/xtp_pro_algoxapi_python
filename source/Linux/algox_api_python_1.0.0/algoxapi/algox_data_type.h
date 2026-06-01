/////////////////////////////////////////////////////////////////////////
///@author 中泰证券股份有限公司
///@file algo_x_data_type.h
///@brief 定义业务公共数据结构
/////////////////////////////////////////////////////////////////////////
#ifndef _XTP_ALGOX_DATA_TYPE_H_
#define _XTP_ALGOX_DATA_TYPE_H_

#if defined(_MSC_VER) && _MSC_VER<1600
typedef signed char        int8_t;
typedef short              int16_t;
typedef int                int32_t;
typedef long long          int64_t;
typedef unsigned char      uint8_t;
typedef unsigned short     uint16_t;
typedef unsigned int       uint32_t;
typedef unsigned long long uint64_t;
#else
#include <stdint.h>
#endif

namespace XTPX {

	namespace API {

		/// 存放证券代码的字符串长度
		constexpr uint32_t XTP_ALGO_TICKER_LEN = 16;
		///错误信息的字符串长度
		constexpr uint32_t XTP_ALGO_ERR_MSG_LEN = 124;
		/// 用户资金账户的字符串长度
		constexpr uint32_t XTP_ALGO_ACCOUNT_NAME_LEN = 16;
		/// 用户资金账户的密码字符串长度
		constexpr uint32_t XTP_ALGO_ACCOUNT_PASSWORD_LEN = 64;

		/// IP地址的字符串长度
		constexpr uint32_t XTP_ALGO_INET_ADDRESS_STR_LEN = 64;
		/// MAC地址的字符串长度
		constexpr uint32_t XTP_ALGO_MAC_ADDRESS_LEN = 19;
		/// 硬盘序列号的字符串长度
		constexpr uint32_t XTP_ALGO_HARDDISK_SN_LEN = 33;
		/// MacOS系统序列号的字符串长度
		constexpr uint32_t XTP_ALGO_MACOS_SNO_LEN = 21;
		/// 移动Android端标识符的字符串长度
		constexpr uint32_t XTP_ALGO_IMEI_LEN = 16;
		/// 移动ios端标识符的字符串长度
		constexpr uint32_t XTP_ALGO_IDFV_LEN = 37;
		/// 其他移动端标识符的字符串长度
		constexpr uint32_t XTP_ALGO_GUID_LEN = 40;
		/// 手机号码的字符串长度
		constexpr uint32_t XTP_ALGO_TEL_LEN = 12;
		/// 软件开发代码的字符串长度
		constexpr uint32_t XTP_ALGO_SCD_LEN = 3;

		/// 存放版本号的字符串长度
		constexpr uint32_t XTP_ALGO_VERSION_LEN = 13;
		/// 版本号类型
		typedef char XTPAlgoVersionType[XTP_ALGO_VERSION_LEN];

		/////////////////////////////////////////////////////////////////////////
		///@brief XTP_ALGO_LOG_LEVEL是日志输出级别类型
		/////////////////////////////////////////////////////////////////////////
		typedef uint8_t XTP_ALGO_LOG_LEVEL;

		///<严重错误级别
		constexpr uint32_t XTP_ALGO_LOG_LEVEL_FATAL = 0;
		///<错误级别
		constexpr uint32_t XTP_ALGO_LOG_LEVEL_ERROR = 1;
		///<警告级别
		constexpr uint32_t XTP_ALGO_LOG_LEVEL_WARNING = 2;
		///<info级别
		constexpr uint32_t XTP_ALGO_LOG_LEVEL_INFO = 3;
		///<debug级别
		constexpr uint32_t XTP_ALGO_LOG_LEVEL_DEBUG = 4;
		///<trace级别
		constexpr uint32_t XTP_ALGO_LOG_LEVEL_TRACE = 5;

		/////////////////////////////////////////////////////////////////////////
		///@brief XTP_ALGO_PROTOCOL_TYPE是通讯传输协议方式
		/////////////////////////////////////////////////////////////////////////
		typedef uint8_t XTP_ALGO_PROTOCOL_TYPE;

		///<采用TCP方式传输
		constexpr uint32_t XTP_ALGO_PROTOCOL_TCP = 1;
		///<采用UDP方式传输(仅行情接口支持)
		constexpr uint32_t XTP_ALGO_PROTOCOL_UDP = 2;


		///@brief XTPStrategyStateType策略状态类型
		typedef uint8_t XTPStrategyStateType;

		///创建中
		constexpr uint32_t XTP_STRATEGY_STATE_CREATING = 0;
		///已创建
		constexpr uint32_t XTP_STRATEGY_STATE_CREATED = 1;
		///开始执行中
		constexpr uint32_t XTP_STRATEGY_STATE_STARTING = 2;
		///已执行
		constexpr uint32_t XTP_STRATEGY_STATE_STARTED = 3;
		///停止中
		constexpr uint32_t XTP_STRATEGY_STATE_STOPPING = 4;
		///已停止
		constexpr uint32_t XTP_STRATEGY_STATE_STOPPED = 5;
		///销毁中
		constexpr uint32_t XTP_STRATEGY_STATE_DESTROYING = 6;
		///已销毁
		constexpr uint32_t XTP_STRATEGY_STATE_DESTROYED = 7;
		///发生错误
		constexpr uint32_t XTP_STRATEGY_STATE_ERROR = 8;

		//////////////////////////////////////////////////////////////////////////
		///@brief XTP_MARKET_TYPE市场类型，交易里使用
		//////////////////////////////////////////////////////////////////////////
		typedef uint32_t XTP_ALGO_MARKET_TYPE;

		///初始化值或者未知
		constexpr uint32_t XTP_ALGO_MKT_INIT = 0;   
		///深圳A股
		constexpr uint32_t XTP_ALGO_MKT_SZ_A = 1;     
		///上海A股
		constexpr uint32_t XTP_ALGO_MKT_SH_A = 2;     
		///北京A股
		constexpr uint32_t XTP_ALGO_MKT_BJ_A = 3;
		///港股    
		constexpr uint32_t XTP_ALGO_MKT_HK = 4;     
		///港股通上海
		constexpr uint32_t XTP_ALGO_MKT_SH_HK = 5;     
		///港股通深圳
		constexpr uint32_t XTP_ALGO_MKT_SZ_HK = 6;     
		///未知交易市场类型
		constexpr uint32_t XTP_ALGO_MKT_UNKNOWN = 7;     


		/////////////////////////////////////////////////////////////////////////
		///@brief XTP_ALGO_SIDE_TYPE是买卖方向类型
		/////////////////////////////////////////////////////////////////////////
		typedef uint8_t XTP_ALGO_SIDE_TYPE;

		///买（新股申购，ETF买，配股，信用交易中担保品买）
		constexpr uint32_t XTP_ALGO_SIDE_BUY = 1;
		///卖（逆回购，ETF卖，信用交易中担保品卖）
		constexpr uint32_t XTP_ALGO_SIDE_SELL = 2;
		///申购
		constexpr uint32_t XTP_ALGO_SIDE_PURCHASE = 7;
		///赎回
		constexpr uint32_t XTP_ALGO_SIDE_REDEMPTION = 8;
		///拆分
		constexpr uint32_t XTP_ALGO_SIDE_SPLIT = 9;
		///合并
		constexpr uint32_t XTP_ALGO_SIDE_MERGE = 10;
		///改版之后的side的备兑，暂不支持
		constexpr uint32_t XTP_ALGO_SIDE_COVER = 11;
		///改版之后的side锁定（对应开平标识为开）/解锁（对应开平标识为平）
		constexpr uint32_t XTP_ALGO_SIDE_FREEZE = 12;
		/// 融资买入
		constexpr uint32_t XTP_ALGO_SIDE_MARGIN_TRADE = 21;
		/// 融券卖出
		constexpr uint32_t XTP_ALGO_SIDE_SHORT_SELL = 22;
		/// 卖券还款
		constexpr uint32_t XTP_ALGO_SIDE_REPAY_MARGIN = 23;
		/// 买券还券
		constexpr uint32_t XTP_ALGO_SIDE_REPAY_STOCK = 24;
		/// 现金还款（不放在普通订单协议，另加请求和查询协议）
//		constexpr uint32_t XTP_SIDE_CASH_REPAY_MARGIN = 25;
		/// 现券还券
		constexpr uint32_t XTP_ALGO_SIDE_STOCK_REPAY_STOCK = 26;
		/// 余券划转
		constexpr uint32_t XTP_ALGO_SIDE_SURSTK_TRANS = 27;
		/// 担保品转入
		constexpr uint32_t XTP_ALGO_SIDE_GRTSTK_TRANSIN = 28;
		/// 担保品转出
		constexpr uint32_t XTP_ALGO_SIDE_GRTSTK_TRANSOUT = 29;

		///组合策略的组合
		constexpr uint32_t XTP_ALGO_SIDE_OPT_COMBINE = 31; 
		///组合策略的拆分
		constexpr uint32_t XTP_ALGO_SIDE_OPT_SPLIT = 32; 
		///组合策略的管理员强制拆分
		constexpr uint32_t XTP_ALGO_SIDE_OPT_SPLIT_FORCE = 33; 
		///组合策略的交易所强制拆分
		constexpr uint32_t XTP_ALGO_SIDE_OPT_SPLIT_FORCE_EXCH = 34;

		///未知或者无效买卖方向
		constexpr uint32_t XTP_ALGO_SIDE_UNKNOWN = 50;

		//////////////////////////////////////////////////////////////////////////
		///@brief XTPAlgoTerminalType是一种终端类型，仅供授权系统使用
		//////////////////////////////////////////////////////////////////////////
		typedef uint32_t XTPAlgoTerminalType;

		///"PC",PC-windows及MacOS
		constexpr uint32_t  XTP_ALGO_TERMINAL_PC = 1; 
		///"MA",Mobile-Android           
		constexpr uint32_t   XTP_ALGO_TERMINAL_ANDROID = 2;          
		///"MI",Mobile-Ios
		constexpr uint32_t   XTP_ALGO_TERMINAL_IOS = 3;      
		///"MW",Mobile-Windows Phone
		constexpr uint32_t   XTP_ALGO_TERMINAL_WP = 4;      
		///"WP",无盘站
		constexpr uint32_t   XTP_ALGO_TERMINAL_STATION = 5;       
		///"TO",电话委托
		constexpr uint32_t   XTP_ALGO_TERMINAL_TEL = 6;       
		///"OH",PC-linux及其他终端
		constexpr uint32_t   XTP_ALGO_TERMINAL_PC_LINUX = 7;

		//////////////////////////////////////////////////////////////////////////
		///@brief 错误消息的响应信息
		//////////////////////////////////////////////////////////////////////////
		typedef struct XTPAlgoRspInfoStruct
		{
			///错误代码
			int32_t	error_id;
			///错误信息
			char	error_msg[XTP_ALGO_ERR_MSG_LEN];
		} XTPARI;

	}//API
}//XTPX

#endif //_XTP_ALGO_DATA_TYPE_H_
