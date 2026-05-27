# encoding: UTF-8

import os
import uuid
from time import sleep

from vnxtpalgox import *

    
def printFuncName(*args):
    """"""
    print('*' * 50)
    print(args)
    print('*' * 50)


class TestApi(AlgoXApi):
    """"""

    def __init__(self):
        """Constructor"""
        super(TestApi, self).__init__()

    #当客户端与AlgoBus通信连接断开时，该方法被调用。
	#@param reason 错误原因，请与错误代码表对应
	#@remark 请不要堵塞此线程，否则会影响algo的登录
    def onAlgoDisconnected(self, reason):
        """"""
        printFuncName("onAlgoDisconnected", reason)

    #当客户端与AlgoBus断线连接时，该方法被调用，仅在断线重连成功后会被调用。
    def OnAlgoConnected(self):
        """"""
        printFuncName('OnAlgoConnected')
        
    
    #algo业务中报送策略单的响应
    #@param data 用户报送的策略单的具体信息
    #@param error 报送策略单发生错误时返回的错误信息，当error为空，或者error.error_id为0时，表明没有错误
    #@param user 资金账户
    #@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    def onInsertAlgoOrder(self,data,error, user):
        """"""
        printFuncName('onInsertAlgoOrder',data, error,user)
        print("data['m_strategy_type']:",data['m_strategy_type'])#策略类型
        print("data['m_strategy_state']:",data['m_strategy_state'])#策略状态 0-创建中,1-已创建,2-开始执行中,3-已执行,4-停止中,5-已停止,6-销毁中,7-已销毁,8-发生错误,
        print("data['m_client_strategy_id']:",data['m_client_strategy_id'])#客户策略id
        print("data['m_xtp_strategy_id']:",data['m_xtp_strategy_id'])#xtp策略id
        if('error_id' in error):
            print("error['error_id']:",error['error_id'])
            print("error['error_msg']:",error['error_msg'])
    
    
    #algo业务中撤销策略单的响应
    #@param data 用户撤销的策略单的具体信息
    #@param error 撤销策略单发生错误时返回的错误信息，当error为空，或者error.error_id为0时，表明没有错误
    #@param user 资金账户
    #@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    def onCancelAlgoOrder(self,data,error, user):
        """"""
        printFuncName('onCancelAlgoOrder',data, error,user)
        print("data['m_strategy_type']:",data['m_strategy_type'])#策略类型
        print("data['m_strategy_state']:",data['m_strategy_state'])#策略状态 0-创建中,1-已创建,2-开始执行中,3-已执行,4-停止中,5-已停止,6-销毁中,7-已销毁,8-发生错误,
        print("data['m_client_strategy_id']:",data['m_client_strategy_id'])#客户策略id
        print("data['m_xtp_strategy_id']:",data['m_xtp_strategy_id'])#xtp策略id
        if('error_id' in error):
            print("error['error_id']:",error['error_id'])
            print("error['error_msg']:",error['error_msg'])
    
    #algo业务中查询策略列表的响应
    #@param data 策略具体信息
    #@param strategy_param 此策略中包含的参数，如果error为空，或者error.error_id为0时，有意义
    #@param error 查询查询策略列表发生错误时返回的错误信息，当error.error_id为0时，表明没有错误
    #@param request_id 此消息响应函数对应的请求ID
    #@param last 此消息响应函数是否为reqid这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
    #@param user 资金账户
    #@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    def onQueryStrategy(self,data,strategy_param,error, reqid, last, user):
        """"""
        printFuncName('onQueryStrategy', data,strategy_param, error, reqid, last,user)
        print("data['m_strategy_type']:",data['m_strategy_type'])#策略类型
        print("data['m_strategy_state']:",data['m_strategy_state'])#策略状态 0-创建中,1-已创建,2-开始执行中,3-已执行,4-停止中,5-已停止,6-销毁中,7-已销毁,8-发生错误,
        print("data['m_client_strategy_id']:",data['m_client_strategy_id'])#客户策略id
        print("data['m_xtp_strategy_id']:",data['m_xtp_strategy_id'])#xtp策略id
        if('error_id' in error):
            print("error['error_id']:",error['error_id'])
            print("error['error_msg']:",error['error_msg'])
    
    #algo业务中报送母单创建时的推送消息(包括其他客户端创建的母单)
	#@param strategy_info 策略具体信息
	#@param strategy_param 此策略中包含的参数
	#@param user 资金账户对应的session_id，登录时得到
	#@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    def onNewStrategyCreateReport(self, data, strategy_param, user):
        """"""
        printFuncName('onNewStrategyCreateReport', data, strategy_param, user)
        print("data['m_strategy_type']:",data['m_strategy_type'])#策略类型
        print("data['m_strategy_state']:",data['m_strategy_state'])#策略状态 0-创建中,1-已创建,2-开始执行中,3-已执行,4-停止中,5-已停止,6-销毁中,7-已销毁,8-发生错误,
        print("data['m_client_strategy_id']:",data['m_client_strategy_id'])#客户策略id
        print("data['m_xtp_strategy_id']:",data['m_xtp_strategy_id'])#xtp策略id
        
    
    #algo业务中策略运行时策略状态通知
    #@param data 用户策略运行情况的状态通知
    #@param user 资金账户
    #@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    def onStrategyStateReport(self,data, user):
        """"""
        printFuncName('onStrategyStateReport', data,user)
        print("m_strategy_info['m_strategy_type']:",data['m_strategy_info']['m_strategy_type'])#策略类型
        print("m_strategy_info['m_strategy_state']:",data['m_strategy_info']['m_strategy_state'])#策略状态 0-创建中,1-已创建,2-开始执行中,3-已执行,4-停止中,5-已停止,6-销毁中,7-已销毁,8-发生错误,
        print("m_strategy_info['m_client_strategy_id']:",data['m_strategy_info']['m_client_strategy_id'])#客户策略id
        print("m_strategy_info['m_xtp_strategy_id']:",data['m_strategy_info']['m_xtp_strategy_id'])#xtp策略id
        print("data['m_strategy_qty']:",data['m_strategy_qty'])#策略总量
        print("data['m_strategy_ordered_qty']:",data['m_strategy_ordered_qty'])#策略已委托数量
        print("data['m_strategy_cancelled_qty']:",data['m_strategy_cancelled_qty'])#策略已撤单数量
        print("data['m_strategy_execution_qty']:",data['m_strategy_execution_qty'])#策略已成交数量
        print("data['m_strategy_unclosed_qty']:",data['m_strategy_unclosed_qty'])#策略未平仓数量(T0卖出数量-买入数量)
        print("data['m_strategy_asset']:",data['m_strategy_asset'])#策略总金额
        print("data['m_strategy_ordered_asset']:",data['m_strategy_ordered_asset'])#策略已委托金额
        print("data['m_strategy_execution_asset']:",data['m_strategy_execution_asset'])#策略已成交金额
        print("data['m_strategy_execution_price']:",data['m_strategy_execution_price'])#策略执行价格
        print("data['m_strategy_market_price']:",data['m_strategy_market_price'])#策略市场价
        print("data['m_strategy_price_diff']:",data['m_strategy_price_diff'])#策略执行价差
        print("data['m_strategy_asset_diff']:",data['m_strategy_asset_diff'])#策略执行绩效(T0资金预净收入)
        print("data['error_id']:",data['error_id'])#错误代码
        print("data['error_msg']:",data['error_msg'])#错误信息
        
    
    #algo业务中用户建立算法通道的消息响应
    #@param user 用户名
    #@param error 建立算法通道发生错误时返回的错误信息，error.error_id为0时，表明没有错误，即算法通道成功
    #@remark 算法通道建立成功后，才能对用户创建策略等操作，一个用户只能拥有一个算法通道，如果之前已经建立，则无需重复建立
    def onALGOUserEstablishChannel(self,user,error):
        """"""
        printFuncName('onALGOUserEstablishChannel',user, error)
        if('error_id' in error):
            print("error['error_id']:",error['error_id'])
            print("error['error_msg']:",error['error_msg'])
    
    
    #algo业务中策略运行时策略指定证券执行状态通知
    #@param data 用户策略指定证券运行情况的状态通知
    #@param user 资金账户
    #@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    def onStrategySymbolStateReport(self,data,user):
        """"""
        printFuncName('onStrategySymbolStateReport',data,user)
        print("m_strategy_info['m_strategy_type']:",data['m_strategy_info']['m_strategy_type'])#策略类型
        print("m_strategy_info['m_strategy_state']:",data['m_strategy_info']['m_strategy_state'])#策略状态
        print("m_strategy_info['m_client_strategy_id']:",data['m_strategy_info']['m_client_strategy_id'])#客户策略id
        print("m_strategy_info['m_xtp_strategy_id']:",data['m_strategy_info']['m_xtp_strategy_id'])#xtp策略id
        print("data['m_ticker']:",data['m_ticker'])#证券代码
        print("data['m_market']:",data['m_market'])#市场
        print("data['m_side']:",data['m_side'])#买卖方向，=0时为T0单
        print("data['m_strategy_qty']:",data['m_strategy_qty'])#策略总量
        print("data['m_strategy_ordered_qty']:",data['m_strategy_ordered_qty'])#策略已委托数量
        print("data['m_strategy_cancelled_qty']:",data['m_strategy_cancelled_qty'])#策略已撤单数量
        print("data['m_strategy_execution_qty']:",data['m_strategy_execution_qty'])#策略已成交数量
        print("data['m_strategy_buy_qty']:",data['m_strategy_buy_qty'])#策略已买入数量(T0)
        print("data['m_strategy_sell_qty']:",data['m_strategy_sell_qty'])#策略已卖出数量(T0)
        print("data['m_strategy_unclosed_qty']:",data['m_strategy_unclosed_qty'])#策略未平仓数量(T0卖出数量-买入数量)
        print("data['m_strategy_asset']:",data['m_strategy_asset'])#策略总金额
        print("data['m_strategy_ordered_asset']:",data['m_strategy_ordered_asset'])#策略已委托金额
        print("data['m_strategy_execution_asset']:",data['m_strategy_execution_asset'])#策略已成交金额
        print("data['m_strategy_buy_asset']:",data['m_strategy_buy_asset'])#策略买入金额(T0)
        print("data['m_strategy_sell_asset']:",data['m_strategy_sell_asset'])#策略卖出金额(TO)
        print("data['m_strategy_unclosed_asset']:",data['m_strategy_unclosed_asset'])#策略未平仓金额(T0)
        print("data['m_strategy_asset_diff']:",data['m_strategy_asset_diff'])#策略毛收益增强金额(T0)
        print("data['m_strategy_execution_price']:",data['m_strategy_execution_price'])#策略执行价格
        print("data['m_strategy_market_price']:",data['m_strategy_market_price'])#策略市场价
        print("data['m_strategy_price_diff']:",data['m_strategy_price_diff'])#策略执行价差(T0时为毛增强收益率)
        print("data['error_id']:",data['error_id'])#错误信息
        print("data['error_msg']:",data['error_msg'])#错误信息
    
	

	#algo业务中算法推荐的响应
	#@param basket_flag 是否将满足条件的推荐结果打包成母单篮的标志，与请求一致，如果此参数为true，那么请以返回的strategy_param为准
	#@param data 推荐算法的具体信息，当basket_flag=true时，此结构体中的market和ticker将没有意义，此时请以strategy_param为准
	#@param strategy_param 算法参数，可直接用来创建母单，如果error_info.error_id为0时，有意义
	#@param error 请求推荐算法发生错误时返回的错误信息，当error为空，或者error.error_id为0时，表明没有错误
	#@param reqid 此消息响应函数对应的请求ID
	#@param last 此消息响应函数是否为request_id这条请求所对应的最后一个响应，当为最后一个的时候为true，如果为false，表示还有其他后续消息响应
	#@param user 资金账户
	#@remark 需要快速返回，否则会堵塞后续消息，当堵塞严重时，会触发断线
    def onStrategyRecommendation(self, basket_flag, data, strategy_param, error, reqid, last, user):
        """"""
        printFuncName('onStrategyRecommendation', basket_flag, data, strategy_param, error, reqid, last, user)
        print("basket_flag:", basket_flag)#是否将满足条件的推荐结果打包成母单篮的标志
        print("strategy_param:",strategy_param)#算法参数
        print("data['m_strategy_type']:",data['m_strategy_type'])#策略类型
        print("data['m_market']:",data['m_market'])#交易市场
        print("data['m_ticker']:",data['m_ticker'])#证券代码
        print("data['unused']:",data['unused'])#保留域
        if('error_id' in error):
            print("error['error_id']:",error['error_id'])
            print("error['error_msg']:",error['error_msg'])
        



