#include <iostream>
#include "friend.pb.h"
#include "mprpcappliaction.h"

int main(int argc, char *argv[]) {
    MprpcApplication::Init(argc, argv);
    fixbug::FriendServiceRpc_Stub stub(new MprpcChannel());
    fixbug::GetFrinedListRequest request;
    request.set_userid(10001);

    fixbug::GetFrinedListResponse response;
    MprpcController controller;
    stub.GetFriendList(&controller, &request, &response, nullptr);
    if (controller.Failed()) {
        std::cout << controller.ErrorText() << std::endl;
    } else {
        if (response.result().errcode() == 0) {
            std::cout << "rpc  GetFriendList response success! " << std::endl;
            for (int i = 0; i < response.friends_size(); i++) {
                std::cout << "index: " << i << "name: " << response.friends(i) << std::endl;
            }
        } else {
            std::cout << "rpc GetFriendList error: " << response.result().errmsg() << std::endl;
        }
    }
    return 0;
}
