//说明部分

//API
#include "xtp_algox_api.h"

//系统
//#ifdef WIN32
//#include "stdafx.h"
//#endif
#include <string>
#include <queue>

//Boost
#define BOOST_PYTHON_STATIC_LIB
#include <boost/python/module.hpp>	//python封装
#include <boost/python/def.hpp>		//python封装
#include <boost/python/dict.hpp>	//python封装
#include <boost/python/list.hpp>	//python封装
#include <boost/python/object.hpp>	//python封装
#include <boost/python.hpp>			//python封装
#include <boost/thread.hpp>			//任务队列的线程功能
#include <boost/bind.hpp>			//任务队列的线程功能


//命名空间
using namespace std;
using namespace boost::python;
using namespace boost;


//常量
#define ONDISCONNECTED 1
#define ONERROR 2
#define ONORDEREVENT 3
#define ONTRADEEVENT 4
#define ONCANCELORDERERROR 5
#define ONQUERYORDER 6
#define ONQUERYTRADE 7
#define ONQUERYPOSITION 8
#define ONQUERYASSET 9
#define ONQUERYFUNDTRANSFER 11
#define ONFUNDTRANSFER 12
#define ONQUERYETF 13
#define ONQUERYETFBASKET 14
#define ONQUERYIPOINFOLIST 15
#define ONQUERYIPOQUOTAINFO 16

#define ONQUERYOPTIONAUCTIONINFO 17

#define ONCREDITCASHREPAY 18
#define ONQUERYCREDITCASHREPAYINFO 19
#define ONQUERYCREDITFUNDINFO 20
#define ONQUERYCREDITDEBTINFO 21
#define ONQUERYCREDITTICKERDEBTINFO 22
#define ONQUERYCREDITASSETDEBTINFO 23
#define ONQUERYCREDITTICKERASSIGNINFO 24
#define ONQUERYCREDITEXCESSSTOCK 25

#define ONCREDITEXTENDDEBTDATE 26
#define ONQUERYCREDITEXTENDDEBTDATEORDERS 27
#define ONQUERYCREDITFUNDEXTRAINFO 28
#define ONQUERYCREDITPOSITIONEXTRAINFO 29

#define ONQUERYORDERBYPAGE 30
#define ONQUERYTRADEBYPAGE 31
#define ONCREDITCASHREPAYDEBTINTERESTFEE 32
#define ONQUERYMULCREDITEXCESSSTOCK 33

#define ONOPTIONCOMBINEDORDEREVENT 34
#define ONOPTIONCOMBINEDTRADEEVENT 35
#define ONQUERYOPTIONCOMBINEDORDERS 36
#define ONQUERYOPTIONCOMBINEDORDERSBYPAGE 37
#define ONQUERYOPTIONCOMBINEDTRADES 38
#define ONQUERYOPTIONCOMBINEDTRADESBYPAGE 39
#define ONQUERYOPTIONCOMBINEDPOSITION 40
#define ONQUERYOPTIONCOMBINEDSTRATEGYINFO 41
#define ONCANCELOPTIONCOMBINEDORDERERROR 42

#define ONQUERYOPTIONCOMBINEDEXECPOSITION 43
#define ONQUERYOTHERSERVERFUND 44


#define ONQUERYSTRATEGY 45
#define ONSTRATEGYASTATEREPORT 46
#define ONALGOUSERESTABLISHCHANNEL 47
#define ONINSERTALGOORDER 48
#define ONCANCELALGOORDER 49
#define ONALGODISCONNECTED 50
#define ONALGOCONNECTED 51
#define ONQUERYOPTIONCOMBINEDORDERSEX 54
#define ONQUERYOPTIONCOMBINEDORDERSBYPAGEEX 55
#define ONSTRATEGYSYMBOLSTATEREPORT 56

