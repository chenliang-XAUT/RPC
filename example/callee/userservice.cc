#include <iostream>
#include <string>
#include "../user.pb.h"
#include "../../src/include/mprpcapplication.h"
#include "../../src/include/rpcprovider.h"
using namespace fixbug;

// // UserService是一个本地服务，提供了两个进程内的本地方法，Login和GetFriendLists

// class UserService
// {
// public:
//     bool Login(std::string name, std::string pwd)
//     {
//         std::cout << "doing local service: Login" << std::endl;
//         std::cout << "name: " << name << " pwd: " << pwd << std::endl;
//         return true;
//     }
// };

// 将UserService 改造成使用在rpc服务提供端
class UserService : public UserServiceRpc
{
public:
    // 本地处理业务
    bool Login(std::string name, std::string pwd)
    {
        std::cout << "doing local service: Login" << std::endl;
        std::cout << "name: " << name << " pwd: " << pwd << std::endl;
        return true;
    }

    /* 
    重写基类UserServiceRpc Login 虚函数
    1. caller -->  Login(LoginRequest) --> muduo  --> callee
    2. callee -->  Login(LoginRequest) --> 交到下面重写的Login方法  --> 本地的Login方法
    */ 
    void Login(::google::protobuf::RpcController* controller,
                       const ::fixbug::LoginRequest* request,
                       ::fixbug::LoginResponse* response,
                       ::google::protobuf::Closure* done)
    {
        // rpc服务消费端caller给rpc服务提供端caller上报了请求参数LoginRequest
        // callee端获取相关数据，处理相关业务
        std::string name = request->name();
        std::string pwd = request->pwd();

        // 做本地业务
        bool login_result = Login(name, pwd); // 调用本地处理业务方法

        // 将 错误码，错误消息，返回值 写入响应
        fixbug::ResultCode *code = response->mutable_result();
        code->set_errcode(0);
        code->set_errmsg("");
        response->set_success(login_result);

        // 执行回调操作 将响应对象数据进行序列化和网络发送(由框架完成)
        done->Run();

    }
};

int main(int argc, char **argv)
{
    // 调用框架的初始化操作
    MprpcApplication::Init(argc, argv);

    // provider是一个rpc网络服务对象，把UserService对象发布到rpc节点上
    RpcProvider provider;
    provider.NotifyService(new UserService());

    //启动一个rpc服务发布节点 Run以后，进程进入阻塞状态，等待远程的rpc调用请求
    provider.Run();
    return 0; 
}