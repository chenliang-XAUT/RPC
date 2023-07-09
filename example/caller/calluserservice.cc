#include <google/protobuf/service.h>
#include <iostream>
#include "../../src/include/mprpcapplication.h"
#include "../../src/include/mprpcchannel.h"
#include "../../src/include/mprpccontroller.h"
#include "../user.pb.h"

int main(int argc, char** argv)
{
    // 使用mprpc框架来调用rpc服务，一定要先调用框架的初始化函数
    MprpcApplication::Init(argc, argv);

    // 演示调用远程发布的rpc方法Login
    fixbug::UserServiceRpc_Stub stub(new MprpcChannel());

    // rpc方法的请求参数
    fixbug::LoginRequest request;
    request.set_name("zhang san");
    request.set_pwd("123456");

    // rpc方法的响应
    fixbug::LoginResponse response;

    // 发起rpc方法的调用 同步rpc调用过程 MprpcChannel::callmethod
    MprpcController controller;
    stub.Login(&controller, &request, &response, nullptr);// RpcChannel->RpcChannel::callMethod 集中完成rpc方法调用的参数序列化和网络发送

    // 一次rpc调用完成， 读取调用结果

    if(controller.Failed())
    {
        // 没有执行一次完整的rpc代码调用
        std::cout << controller.ErrorText() << std::endl;
    }
    else
    {

    }

    if (response.result().errcode() == 0)
    {
        std::cout << "rpc login response success:" << response.success() << std::endl;
    }
    else
    {
        std::cout << "rpc login response error: " << response.result().errmsg() << std::endl;
    }
    return 0;
}