#define ONQUERYBONDIPOINFOLIST	58
#define ONQUERYBONDSWAPSTOCKINFO 59
#define ONNEWSTRATEGYCREATEREPORT 60
#define ONSTRATEGYRECOMMENDATION 61
#define ONMODIFYALGOORDER 62
#define ONSERVERSTATUSNOTIFICATION  63
#define ONCONNECT  64
#define ONRESUMEEND  65
#define ONUNKNOWNORDER  66
#define ONORDERACK  67
#define ONQUERYSECURITYACCOUNT  68
#define ONQUERYFUNDTRANSFERBYPAGE  69
#define ONUNKNOWNFUNDTRANSFER  70
///-------------------------------------------------------------------------------------
///API中的部分组件
///-------------------------------------------------------------------------------------

//GIL全局锁简化获取用，
//用于帮助C++线程获得GIL锁，从而防止python崩溃
class PyLock
{
private:
	PyGILState_STATE gil_state;

public:
	//在某个函数方法中创建该对象时，获得GIL锁
	PyLock()
	{
		gil_state = PyGILState_Ensure();
	}

	//在某个函数完成后销毁该对象时，解放GIL锁
	~PyLock()
	{
		PyGILState_Release(gil_state);
	}
};


//任务结构体
struct Task
{
	int task_name;		//回调函数名称对应的常量
	void *task_data;	//数据结构体
	void *task_error;	//错误结构体
	void *task_error_extra;//额外错误结构体
	int task_id;		//请求id
	bool task_last;		//是否为最后返回
	bool addtional_bool;		//补充bool字段
	int64_t addtional_int;		//补充账户字段
	double remain_amount;//补充double字段
	int64_t addtional_int_two;		//补充整数字段
	int64_t addtional_int_three;		//补充整数字段
	int64_t addtional_int_four;		//补充整数字段
	uint64_t addtional_int_five;		//补充整数字段

	int64_t req_count;
	int64_t order_sequence; 
	int64_t query_reference;
	int64_t trade_sequence;

	string strategy_param;
	string user;
	int reason;
};


///线程安全的队列
template<typename Data>

class ConcurrentQueue
{
private:
	queue<Data> the_queue;								//标准库队列
	mutable boost::mutex the_mutex;						//boost互斥锁				
	boost::condition_variable the_condition_variable;	//boost条件变量

public:

	//存入新的任务
	void push(Data const& data)
	{
		boost::mutex::scoped_lock lock(the_mutex);		//获取互斥锁
		the_queue.push(data);							//向队列中存入数据
		lock.unlock();									//释放锁
		the_condition_variable.notify_one();			//通知正在阻塞等待的线程
	}

	//检查队列是否为空
	bool empty() const
	{
		boost::mutex::scoped_lock lock(the_mutex);
		return the_queue.empty();
	}

	//取出
	Data wait_and_pop()
	{
		boost::mutex::scoped_lock lock(the_mutex);

		while (the_queue.empty())						//当队列为空时
		{
			the_condition_variable.wait(lock);			//等待条件变量通知
		}

		Data popped_value = the_queue.front();			//获取队列中的最后一个任务
		the_queue.pop();								//删除该任务
		return popped_value;							//返回该任务
	}

};


void getNestedDictValue(dict d, string key1, string key2, int *value);

void getNestedDictChar(dict d, string key1, string key2, char *value);

void getNestedDictChar2(dict d, string key1, string key2, string key3, char *value, int index);

void getNestedDictValue2(dict d, string key1, string key2, string key3, int *value, int index);

//从字典中获取某个建值对应的整数，并赋值到请求结构体对象的值上
void getInt(dict d, string key, int *value);

void getUint64(dict d, string key, uint64_t *value);

void getUint32(dict d, string key, uint32_t *value);

void getInt64(dict d, string key, int64_t *value);



//从字典中获取某个建值对应的浮点数，并赋值到请求结构体对象的值上
void getDouble(dict d, string key, double* value);


//从字典中获取某个建值对应的字符，并赋值到请求结构体对象的值上
void getChar(dict d, string key, char* value);


