#include <string>
#include <iostream>

#include "test.pb.h"

int main() {
//    fixbug::LoginResponse rsp;
//    fixbug::ResultCode *rc = rsp.mutable_result();
//    rc->set_errcode(1);
//    rc->set_errmsg("Failed");

    fixbug::GetFriendListsResponese rsp;
    fixbug::ResultCode *rc = rsp.mutable_result();
    rc->set_errcode(1);
    fixbug::User *user1 = rsp.add_friend_lists();
    user1->set_name("zhangshan");
    user1->set_age(20);
    user1->set_sex(fixbug::User_Sex_MAN);

    std::cout << rsp.friend_lists_size() << std::endl;
};

int main1() {
    fixbug::LoginRequest req;
    req.set_name("Gao Sheng");
    req.set_pwd("123456");

    std::string send_str;
    if (req.SerializeToString(&send_str)) {
        std::cout << send_str.c_str() << std::endl;
    }

    fixbug::LoginRequest reqB;
    if (reqB.ParseFromString(send_str)) {
        std::cout << reqB.name() << std::endl;
        std::cout << reqB.pwd() << std::endl;
    }

    return 0;
};