/////////////////////////////////////////////////////////////////////////
///@author 中泰证券股份有限公司
///@file algo_x_api_struct.h
///@brief 定义业务公共数据结构
/////////////////////////////////////////////////////////////////////////
#ifndef _XTP_ALGOX_API_STRUCT_H_
#define _XTP_ALGOX_API_STRUCT_H_

#include "algox_data_type.h"

#pragma pack(push)
#pragma pack(1)

namespace XTPX {

	namespace API {

		///策略信息结构体
		typedef struct XTPStrategyInfoStruct
		{
			uint64_t				m_client_strategy_id;	///< 客户策略id
			uint64_t				m_xtp_strategy_id;		///< xtp策略id
			uint16_t				m_strategy_type;		///< 策略类型
			XTPStrategyStateType	m_strategy_state;		///< 策略状态
			char					unused[5];				///< 预留字段
		} XTPStrategyInfoStruct;

		///策略状态结构体
		typedef struct XTPStrategyStateReportStruct
		{
			XTPStrategyInfoStruct		m_strategy_info;			///< 策略信息	
			int64_t						m_strategy_qty;				///< 策略总量
			int64_t						m_strategy_ordered_qty;		///< 策略已委托数量
			int64_t						m_strategy_cancelled_qty;	///< 策略已撤单数量
			int64_t						m_strategy_execution_qty;	///< 策略已成交数量
			int64_t						m_strategy_unclosed_qty;	///< 策略未平仓数量(T0卖出数量-买入数量)
			double						m_strategy_asset;			///< 策略总金额
			double						m_strategy_ordered_asset;	///< 策略已委托金额
			double						m_strategy_execution_asset;	///< 策略已成交金额
			double						m_strategy_execution_price;	///< 策略执行价格
			double						m_strategy_market_price;	///< 策略市场价
			double						m_strategy_price_diff;		///< 策略执行价差	
			double						m_strategy_asset_diff;		///< 策略执行绩效(T0资金预净收入)
			XTPARI						m_error_info;				///< 错误信息
		} XTPStrategyStateReport;

		///策略中指定证券的算法执行状态结构体
		typedef struct XTPStrategySymbolStateReportStruct
		{
			XTPStrategyInfoStruct		m_strategy_info;			///< 策略信息
			char						m_ticker[XTP_ALGO_TICKER_LEN];	///< 证券代码
			XTP_ALGO_MARKET_TYPE		m_market;					///< 市场
			XTP_ALGO_SIDE_TYPE			m_side;						///< 买卖方向，=0时为T0单
			char						unused[3];					///< 预留字段
			int64_t						m_strategy_qty;				///< 策略总量
			int64_t						m_strategy_ordered_qty;		///< 策略已委托数量
			int64_t						m_strategy_cancelled_qty;	///< 策略已撤单数量
			int64_t						m_strategy_execution_qty;	///< 策略已成交数量
			int64_t						m_strategy_buy_qty;			///< 策略已买入数量(T0)
			int64_t						m_strategy_sell_qty;		///< 策略已卖出数量(T0)
			int64_t						m_strategy_unclosed_qty;	///< 策略未平仓数量(T0卖出数量-买入数量)
			double						m_strategy_asset;			///< 策略总金额
			double						m_strategy_ordered_asset;	///< 策略已委托金额
			double						m_strategy_execution_asset;	///< 策略已成交金额
			double						m_strategy_buy_asset;		///< 策略买入金额(T0)
			double						m_strategy_sell_asset;		///< 策略卖出金额(TO)
			double						m_strategy_unclosed_asset;	///< 策略未平仓金额(T0)
			double						m_strategy_asset_diff;		///< 策略毛收益增强金额(T0)
			double						m_strategy_execution_price;	///< 策略执行价格
			double						m_strategy_market_price;	///< 策略市场价
			double						m_strategy_price_diff;		///< 策略执行价差(T0时为毛增强收益率)	
			XTPARI						m_error_info;				///< 错误信息
		} XTPStrategySymbolStateReport;

		///推荐算法结构体
		typedef struct XTPStrategyRecommendationInfoStruct
		{
			char						m_ticker[XTP_ALGO_TICKER_LEN];	///< 证券代码
			XTP_ALGO_MARKET_TYPE		m_market;					///< 交易市场
			uint16_t					m_strategy_type;			///< 策略类型
			char						unused[66];				///< 保留域
		} XTPStrategyRecommendationInfo;

		//////////////////////////////////////////////////////////////////////////
		///申报用户的ip和mac等信息，仅授权系统使用
		//////////////////////////////////////////////////////////////////////////
		struct XTPUserTerminalInfoReqEx {
			XTPAlgoTerminalType term_type;							///<终端类型
			int32_t internet_port;									///<公网端口号
			char  local_ip[XTP_ALGO_INET_ADDRESS_STR_LEN];			///<本地IP地址
			char  mac_addr[XTP_ALGO_MAC_ADDRESS_LEN];				///<MAC地址
			char  hd[XTP_ALGO_HARDDISK_SN_LEN];						///<硬盘序列号
			char  internet_ip[XTP_ALGO_INET_ADDRESS_STR_LEN];		///<公网IP地址
			XTPAlgoVersionType  client_version;						///<客户端版本号
			char  macos_sno[XTP_ALGO_MACOS_SNO_LEN];				///<MacOS系统的序列号，仅为MacOS系统需要填写
			char  imei[XTP_ALGO_IMEI_LEN];							///<移动Android端标识符
			char  idfv[XTP_ALGO_IDFV_LEN];							///<移动ios端标识符
			char  guid[XTP_ALGO_GUID_LEN];							///<移动其他终端标识符
			char  regist_tel[XTP_ALGO_TEL_LEN];						///<注册手机号码
			char  used_tel[XTP_ALGO_TEL_LEN];						///<实际使用手机号码
			char  scd[XTP_ALGO_SCD_LEN];							///<软件开发代码
			char  unused[34];										///<预留
		};

	}//API
}//XTPX

#pragma pack(pop)

#endif //_XTP_ALGO_API_STRUCT_H_