//从字典中获取某个建值对应的字符串，并赋值到请求结构体对象的值上
void getStr(dict d, string key, char* value);


///-------------------------------------------------------------------------------------
///C++ SPI的回调函数方法实现
///-------------------------------------------------------------------------------------

//API的继承实现
class AlgoXApi : public XTPX::API::AlgoXSpi
{
private:
	XTPX::API::AlgoXApi* api;			//API对象
	boost::thread *task_thread;			//工作线程指针（向python中推送数据）
	ConcurrentQueue<Task*> task_queue;	//任务队列

public:
	AlgoXApi()
	{
		function0<void> f = boost::bind(&AlgoXApi::processTask, this);
		boost::thread t(f);
		this->task_thread = &t;
	};

	~AlgoXApi()
	{
	};

	//-------------------------------------------------------------------------------------
	//ALGOX API回调函数
	//-------------------------------------------------------------------------------------

	///algo业务中报送策略单的响应
	///@param strategy_info 用户报送的策略单的具体信息
	///@param error_info 报送策略单发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
	///@param user_name 资金账户
	///@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
	virtual void OnInsertAlgoOrder(XTPX::API::XTPStrategyInfoStruct* strategy_info, XTPX::API::XTPARI *error_info, char* user_name);

	///algo业务中撤销策略单的响应
	///@param strategy_info 用户撤销的策略单的具体信息
	///@param error_info 撤销策略单发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
	///@param user_name 资金账户
	///@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
	virtual void OnCancelAlgoOrder(XTPX::API::XTPStrategyInfoStruct* strategy_info, XTPX::API::XTPARI *error_info, char* user_name);

	///algo业务中查询策略列表的响应
	///@param strategy_info 策略具体信息
	///@param strategy_param 此策略中包含的参数，如果error_info.error_id为0时，有意义
	///@param error_info 查询查询策略列表发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
	///@param request_id 此消息响应函数对应的请求ID
	///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
	///@param user_name 资金账户
	///@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
	virtual void OnQueryStrategy(XTPX::API::XTPStrategyInfoStruct* strategy_info, char* strategy_param, XTPX::API::XTPARI *error_info, int32_t request_id, bool is_last, char* user_name);

	///algo业务中报送母单创建时的推送消息(包括其他客户端创建的母单)
	///@param strategy_info 策略具体信息
	///@param strategy_param 此策略中包含的参数
	///@param user_name 资金账户
	///@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
	virtual void OnNewStrategyCreateReport(XTPX::API::XTPStrategyInfoStruct* strategy_info, char* strategy_param, char* user_name);

	///algo业务中策略运行时策略状态通知
	///@param strategy_state 用户策略运行情况的状态通知
	///@param user_name 资金账户
	///@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
	virtual void OnStrategyStateReport(XTPX::API::XTPStrategyStateReport* strategy_state, char* user_name);

	///algo业务中用户建立算法通道的消息响应
	///@param user 用户名
	///@param error_info 建立算法通道发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误，即算法通道成功
	///@param user_name 资金账户
	///@remark 算法通道建立成功后，才能对用户创建策略等操作，一个用户只能拥有一个算法通道，如果之前已经建立，则无需重复建立
	virtual void OnALGOUserEstablishChannel(char* user_name, XTPX::API::XTPARI* error_info);

	///当客户端与AlgoBus通信连接断开时，该方法被调用。
	///@param reason 错误原因，请与错误代码表对应
	///@remark 请不要堵塞此线程，否则会影响algo的登录
	virtual void OnAlgoDisconnected(int reason);

	///当客户端与AlgoBus断线连接时，该方法被调用，仅在断线重连成功后会被调用。
	virtual void OnAlgoConnected();

	///algo业务中策略运行时策略指定证券执行状态通知
	///@param strategy_symbol_state 用户策略指定证券运行情况的状态通知
	///@param user_name 资金账户
	///@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
	virtual void OnStrategySymbolStateReport(XTPX::API::XTPStrategySymbolStateReport* strategy_symbol_state, char* user_name);

