#include "./include/mprpcapplication.h"
#include <iostream>
#include <unistd.h>
#include <string>

// 初始化静态成员变量
MrpcConfig MprpcApplication::m_config;

// 返回静态成员变量，用于处理配置文件读取
MrpcConfig& MprpcApplication::getConfig()
{
    return m_config;
}

void ShowArgsHelp()
{
    std::cout << "format: command -i <configfile>" << std::endl;
}

// 读取配置文件，加载相关参数
void MprpcApplication::Init(int argc, char **argv)
{
    if(argc < 2)
    {
        ShowArgsHelp();
        exit(EXIT_FAILURE);
    }

    int c = 0;
    std::string config_file;

    while ((c = getopt(argc, argv, "i:")) != -1)
    {
        switch (c)
        {
        case 'i':
            config_file = optarg;
            break;
        case '?':
            std::cout << "invalid args!" << std::endl;
            ShowArgsHelp();
            exit(EXIT_FAILURE);
            break;
        case ':':
            std::cout << "need <configfile>" << std::endl;
            ShowArgsHelp();
            exit(EXIT_FAILURE);
        default:
            break;
        }
    }

    // 开始加载配置文件
    m_config.LoadConfigFile(config_file.c_str());
    
    // std::cout << "rpcserverip: " << m_config.Load("rpcserverip") << std::endl;

}
MprpcApplication& MprpcApplication::GetInstance()
{
    static MprpcApplication app;
    return app;
}