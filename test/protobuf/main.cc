#include "test.pb.h"
#include "string"
#include "iostream"

using namespace fixbug;

int main(){

    // LoginResponse rsp;
    // ResultCode *rc = rsp.mutable_result();
    // rc->set_errcode(1);
    // rc->set_errmsg("登录失败");

    GetFriendListsResponse rsp;
    ResultCode *rc = rsp.mutable_result();
    rc->set_errcode(0);

    // 增加好友列表元素
    User *user1 = rsp.add_friend_list();
    user1->set_name("张三");
    user1->set_age(22);
    user1->set_sex(User::MAN);

    User *user2 = rsp.add_friend_list();
    user2->set_name("张三");
    user2->set_age(22);
    user2->set_sex(User::MAN);

    // 好友个数
    std::cout << rsp.friend_list_size() << std::endl;

    return 0;
}

int main1()
{
    // 封装了login请求对象的数据
    LoginRequest req;
    req.set_name("张三");
    req.set_pwd("123456");

    // 对象数据序列化 char*
    std::string send_str;
    if (req.SerializeToString(&send_str))
    {
        std::cout << send_str.c_str() << std::endl;
    }

    // 从send_str反序列化为一个login请求对象
    LoginRequest reqB;
    if (reqB.ParseFromString(send_str))
    {
        std::cout << reqB.name() << std::endl;
        std::cout << reqB.pwd() << std::endl;
    }
    return 0;
}