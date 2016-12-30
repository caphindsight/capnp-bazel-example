#include <iostream>
#include "third_party/capnproto/c++/src/capnp/ez-rpc.h"
#include "greet/greet-service.capnp.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " HOST[:PORT]" << std::endl;
        return 1;
    }

    std::cout << "Your name: ";
    std::cout.flush();

    std::string name;
    std::cin >> name;

    std::cout << "Initializing client.." << std::endl;
    capnp::EzRpcClient client(argv[1], 9060);

    auto& waitScope = client.getWaitScope();

    std::cout << "Establishing RPC session.." << std::endl;
    GreetService::Client cap = client.getMain<GreetService>();

    auto request = cap.greetRequest();
    request.setName(name);

    std::cout << "Sending request.." << std::endl;
    auto promise = request.send();

    std::cout << "Waiting for response.." << std::endl;
    auto response = promise.wait(waitScope);

    std::cout << "Received greeting!" << std::endl;
    auto greeting = response.getGreeting();

    std::cout << greeting.cStr() << std::endl;

    std::cout << "Sending random number request.." << std::endl;
    auto response2 = cap.randRequest().send().wait(waitScope);
    
    std::cout << "x = " << response2.getRandVal() << std::endl;

    return 0;
}

