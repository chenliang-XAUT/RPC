#include "./include/mrpcconfig.h"
#include <iostream>
#include <string>

// 负责解析加载配置文件
void MrpcConfig::LoadConfigFile(const char *config_file)
{
    // 打开文件
    FILE *pf = fopen(config_file, "r");
    if (pf == nullptr)
    {
        std::cout << config_file << " is not exist!" << std::endl;
        exit(EXIT_FAILURE);
    }

    // 1.去掉注释  2.正确的配置项(含有=) 3.去掉开头和结尾的多余空格
    while(!feof(pf)){
        char buf[512] = {0};
        // 读取一行
        fgets(buf, 512, pf);

        std::string read_buf(buf);
        Trim(read_buf);

        // 判断是否为注释
        if (read_buf[0] == '#' || read_buf.empty())
        {
            continue;
        }

        // 解析配置项
        int idx = read_buf.find('=');
        if (idx == -1)
        {
            // 配置项不合法
            continue;
        }

        std::string key, value;
        key = read_buf.substr(0, idx);
        // 去掉前后空格
        Trim(key);

        // 截取'\n'
        int endidx = read_buf.find('\n', idx);
        value = read_buf.substr(idx+1, endidx-idx-1);
        // 去掉前后空格
        Trim(value);

        m_configMap[key] = value;   
    } 
}

// 查询配置项信息
std::string MrpcConfig::Load(const std::string &key)
{
    auto it = m_configMap.find(key);
    if (it == m_configMap.end())
    {
        return "";
    }
    
    return m_configMap[key];
}

// 去掉字符串前后的空格
void MrpcConfig::Trim(std::string &src_buf)
{
    // 去掉前面的多余的空格
    // 从开头找到第一个不是空格的元素下标,如果开头没有空格则返回-1
    int idx = src_buf.find_first_not_of(' ');

    if (idx != -1){
        // 处理开头空格
        src_buf = src_buf.substr(idx, src_buf.size()-idx);
    }

    // 去掉字符串后面的空格
    idx = src_buf.find_last_not_of(' ');

    if(idx != -1)
    {
        // 处理后面的空格
        src_buf = src_buf.substr(0, idx+1);
    }

}