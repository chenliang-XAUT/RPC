#pragma once
#include "mrpcconfig.h"

// mprpc框架的基础类, 负责框架的一些初始化操作
class MprpcApplication
{
public:
    static void Init(int argc, char **argv);
    static MprpcApplication& GetInstance();
    static MrpcConfig& getConfig();
private:
    MprpcApplication(){}
    MprpcApplication(const MprpcApplication&) = delete;
    MprpcApplication(MprpcApplication&&) = delete;

    static MrpcConfig m_config;
};