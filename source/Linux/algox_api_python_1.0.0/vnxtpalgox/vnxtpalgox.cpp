// vnctpmd.cpp : 定义 DLL 应用程序的导出函数。
//
//#include "stdafx.h"
#include "vnxtpalgox.h"


///-------------------------------------------------------------------------------------
///从Python对象到C++类型转换用的函数
///-------------------------------------------------------------------------------------

// 嵌套结构体-int类型处理
void getNestedDictValue(dict d, string key1, string key2, int *value) {
	if (d.has_key(key1)) {        //检查字典中是否存在该键值
		dict o1 = (dict)d[key1];    //获取该键值
		if (o1.has_key(key2)) {
			object o2 = o1[key2];    //获取该键值
			extract<int> x(o2);    //创建提取器
			if (x.check()) {        //如果可以提取
				*value = x();    //对目标整数指针赋值
			}
		}
	}
}

// 嵌套结构体-字符串类型处理
void getNestedDictChar(dict d, string key1, string key2, char *value) {
	if (d.has_key(key1)) {        //检查字典中是否存在该键值
		dict o1 = (dict)d[key1];    //获取该键值
		if (o1.has_key(key2)) {
			object o2 = o1[key2];    //获取该键值
			extract<string> x(o2);    //创建提取器
			if (x.check()) {        //如果可以提取
				string s = x();
				const char *buffer = s.c_str();
#ifdef WIN32
				strcpy_s(value, strlen(buffer) + 1, buffer);
#else
				strncpy(value, buffer, strlen(buffer) + 1);
#endif
			}
		}
	}
}

// 嵌套结构体数组-字符串类型处理
void getNestedDictChar2(dict d, string key1, string key2, string key3, char *value, int index) {
	if (d.has_key(key1)) {        //检查字典中是否存在该键值
		dict o1 = (dict)d[key1];    //获取该键值
		if (o1.has_key(key2)) {
			dict o2 = (dict)(((boost::python::list)o1[key2])[index]);    //获取该键值
			if (o2.has_key(key3)) {
				object o3 = o2[key3];    //获取该键值
				extract<string> x(o3);    //创建提取器
				if (x.check()) {        //如果可以提取
					string s = x();
					const char *buffer = s.c_str();
#ifdef WIN32
					strcpy_s(value, strlen(buffer) + 1, buffer);
#else
					strncpy(value, buffer, strlen(buffer) + 1);
#endif
				}
			}
		}
	}
}

// 嵌套结构体数组-int类型处理
void getNestedDictValue2(dict d, string key1, string key2, string key3, int *value, int index) 
{
	if (d.has_key(key1)) {        //检查字典中是否存在该键值
		dict o1 = (dict)d[key1];    //获取该键值
		if (o1.has_key(key2)) {
			dict o2 = (dict)(((boost::python::list)o1[key2])[index]);    //获取该键值
			if (o2.has_key(key3)) {
				object o3 = o2[key3];    //获取该键值
				extract<int> x(o3);    //创建提取器
				if (x.check()) {        //如果可以提取
					*value = x();    //对目标整数指针赋值
				}
			}
		}
	}
}

void getInt(dict d, string key, int *value)
{
	if (d.has_key(key))		//检查字典中是否存在该键值
	{
		object o = d[key];	//获取该键值
		extract<int> x(o);	//创建提取器
		if (x.check())		//如果可以提取
		{
			*value = x();	//对目标整数指针赋值
		}
	}
};

void getUint64(dict d, string key, uint64_t *value)
{
	if (d.has_key(key))		//检查字典中是否存在该键值
	{
		object o = d[key];	//获取该键值
		extract<uint64_t> x(o);	//创建提取器
		if (x.check())		//如果可以提取
		{
			*value = x();	//对目标整数指针赋值
		}
	}
};

void getUint32(dict d, string key, uint32_t *value)
{
	if (d.has_key(key))		//检查字典中是否存在该键值
	{
		object o = d[key];	//获取该键值
		extract<int> x(o);	//创建提取器
		if (x.check())		//如果可以提取
		{
			*value = x();	//对目标整数指针赋值
		}
	}
};

void getUint16(dict d, string key, uint16_t *value)
{
	if (d.has_key(key))		//检查字典中是否存在该键值
	{
		object o = d[key];	//获取该键值
		extract<int> x(o);	//创建提取器
		if (x.check())		//如果可以提取
		{
			*value = x();	//对目标整数指针赋值
		}
	}
};

void getInt64(dict d, string key, int64_t *value)
{
	if (d.has_key(key))		//检查字典中是否存在该键值
	{
		object o = d[key];	//获取该键值
		extract<int64_t> x(o);	//创建提取器
		if (x.check())		//如果可以提取
		{
			*value = x();	//对目标整数指针赋值
		}
	}
};

void getDouble(dict d, string key, double *value)
{
	if (d.has_key(key))
	{
		object o = d[key];
		extract<double> x(o);
		if (x.check())
		{
			*value = x();
		}
	}
};

void getStr(dict d, string key, char *value)
{
	if (d.has_key(key))
	{
		object o = d[key];
		extract<string> x(o);
		if (x.check())
		{
			string s = x();
			const char *buffer = s.c_str();
			//对字符串指针赋值必须使用strcpy_s, vs2013使用strcpy编译通不过
			//+1应该是因为C++字符串的结尾符号？不是特别确定，不加这个1会出错
#ifdef _MSC_VER //WIN32
			strcpy_s(value, strlen(buffer) + 1, buffer);
#elif __GNUC__
			strncpy(value, buffer, strlen(buffer) + 1);
#endif
		}
	}
};