if __name__ == '__main__':

    ip = '122.112.139.0'
    port = 6202
    user = 'username'
    password = 'password'
    reqid = 0

    #创建TraderApi
    #@param client_id （必须输入）客户端id，用于区分同一用户的不同客户端，由用户自定义
    #@param save_file_path （必须输入）存贮订阅信息文件的目录，请设定一个真实存在的有可写权限的路径
    #@param log_level 日志输出级别
    #@return 创建出的UserApi
    #@remark 只能创建一次，系统不支持过夜，请确保每天开盘前重新启动
    api = TestApi()
    api.createAlgoXApi(2, os.getcwd(),4)
    
    
    #获取API的发行版本号
    #@return 返回api发行版本号
    retGetApiVersion = api.getApiVersion()
    printFuncName('getApiVersion',retGetApiVersion)

    #获取API的系统错误
    #@return 返回的错误信息，可以在loginALGO、insertAlgoOrder等接口返回值非0时调用，获取失败的原因
    #@remark 可以在调用api接口失败时调用，例如loginALGO失败时
    retGetLastError = api.getApiLastError();
    printFuncName('getApiLastError', retGetLastError) 


    #设置软件开发版本号
    #@param version 用户开发软件版本号，非api发行版本号，长度不超过15位
    #@remark 此函数必须在loginALGO之前调用，标识的是客户端版本号，而不是API的版本号，由用户自定义
    api.setSoftwareVersion("test")

    #设置心跳检测时间间隔，单位为秒
	#@param interval 心跳检测时间间隔，单位为秒
	#@remark 此函数必须在loginALGO之前调用
    api.setHeartBeatInterval(30)   

    
    #用户登录algo服务器请求
    #@return 表明此资金账号登录是否成功，非“0”表示登录失败，可以调用getApiLastError()来获取错误代码，“0”表示登录成功
    #@param ip algo服务器地址，类似“127.0.0.1”
    #@param port algo服务器端口号
    #@param user 登录用户名
    #@param password 登录密码
    #@param sock_type “1”代表TCP，“2”代表UDP，目前暂时只支持TCP
    #@remark 此函数为同步阻塞式，不需要异步等待登录成功，当函数返回即可进行后续操作，此api只需调用一次，所有用户共用即可
    retLoginALGO = api.loginALGO(ip, port, user, password, 1)
    printFuncName('loginALGO', retLoginALGO)   
    if retLoginALGO != 0 :
       retGetApiLastError = api.getApiLastError()
       printFuncName('getApiLastError', retGetApiLastError)   
    
    #用户请求使用algo服务器建立算法通道
    #@return 表表明此资金账号建立算法通道请求消息发送是否成功，非“0”表示发送失败，可以调用getApiLastError()来获取错误代码，“0”表示发送成功
    #@param user 登录用户名
    #@param password 登录密码
    #@remark 此函数为异步方式，一个用户只能拥有一个算法通道，如果之前已经建立，则无需重复建立
    reqid += 1
    aLGOUserEstablishChannel = api.aLGOUserEstablishChannel(user,password)
    printFuncName('aLGOUserEstablishChannel',aLGOUserEstablishChannel)
    if aLGOUserEstablishChannel != 0 :
        retGetApiLastError = api.getApiLastError()
        printFuncName('getApiLastError-aLGOUserEstablishChannel', retGetApiLastError)   
    sleep(1)

    #algo业务中用户报算法单请求
    #@return 算法报单请求发送是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
    #@param strategy_type 需要创建的策略类型
    #@param client_strategy_id 用户自定义id，帮助用户定位
    #@param strategy_param 策略参数
    #@param user 资金账户
    #@remark 仅能在用户建立算法通道后使用，算法单的异步通知
    reqid += 1
    strategy_type = 5001 
    strategy_param = '{"start_time": "09:30:00", "end_time": "14:57:00", "buy_side": "BUY", "sell_side": "SELL", "business_type": "CASH", "trade_list": [{"market": "SH", "ticker": "600000", "quantity": 13000}]}'
    client_strategy_id = 1001
    insertAlgoOrder = api.insertAlgoOrder(strategy_type,client_strategy_id,strategy_param,user)
    printFuncName('insertAlgoOrder',insertAlgoOrder)
    if insertAlgoOrder != 0 :
        retGetApiLastError = api.getApiLastError()
        printFuncName('getApiLastError-insertAlgoOrder', retGetApiLastError)   
    sleep(1)
    

    


    
    #algo业务中用户撤销算法单请求
    #@return 请求发送是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
    #@param cancel_flag 是否需要撤销的算法单已下的订单，true-撤单，false-不撤单
    #@param xtp_strategy_id 需要撤销的算法单在xtp algobus系统中的id
    #@param user 资金账户
    #@remark 仅能在用户建立算法通道后调用
    reqid += 1
    xtp_strategy_id = 1894408323075
    cancelAlgoOrder = api.cancelAlgoOrder(0,xtp_strategy_id,user)
    printFuncName('cancelAlgoOrder',cancelAlgoOrder)
    if cancelAlgoOrder != 0 :
        retGetApiLastError = api.getApiLastError()
        printFuncName('getApiLastError', retGetApiLastError)   
    sleep(1)
    
    #algo业务中查询用户策略请求
    #@return 请求发送是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
    #@param strategy_type 需要查询的策略类型，可填0
    #@param client_strategy_id 需要查询的策略用户自定义id，可填0
    #@param xtp_strategy_id 需要查询的策略在xtp系统中的id，如果指定，就一定按指定查询，如果填0，则按其他筛选条件查询
    #@param user 资金账户
    #@param request_id 用于用户定位查询响应的ID，由用户自定义
    #@remark xtp_strategy_id条件的优先级最高，只有当xtp_strategy_id为0时，其他条件才生效，此条请求可能对应多条回应消息
    reqid += 1
    xtp_strategy_id = 1743756787714
    queryStrategy = api.queryStrategy(0,0,xtp_strategy_id,user, reqid)
    printFuncName('queryStrategy',queryStrategy)
    sleep(1)

    
  
    
    sleep(1)
	#algo业务中请求推荐算法
	#@return 请求发送是否成功，“0”表示成功，非“0”表示出错，此时用户可以调用GetApiLastError()来获取错误代码
	#@param basket_flag 是否将满足条件的推荐结果打包成母单篮的标志，true-打包
	#@param basket_param 需要算法推荐的证券列表，为json字串，具体格式参考说明文档或咨询运营人员
	#@param user 资金账户
	#@param reqid 用于用户定位查询响应的ID，由用户自定义
	#@remark 此条请求可能对应多条回应消息，此功能上线时间视服务器后台支持情况而定，具体以运营通知时间为准
    reqid += 1
    basket_flag = True
    #有回调的算法推荐
    basket_param = "{\"symbol_list\": [{\"ticker\": \"000001\", \"market\": \"SZ\", \"strategy_category\": \"ALGO\", \"quantity\": 10000, \"side\": \"BUY\"}]}"
    #无回调的算法推荐
    #basket_param = "{\"symbol_list\": [{\"ticker\": \"000001\", \"market\": \"SZ\", \"strategy_category\": \"T0\", \"quantity\": 10000}]}"
    strategyRecommendation = api.strategyRecommendation(basket_flag, basket_param, user, reqid)
    printFuncName('strategyRecommendation', strategyRecommendation)
    
    sleep(100)
    

   
   
    