	///algo业务中算法推荐的响应
	///@param basket_flag 是否将满足条件的推荐结果打包成母单篮的标志，与请求一致，如果此参数为true，那么请以返回的strategy_param为准
	///@param recommendation_info 推荐算法的具体信息，当basket_flag=true时，此结构体中的market和ticker将没有意义，此时请以strategy_param为准
	///@param strategy_param 算法参数，可直接用来创建母单，如果error_info.error_id为0时，有意义
	///@param error_info 请求推荐算法发生错误时返回的错误信息，当error_info为空，或者error_info.error_id为0时，表明没有错误
	///@param request_id 此消息响应函数对应的请求ID
	///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
	///@param user_name 资金账户
	///@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
	virtual void OnStrategyRecommendation(bool basket_flag, XTPX::API::XTPStrategyRecommendationInfo* recommendation_info, char* strategy_param, XTPX::API::XTPARI *error_info, int32_t request_id, bool is_last, char* user_name);

	

	//-------------------------------------------------------------------------------------
	//task：任务
	//-------------------------------------------------------------------------------------

	void processTask();

	

	

	//////////algo/////////
	void processQueryStrategy(Task *task);

	void processStrategyStateReport(Task *task);

	void processALGOUserEstablishChannel(Task *task);

	void processInsertAlgoOrder(Task *task);

	void processCancelAlgoOrder(Task *task);

	void processAlgoDisconnected(Task *task);

	void processAlgoConnected(Task *task);

	void processStrategySymbolStateReport(Task *task);
	
	void processNewStrategyCreateReport(Task *task);
	
	void processStrategyRecommendation(Task *task);   
	
	
	//-------------------------------------------------------------------------------------
	//data：回调函数的数据字典
	//error：回调函数的错误字典
	//reqid：请求id
	//last：是否为最后返回
	//-------------------------------------------------------------------------------------



	//////////////algo////////

	virtual void onQueryStrategy(dict data, string strategy_param, dict error_info, int32_t request_id, bool is_last, string user_name){};
	
	virtual void onStrategyStateReport(dict data,  string user_name){};

	virtual void onALGOUserEstablishChannel(string user,dict error_info){};

	virtual void onInsertAlgoOrder(dict data,dict error_info, string user_name){};

	virtual void onCancelAlgoOrder(dict data,dict error_info, string user_name){};

	virtual void onAlgoDisconnected(int reason){};

	virtual void onAlgoConnected(){};

	virtual void onStrategySymbolStateReport(dict data, string user_name) {};
	
	virtual void onNewStrategyCreateReport(dict data, string strategy_param, string user_name) {};
	
	virtual void onStrategyRecommendation(bool basket_flag, dict data, string strategy_param, dict error_info, int32_t request_id, bool is_last, string user_name) {};
	
	
	//-------------------------------------------------------------------------------------
	//req:主动函数的请求字典
	//-------------------------------------------------------------------------------------
	/////////////////////algo///////////////////////
	void createAlgoXApi(uint8_t clientid, string path, int log_level);

	//void release();

	//int exit();

	dict getApiLastError();

	string getApiVersion();

	void setSoftwareVersion(string version);

	void setHeartBeatInterval(uint32_t interval);

	int loginALGO(string ip, int port, string user, string password, int socktype);

	int insertAlgoOrder(uint32_t strategy_type, uint64_t client_strategy_id, string strategy_param, string user_name);

	int cancelAlgoOrder(bool cancel_flag, uint64_t xtp_strategy_id, string user_name);

	int queryStrategy(uint32_t strategy_type, uint64_t client_strategy_id, uint64_t xtp_strategy_id, string user_name, int32_t request_id);

	int aLGOUserEstablishChannel(string user_name, string password);

	int strategyRecommendation(bool basket_flag, string basket_param, string user_name, int32_t request_id);

};