void getChar(dict d, string key, string& value)
{
	if (d.has_key(key))
	{
		object o = d[key];
		extract<string> x(o);
		if (x.check())
		{
			string s = x();
			value = s;
			//char buffer[XTP_ACCOUNT_PASSWORD_LEN];
			//strcpy(buffer, s.c_str());
			//const char buffer[XTP_ACCOUNT_PASSWORD_LEN] = s.c_str();
			//*value = *buffer;
		}
	}
};

string addEndingChar(char *value){
	//printf("value:%s\n",value);
	string endStr = value;
	//printf("endStr:%s\n",endStr.c_str());
	return endStr;
}

///-------------------------------------------------------------------------------------
///C++的回调函数将数据保存到队列中
///-------------------------------------------------------------------------------------

void AlgoXApi::OnInsertAlgoOrder(XTPX::API::XTPStrategyInfoStruct* strategy_info, XTPX::API::XTPARI *error_info, char* user_name)
{
	Task* task = new Task();
	task->task_name = ONINSERTALGOORDER;

	if (strategy_info) {
		XTPX::API::XTPStrategyInfoStruct *task_data = new XTPX::API::XTPStrategyInfoStruct();
		*task_data = *strategy_info;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPX::API::XTPARI *task_error = new XTPX::API::XTPARI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	if (user_name)
		task->user = addEndingChar(user_name);
	this->task_queue.push(task);
}

void AlgoXApi::OnCancelAlgoOrder(XTPX::API::XTPStrategyInfoStruct* strategy_info, XTPX::API::XTPARI *error_info, char* user_name)
{
	Task* task = new Task();
	task->task_name = ONCANCELALGOORDER;

	if (strategy_info) {
		XTPX::API::XTPStrategyInfoStruct *task_data = new XTPX::API::XTPStrategyInfoStruct();
		*task_data = *strategy_info;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPX::API::XTPARI *task_error = new XTPX::API::XTPARI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	if (user_name)
		task->user = addEndingChar(user_name);
	this->task_queue.push(task);
}

void AlgoXApi::OnQueryStrategy(XTPX::API::XTPStrategyInfoStruct* strategy_info, char* strategy_param, XTPX::API::XTPARI *error_info, int32_t request_id, bool is_last, char* user_name)
{
	Task* task = new Task();
	task->task_name = ONQUERYSTRATEGY;
	if (strategy_info) {
		XTPX::API::XTPStrategyInfoStruct *task_data = new XTPX::API::XTPStrategyInfoStruct();
		*task_data = *strategy_info;
		task->task_data = task_data;
	}

	if (strategy_param)
		task->strategy_param = addEndingChar(strategy_param);
	if (error_info)
	{
		XTPX::API::XTPARI *task_error = new XTPX::API::XTPARI();
		*task_error = *error_info;
		task->task_error = task_error;
	}
	task->task_id = request_id;
	task->task_last = is_last;
	if (user_name)
		task->user = addEndingChar(user_name);
	this->task_queue.push(task);
}

void AlgoXApi::OnNewStrategyCreateReport(XTPX::API::XTPStrategyInfoStruct* strategy_info, char* strategy_param, char* user_name)
{
	Task* task = new Task();
	task->task_name = ONNEWSTRATEGYCREATEREPORT;

	if (strategy_info) {
		XTPX::API::XTPStrategyInfoStruct *task_data = new XTPX::API::XTPStrategyInfoStruct();
		*task_data = *strategy_info;
		task->task_data = task_data;
	}

	if (strategy_param)
	{
		task->strategy_param = addEndingChar(strategy_param);
	}

	if (user_name)
		task->user = addEndingChar(user_name);
	this->task_queue.push(task);
}

void AlgoXApi::OnStrategyStateReport(XTPX::API::XTPStrategyStateReport* strategy_state, char* user_name)
{
	Task* task = new Task();
	task->task_name = ONSTRATEGYASTATEREPORT;

	if (strategy_state) {
		XTPX::API::XTPStrategyStateReportStruct *task_data = new XTPX::API::XTPStrategyStateReportStruct();
		*task_data = *strategy_state;
		task->task_data = task_data;
	}

	if (user_name)
		task->user = addEndingChar(user_name);
	this->task_queue.push(task);
}

void AlgoXApi::OnALGOUserEstablishChannel(char* user_name, XTPX::API::XTPARI* error_info)
{
	Task* task = new Task();
	task->task_name = ONALGOUSERESTABLISHCHANNEL;

	if (user_name)
		task->user = addEndingChar(user_name);

	if (error_info)
	{
		XTPX::API::XTPARI *task_error = new XTPX::API::XTPARI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	this->task_queue.push(task);
}

void AlgoXApi::OnAlgoDisconnected(int reason) {
	Task* task = new Task();
	task->task_name = ONALGODISCONNECTED;


	task->reason = reason;
	this->task_queue.push(task);
}

void AlgoXApi::OnAlgoConnected() {
	Task* task = new Task();
	task->task_name = ONALGOCONNECTED;

	this->task_queue.push(task);
}

void AlgoXApi::OnStrategySymbolStateReport(XTPX::API::XTPStrategySymbolStateReport* strategy_symbol_state, char* user_name)
{
	Task* task = new Task();
	task->task_name = ONSTRATEGYSYMBOLSTATEREPORT;

	if (strategy_symbol_state)
	{
		XTPX::API::XTPStrategySymbolStateReport *task_data = new XTPX::API::XTPStrategySymbolStateReport();
		*task_data = *strategy_symbol_state;
		task->task_data = task_data;
	}
	if (user_name)
		task->user = addEndingChar(user_name);
	this->task_queue.push(task);
}

void AlgoXApi::OnStrategyRecommendation(bool basket_flag, XTPX::API::XTPStrategyRecommendationInfo* recommendation_info, char* strategy_param, XTPX::API::XTPARI *error_info, int32_t request_id, bool is_last, char* user_name)
{
	Task* task = new Task();
	task->task_name = ONSTRATEGYRECOMMENDATION;
	task->addtional_bool = basket_flag;

	if (recommendation_info) {
		XTPX::API::XTPStrategyRecommendationInfo *task_data = new XTPX::API::XTPStrategyRecommendationInfo();
		*task_data = *recommendation_info;
		task->task_data = task_data;
	}

	if (strategy_param)
	{
		task->strategy_param = addEndingChar(strategy_param);
	}

	if (error_info)
	{
		XTPX::API::XTPARI *task_error = new XTPX::API::XTPARI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->task_id = request_id;
	task->task_last = is_last;
	if(user_name)
		task->user = addEndingChar(user_name);
	this->task_queue.push(task);
}



////////////////////////algo////////////////////////
/*void TraderApi::OnQueryStrategy(XTPStrategyInfoStruct* strategy_info, char* strategy_param, XTPRI *error_info, int32_t request_id, bool is_last, uint64_t session_id) {
	Task* task = new Task();
	task->task_name = ONQUERYSTRATEGY;
	if (strategy_info) {
		XTPStrategyInfoStruct *task_data = new XTPStrategyInfoStruct();
		*task_data = *strategy_info;
		task->task_data = task_data;
	}
	
	if(strategy_param)
		task->strategy_param = addEndingChar(strategy_param);
	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}
	task->task_id = request_id;
	task->task_last = is_last;
	task->addtional_int = session_id;
	this->task_queue.push(task);
	
}

void TraderApi::OnStrategyStateReport(XTPStrategyStateReportStruct* strategy_state,uint64_t session_id) {
	Task* task = new Task();
	task->task_name = ONSTRATEGYASTATEREPORT;

	if (strategy_state) {
		XTPStrategyStateReportStruct *task_data = new XTPStrategyStateReportStruct();
		*task_data = *strategy_state;
		task->task_data = task_data;
	}

	task->addtional_int = session_id;
	this->task_queue.push(task);
}


void TraderApi::OnALGOUserEstablishChannel(char* user, XTPRI* error_info, uint64_t session_id) {
	Task* task = new Task();
	task->task_name = ONALGOUSERESTABLISHCHANNEL;

	task->user = addEndingChar(user);

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}


	task->addtional_int = session_id;
	this->task_queue.push(task);
}

void TraderApi::OnInsertAlgoOrder(XTPStrategyInfoStruct* strategy_info, XTPRI *error_info, uint64_t session_id) {
	Task* task = new Task();
	task->task_name = ONINSERTALGOORDER;

	if (strategy_info) {
		XTPStrategyInfoStruct *task_data = new XTPStrategyInfoStruct();
		*task_data = *strategy_info;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->addtional_int = session_id;
	this->task_queue.push(task);
}


void TraderApi::OnCancelAlgoOrder(XTPStrategyInfoStruct* strategy_info, XTPRI *error_info, uint64_t session_id) {
	Task* task = new Task();
	task->task_name = ONCANCELALGOORDER;

	if (strategy_info) {
		XTPStrategyInfoStruct *task_data = new XTPStrategyInfoStruct();
		*task_data = *strategy_info;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->addtional_int = session_id;
	this->task_queue.push(task);
}

void TraderApi::OnAlgoDisconnected(int reason){
	Task* task = new Task();
	task->task_name = ONALGODISCONNECTED;


	task->reason = reason;
	this->task_queue.push(task);
}



void TraderApi::OnStrategySymbolStateReport(XTPStrategySymbolStateReport* strategy_symbol_state, uint64_t session_id)
{
	Task* task = new Task();
	task->task_name = ONSTRATEGYSYMBOLSTATEREPORT;

	if (strategy_symbol_state)
	{
		XTPStrategySymbolStateReport *task_data = new XTPStrategySymbolStateReport();
		*task_data = *strategy_symbol_state;
		task->task_data = task_data;
	}

	task->addtional_int = session_id;
	this->task_queue.push(task);
}

void TraderApi::OnNewStrategyCreateReport(XTPStrategyInfoStruct* strategy_info, char* strategy_param, uint64_t session_id)
{
	Task* task = new Task();
	task->task_name = ONNEWSTRATEGYCREATEREPORT;

	if (strategy_info) {
		XTPStrategyInfoStruct *task_data = new XTPStrategyInfoStruct();
		*task_data = *strategy_info;
		task->task_data = task_data;
	}

	if(strategy_param)
	{
		task->strategy_param = addEndingChar(strategy_param);
	}

	task->addtional_int = session_id;
	this->task_queue.push(task);
}

void TraderApi::OnStrategyRecommendation(bool basket_flag, XTPStrategyRecommendationInfo* recommendation_info, char* strategy_param, XTPRI *error_info, int32_t request_id, bool is_last, uint64_t session_id)
{
	Task* task = new Task();
	task->task_name = ONSTRATEGYRECOMMENDATION;
	task->addtional_bool = basket_flag;

	if (recommendation_info) {
		XTPStrategyRecommendationInfo *task_data = new XTPStrategyRecommendationInfo();
		*task_data = *recommendation_info;
		task->task_data = task_data;
	}

	if (strategy_param)
	{
		task->strategy_param = addEndingChar(strategy_param);
	}

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->task_id = request_id;
	task->task_last = is_last;
	task->addtional_int = session_id;
	this->task_queue.push(task);
}

void TraderApi::OnModifyAlgoOrder(XTPStrategyInfoStruct* strategy_info, XTPRI *error_info, uint64_t session_id)
{
	Task* task = new Task();
	task->task_name = ONMODIFYALGOORDER;

	if (strategy_info) {
		XTPStrategyInfoStruct *task_data = new XTPStrategyInfoStruct();
		*task_data = *strategy_info;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->addtional_int = session_id;
	this->task_queue.push(task);
}*/

///-------------------------------------------------------------------------------------
///工作线程从队列中取出数据，转化为python对象后，进行推送
///-------------------------------------------------------------------------------------

void AlgoXApi::processTask()
{
	while (1)
	{
		Task* task = this->task_queue.wait_and_pop();

		switch (task->task_name)
		{

			case ONINSERTALGOORDER: 
			{
				this->processInsertAlgoOrder(task);
				break;
			}

			case ONCANCELALGOORDER: 
			{
				this->processCancelAlgoOrder(task);
				break;
			}

			case ONQUERYSTRATEGY: 
			{
				this->processQueryStrategy(task);
				break;
			}

			case ONNEWSTRATEGYCREATEREPORT:
			{
				this->processNewStrategyCreateReport(task);
				break;
			}

			case ONSTRATEGYASTATEREPORT: 
			{
				this->processStrategyStateReport(task);
				break;
			}

			case ONALGOUSERESTABLISHCHANNEL: 
			{
				this->processALGOUserEstablishChannel(task);
				break;
			}

			case ONALGODISCONNECTED: 
			{
				this->processAlgoDisconnected(task);
				break;
			}

			case ONALGOCONNECTED: 
			{
				this->processAlgoConnected(task);
				break;
			}

			case ONSTRATEGYSYMBOLSTATEREPORT:
			{
				this->processStrategySymbolStateReport(task);
				break;
			}

			case ONSTRATEGYRECOMMENDATION:
			{
				this->processStrategyRecommendation(task);
				break;
			}

			
		};
	}
};



//////////algo/////////
void AlgoXApi::processQueryStrategy(Task *task) {
	PyLock lock;
	dict data;
	if (task->task_data){
		XTPX::API::XTPStrategyInfoStruct *task_data = (XTPX::API::XTPStrategyInfoStruct*)task->task_data;
		data["m_strategy_type"] = task_data->m_strategy_type;
		data["m_strategy_state"] = (int)task_data->m_strategy_state;
		data["m_client_strategy_id"] = task_data->m_client_strategy_id;
		data["m_xtp_strategy_id"] = task_data->m_xtp_strategy_id;
		data["unused"] = addEndingChar(task_data->unused);

	}

	dict error;
	if (task->task_error)
	{
		XTPX::API::XTPARI *task_error = (XTPX::API::XTPARI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = addEndingChar(task_error->error_msg);
		delete task->task_error;
	}
	this->onQueryStrategy(data,task->strategy_param, error,task->task_id,task->task_last,task->user);
	delete task;
}


void AlgoXApi::processStrategyStateReport(Task *task) {
	PyLock lock;
	dict data;
	if (task->task_data){
		dict m_strategy_info;
		XTPX::API::XTPStrategyStateReportStruct *task_data = (XTPX::API::XTPStrategyStateReportStruct*)task->task_data;
		m_strategy_info["m_strategy_type"] = task_data->m_strategy_info.m_strategy_type;
		m_strategy_info["m_strategy_state"] = (int)task_data->m_strategy_info.m_strategy_state;
		m_strategy_info["m_client_strategy_id"] = task_data->m_strategy_info.m_client_strategy_id;
		m_strategy_info["m_xtp_strategy_id"] = task_data->m_strategy_info.m_xtp_strategy_id;
		m_strategy_info["unused"] = task_data->m_strategy_info.unused;
		data["m_strategy_info"] = m_strategy_info;

		data["m_strategy_qty"] = task_data->m_strategy_qty;
		data["m_strategy_ordered_qty"] = task_data->m_strategy_ordered_qty;
		data["m_strategy_cancelled_qty"] = task_data->m_strategy_cancelled_qty;
		data["m_strategy_execution_qty"] = task_data->m_strategy_execution_qty;
		data["m_strategy_unclosed_qty"] = task_data->m_strategy_unclosed_qty;
		data["m_strategy_asset"] = task_data->m_strategy_asset;
		data["m_strategy_ordered_asset"] = task_data->m_strategy_ordered_asset;
		data["m_strategy_execution_asset"] = task_data->m_strategy_execution_asset;
		data["m_strategy_execution_price"] = task_data->m_strategy_execution_price;
		data["m_strategy_market_price"] = task_data->m_strategy_market_price;
		data["m_strategy_price_diff"] = task_data->m_strategy_price_diff;
		data["m_strategy_asset_diff"] = task_data->m_strategy_asset_diff;

		dict m_error_info;
		m_error_info["error_id"] = task_data->m_error_info.error_id;
		m_error_info["error_msg"] = addEndingChar(task_data->m_error_info.error_msg);
		data["m_error_info"] = m_error_info;
	}


	this->onStrategyStateReport(data,task->user);
	delete task;
}

void AlgoXApi::processALGOUserEstablishChannel(Task *task) {
	PyLock lock;

	dict error;
	if (task->task_error)
	{
		XTPX::API::XTPARI *task_error = (XTPX::API::XTPARI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = addEndingChar(task_error->error_msg);
		delete task->task_error;
	}

	this->onALGOUserEstablishChannel(task->user, error);
	delete task;
}

void AlgoXApi::processInsertAlgoOrder(Task *task) {
	PyLock lock;
	dict data;
	if (task->task_data){
		XTPX::API::XTPStrategyInfoStruct *task_data = (XTPX::API::XTPStrategyInfoStruct*)task->task_data;
		data["m_strategy_type"] = task_data->m_strategy_type;
		data["m_strategy_state"] = (int)task_data->m_strategy_state;
		data["m_client_strategy_id"] = task_data->m_client_strategy_id;
		data["m_xtp_strategy_id"] = task_data->m_xtp_strategy_id;
		data["unused"] = addEndingChar(task_data->unused);

	}

	dict error;
	if (task->task_error)
	{
		XTPX::API::XTPARI *task_error = (XTPX::API::XTPARI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = addEndingChar(task_error->error_msg);
		delete task->task_error;
	}

	this->onInsertAlgoOrder(data, error,task->user);
	delete task;
}


void AlgoXApi::processCancelAlgoOrder(Task *task) {
	PyLock lock;
	dict data;
	if (task->task_data){
		XTPX::API::XTPStrategyInfoStruct *task_data = (XTPX::API::XTPStrategyInfoStruct*)task->task_data;
		data["m_strategy_type"] = task_data->m_strategy_type;
		data["m_strategy_state"] = (int)task_data->m_strategy_state;
		data["m_client_strategy_id"] = task_data->m_client_strategy_id;
		data["m_xtp_strategy_id"] = task_data->m_xtp_strategy_id;
		data["unused"] = addEndingChar(task_data->unused);

	}

	dict error;
	if (task->task_error)
	{
		XTPX::API::XTPARI *task_error = (XTPX::API::XTPARI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = addEndingChar(task_error->error_msg);
		delete task->task_error;
	}

	this->onCancelAlgoOrder(data, error,task->user);
	delete task;
}

void AlgoXApi::processAlgoDisconnected(Task *task) {
	PyLock lock;

	this->onAlgoDisconnected(task->reason);
	delete task;
}

void AlgoXApi::processAlgoConnected(Task *task) {
	PyLock lock;

	this->onAlgoConnected();
	delete task;
}

void AlgoXApi::processStrategySymbolStateReport(Task *task)
{
	PyLock lock;

	dict data;
	if (task->task_data)
	{
		dict m_strategy_info;
		XTPX::API::XTPStrategySymbolStateReport *task_data = (XTPX::API::XTPStrategySymbolStateReport*)task->task_data;
		m_strategy_info["m_strategy_type"] = task_data->m_strategy_info.m_strategy_type;
		m_strategy_info["m_strategy_state"] = (int)task_data->m_strategy_info.m_strategy_state;
		m_strategy_info["m_client_strategy_id"] = task_data->m_strategy_info.m_client_strategy_id;
		m_strategy_info["m_xtp_strategy_id"] = task_data->m_strategy_info.m_xtp_strategy_id;
		m_strategy_info["unused"] = addEndingChar(task_data->m_strategy_info.unused);
		data["m_strategy_info"] = m_strategy_info;
		data["m_ticker"] = addEndingChar(task_data->m_ticker);
		data["m_market"] = (int)task_data->m_market;
		data["m_side"] = (int)task_data->m_side;
		data["unused"] = addEndingChar(task_data->unused);
		data["m_strategy_qty"] = task_data->m_strategy_qty;
		data["m_strategy_ordered_qty"] = task_data->m_strategy_ordered_qty;
		data["m_strategy_cancelled_qty"] = task_data->m_strategy_cancelled_qty;
		data["m_strategy_execution_qty"] = task_data->m_strategy_execution_qty;
		data["m_strategy_buy_qty"] = task_data->m_strategy_buy_qty;
		data["m_strategy_sell_qty"] = task_data->m_strategy_sell_qty;
		data["m_strategy_unclosed_qty"] = task_data->m_strategy_unclosed_qty;
		data["m_strategy_asset"] = task_data->m_strategy_asset;
		data["m_strategy_ordered_asset"] = task_data->m_strategy_ordered_asset;
		data["m_strategy_execution_asset"] = task_data->m_strategy_execution_asset;
		data["m_strategy_buy_asset"] = task_data->m_strategy_buy_asset;
		data["m_strategy_sell_asset"] = task_data->m_strategy_sell_asset;
		data["m_strategy_unclosed_asset"] = task_data->m_strategy_unclosed_asset;
		data["m_strategy_asset_diff"] = task_data->m_strategy_asset_diff;
		data["m_strategy_execution_price"] = task_data->m_strategy_execution_price;
		data["m_strategy_market_price"] = task_data->m_strategy_market_price;
		data["m_strategy_price_diff"] = task_data->m_strategy_price_diff;
		dict m_error_info;
		m_error_info["error_id"] = task_data->m_error_info.error_id;
		m_error_info["error_msg"] = addEndingChar(task_data->m_error_info.error_msg);
		data["m_error_info"] = m_error_info;

		delete task->task_data;
	}
	this->onStrategySymbolStateReport(data, task->user);
	delete task;
}

void AlgoXApi::processNewStrategyCreateReport(Task *task)
{
	PyLock lock;

	dict data;
	if (task->task_data)
	{
		XTPX::API::XTPStrategyInfoStruct *task_data = (XTPX::API::XTPStrategyInfoStruct*)task->task_data;
		data["m_strategy_type"] = task_data->m_strategy_type;
		data["m_strategy_state"] = (int)task_data->m_strategy_state;
		data["m_client_strategy_id"] = task_data->m_client_strategy_id;
		data["m_xtp_strategy_id"] = task_data->m_xtp_strategy_id;
		data["unused"] = addEndingChar(task_data->unused);
	}

	this->onNewStrategyCreateReport(data, task->strategy_param, task->user);
	delete task;
}

void AlgoXApi::processStrategyRecommendation(Task *task)
{
	PyLock lock;

	dict data;
	if (task->task_data)
	{
		XTPX::API::XTPStrategyRecommendationInfo *task_data = (XTPX::API::XTPStrategyRecommendationInfo*)task->task_data;
		data["m_strategy_type"] = task_data->m_strategy_type;
		data["m_market"] = (int)task_data->m_market;
		data["m_ticker"] = addEndingChar(task_data->m_ticker);
		data["unused"] = addEndingChar(task_data->unused);
	}

	dict error;
	if (task->task_error)
	{
		XTPX::API::XTPARI *task_error = (XTPX::API::XTPARI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = addEndingChar(task_error->error_msg);
		delete task->task_error;
	}

	this->onStrategyRecommendation(task->addtional_bool, data, task->strategy_param, error, task->task_id,task->task_last, task->user);
	delete task;
}


///-------------------------------------------------------------------------------------
///主动函数
///-------------------------------------------------------------------------------------

void AlgoXApi::createAlgoXApi(uint8_t clientid, string path, int log_level)
{
	this->api = XTPX::API::AlgoXApi::CreateAlgoXApi(clientid, path.c_str(),(XTPX::API::XTP_ALGO_LOG_LEVEL)log_level);
	this->api->RegisterSpi(this);
};



dict AlgoXApi::getApiLastError()
{
	dict d;
	XTPX::API::XTPARI *error = this->api->GetApiLastError();
	if(error == NULL)
		return d;

	d["error_id"] = error->error_id;
	d["error_msg"] = addEndingChar(error->error_msg);

	return d;
}

string AlgoXApi::getApiVersion()
{
	string ret ="";
	const char* p = this->api->GetApiVersion();
	if (p == NULL)
		ret = "NULL";
	else
		ret = p;
	return ret;
}



void AlgoXApi::setSoftwareVersion(string version)
{
	this->api->SetSoftwareVersion(version.c_str());
}

void AlgoXApi::setHeartBeatInterval(uint32_t interval)
{
	this->api->SetHeartBeatInterval(interval);
};

int AlgoXApi::loginALGO(string ip, int port, string user, string password, int socktype)
{
	return this->api->LoginALGO(ip.c_str(), port, user.c_str(), password.c_str(), (XTPX::API::XTP_ALGO_PROTOCOL_TYPE)socktype);
};

int AlgoXApi::insertAlgoOrder(uint32_t strategy_type, uint64_t client_strategy_id, string strategy_param, string user_name)
{
	return this->api->InsertAlgoOrder(strategy_type, client_strategy_id, (char*)strategy_param.c_str(), user_name.c_str());
}

int AlgoXApi::cancelAlgoOrder(bool cancel_flag, uint64_t xtp_strategy_id, string user_name)
{
	return this->api->CancelAlgoOrder(cancel_flag, xtp_strategy_id, user_name.c_str());
}

int AlgoXApi::queryStrategy(uint32_t strategy_type, uint64_t client_strategy_id, uint64_t xtp_strategy_id, string user_name, int32_t request_id)
{
	return this->api->QueryStrategy(strategy_type, client_strategy_id, xtp_strategy_id, user_name.c_str(), request_id);
}

int AlgoXApi::aLGOUserEstablishChannel(string user_name, string password)
{
	return this->api->ALGOUserEstablishChannel(user_name.c_str(), password.c_str());
}

int AlgoXApi::strategyRecommendation(bool basket_flag, string basket_param, string user_name, int32_t request_id)
{
	return this->api->StrategyRecommendation(basket_flag, (char*)basket_param.c_str(), user_name.c_str(), request_id);
}




///-------------------------------------------------------------------------------------
///Boost.Python封装
///-------------------------------------------------------------------------------------

struct AlgoXApiWrap : AlgoXApi, wrapper < AlgoXApi >
{
	virtual void onDisconnected(uint64_t session, int reason)
	{
		try
		{
			this->get_override("onDisconnected")(session, reason);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onServerStatusNotification(uint64_t session, uint32_t server_type, bool status)
	{
		try
		{
			this->get_override("onServerStatusNotification")(session, server_type, status);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onError(dict data)
	{
		try
		{
			this->get_override("onError")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onConnect(uint64_t session, string user)
	{
		try
		{
			this->get_override("onConnect")(session, user);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onResumeEnd(uint64_t session)
	{
		try
		{
			this->get_override("onResumeEnd")(session);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onUnknownOrder(uint64_t order_xtp_id, uint64_t session)
	{
		try
		{
			this->get_override("onUnknownOrder")(order_xtp_id, session);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onOrderAck(dict data, uint64_t session)
	{
		try
		{
			this->get_override("onOrderAck")(data, session);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};


	virtual void onOrderEvent(dict data, dict error, uint64_t session)
	{
		try
		{
			this->get_override("onOrderEvent")(data, error, session);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onTradeEvent(dict data, uint64_t session)
	{
		try
		{
			this->get_override("onTradeEvent")(data, session);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onCancelOrderError(dict data, dict error, uint64_t session)
	{
		try
		{
			this->get_override("onCancelOrderError")(data, error, session);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onQueryOrder(dict data, dict error, int id, bool last, uint64_t session)
	{
		try
		{
			this->get_override("onQueryOrder")(data, error, id, last, session);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onQueryOrderByPage(dict data, int64_t req_count, int64_t order_sequence, int64_t query_reference, int reqid, bool last, uint64_t session)
	{
		try
		{
			this->get_override("onQueryOrderByPage")(data,req_count,order_sequence, query_reference, reqid, last, session);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};


	virtual void onQueryTrade(dict data, dict error, int id, bool last, uint64_t session)
	{
		try
		{
			this->get_override("onQueryTrade")(data, error, id, last, session);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onQueryTradeByPage(dict data, int64_t req_count, int64_t trade_sequence, int64_t query_reference, int reqid, bool last, uint64_t session)
	{
		try
		{
			this->get_override("onQueryTradeByPage")(data, req_count,trade_sequence,query_reference, reqid, last, session);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onQueryPosition(dict data, dict error, int id, bool last, uint64_t session)
	{
		try
		{
			this->get_override("onQueryPosition")(data, error, id, last, session);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onQuerySecurityAccount(dict data, dict error, int reqid, bool last, uint64_t session)
	{
		try
		{
			this->get_override("onQuerySecurityAccount")(data, error, reqid, last, session);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onQueryAsset(dict data, dict error, int id, bool last, uint64_t session)
	{
		try
		{
			this->get_override("onQueryAsset")(data, error, id, last, session);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};


	virtual void onQueryFundTransfer(dict data, dict fund_transfer_err_info, dict error, int reqid, bool last, uint64_t session)
	{
		try
		{
			this->get_override("onQueryFundTransfer")(data, fund_transfer_err_info, error, reqid, last, session);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onQueryFundTransferByPage(dict data, dict fund_transfer_err_info, dict error, int64_t req_count, int64_t sequence, int64_t query_reference, int reqid, bool last, uint64_t session)
	{
		try
		{
			this->get_override("onQueryFundTransferByPage")(data, fund_transfer_err_info, error, req_count, sequence, query_reference, reqid, last, session);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onFundTransfer(dict data, dict error, uint64_t session)
	{
		try
		{
			this->get_override("onFundTransfer")(data, error, session);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onQueryOtherServerFund(dict data, dict error_info, int request_id, uint64_t session) {
		PyLock lock;
		printf("onQueryOtherServerFund--");
		try {
			this->get_override("onQueryOtherServerFund")(data, error_info, request_id, session);
		}
		catch (error_already_set const &) {
			PyErr_Print();
		}
	};

	virtual void onUnknownFundTransfer(uint64_t serial_id, uint64_t session)
	{
		try
		{
			this->get_override("onUnknownFundTransfer")(serial_id, session);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onQueryETF(dict data, dict error, int id, bool last, uint64_t session)
	{
		try
		{
			this->get_override("onQueryETF")(data, error, id, last, session);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onQueryETFBasket(dict data, dict error, int id, bool last, uint64_t session)
	{
		try
		{
			this->get_override("onQueryETFBasket")(data, error, id, last, session);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onQueryIPOInfoList(dict data, dict error, int id, bool last, uint64_t session)
	{
		try
		{
			this->get_override("onQueryIPOInfoList")(data, error, id, last, session);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onQueryIPOQuotaInfo(dict data, dict error, int id, bool last, uint64_t session)
	{
		try
		{
			this->get_override("onQueryIPOQuotaInfo")(data, error, id, last, session);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onQueryBondIPOInfoList(dict data, dict error, int id, bool last, uint64_t session)
	{
		try
		{
			this->get_override("onQueryBondIPOInfoList")(data, error, id, last, session);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onQueryBondSwapStockInfo(dict data, dict error, int id, bool last, uint64_t session)
	{
		try
		{
			this->get_override("onQueryBondSwapStockInfo")(data, error, id, last, session);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	

	virtual void onQueryStrategy(dict data, string strategy_param, dict error_info, int32_t request_id, bool is_last, string user_name) {
		PyLock lock;
		printf("onQueryStrategy---\n");
		try {
			this->get_override("onQueryStrategy")(data,strategy_param, error_info, request_id,is_last, user_name);
			printf("get_override(onQueryStrategy)---\n");
		} catch (error_already_set const &) {
			PyErr_Print();
			printf("catch(onQueryStrategy)\n");
		}
	};

	virtual void onStrategyStateReport(dict data, string user_name) {
		PyLock lock;

		try {
			this->get_override("onStrategyStateReport")(data, user_name);
		} catch (error_already_set const &) {
			PyErr_Print();
		}
	};

	virtual void onALGOUserEstablishChannel(string user,dict error_info) {
		PyLock lock;

		try {
			this->get_override("onALGOUserEstablishChannel")(user,error_info);
		} catch (error_already_set const &) {
			PyErr_Print();
		}
	};
	virtual void onInsertAlgoOrder(dict data,dict error_info, string user_name) {
		PyLock lock;

		try {
			this->get_override("onInsertAlgoOrder")(data,error_info,user_name);
		} catch (error_already_set const &) {
			PyErr_Print();
		}
	};

	virtual void onCancelAlgoOrder(dict data,dict error_info, string user_name) {
		PyLock lock;

		try {
			this->get_override("onCancelAlgoOrder")(data,error_info, user_name);
		} catch (error_already_set const &) {
			PyErr_Print();
		}
	};

	virtual void onAlgoDisconnected(int reason) {
		PyLock lock;

		try {
			this->get_override("onAlgoDisconnected")(reason);
		} catch (error_already_set const &) {
			PyErr_Print();
		}
	};

	virtual void onAlgoConnected() {
		PyLock lock;

		try {
			this->get_override("onAlgoConnected")();
		} catch (error_already_set const &) {
			PyErr_Print();
		}
	};

	virtual void onStrategySymbolStateReport(dict data, string user_name) {
		PyLock lock;

		try {
			this->get_override("onStrategySymbolStateReport")(data, user_name);
		}
		catch (error_already_set const &) {
			PyErr_Print();
		}
	};

	virtual void onNewStrategyCreateReport(dict data, string strategy_param, string user_name) {
		PyLock lock;

		try {
			this->get_override("onNewStrategyCreateReport")(data, strategy_param, user_name);
		}
		catch (error_already_set const &) {
			PyErr_Print();
		}
	};

	virtual void onStrategyRecommendation(bool basket_flag, dict data, string strategy_param, dict error_info, int32_t request_id, bool is_last, string user_name) {
		PyLock lock;

		try {
			this->get_override("onStrategyRecommendation")(basket_flag, data, strategy_param, error_info, request_id, is_last, user_name);
		}
		catch (error_already_set const &) {
			PyErr_Print();
		}
	};

};


BOOST_PYTHON_MODULE(vnxtpalgox)
{
	//PyEval_InitThreads();	//导入时运行，保证先创建GIL
	Py_Initialize();

	class_<AlgoXApiWrap, boost::noncopyable>("AlgoXApi")
		.def("createAlgoXApi", &AlgoXApiWrap::createAlgoXApi)
		//.def("exit", &AlgoXApiWrap::exit)
		.def("getApiLastError", &AlgoXApiWrap::getApiLastError)
		.def("getApiVersion", &AlgoXApiWrap::getApiVersion)
		.def("setSoftwareVersion", &AlgoXApiWrap::setSoftwareVersion)
		.def("setHeartBeatInterval", &AlgoXApiWrap::setHeartBeatInterval)
		.def("loginALGO", &AlgoXApiWrap::loginALGO)
		.def("insertAlgoOrder", &AlgoXApiWrap::insertAlgoOrder)
		.def("cancelAlgoOrder", &AlgoXApiWrap::cancelAlgoOrder)
		.def("queryStrategy", &AlgoXApiWrap::queryStrategy)
		.def("aLGOUserEstablishChannel", &AlgoXApiWrap::aLGOUserEstablishChannel)
		.def("strategyRecommendation", &AlgoXApiWrap::strategyRecommendation)

		////////////////////////回调///////////////////////
		.def("onQueryStrategy", pure_virtual(&AlgoXApiWrap::onQueryStrategy))
		.def("onStrategyStateReport", pure_virtual(&AlgoXApiWrap::onStrategyStateReport))
		.def("onALGOUserEstablishChannel", pure_virtual(&AlgoXApiWrap::onALGOUserEstablishChannel))
		.def("onInsertAlgoOrder", pure_virtual(&AlgoXApiWrap::onInsertAlgoOrder))
		.def("onCancelAlgoOrder", pure_virtual(&AlgoXApiWrap::onCancelAlgoOrder))
		.def("onAlgoDisconnected", pure_virtual(&AlgoXApiWrap::onAlgoDisconnected))
		.def("onAlgoConnected", pure_virtual(&AlgoXApiWrap::onAlgoConnected))
		.def("onStrategySymbolStateReport", pure_virtual(&AlgoXApiWrap::onStrategySymbolStateReport))
		.def("onNewStrategyCreateReport", pure_virtual(&AlgoXApiWrap::onNewStrategyCreateReport))
		.def("onStrategyRecommendation", pure_virtual(&AlgoXApiWrap::onStrategyRecommendation))
		;
};
