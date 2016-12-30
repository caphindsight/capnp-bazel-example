#include <cstdlib>
#include <iostream>
#include <string>
#include "third_party/capnproto/c++/src/capnp/ez-rpc.h"
#include "greet-service.capnp.h"

inline int Rand() {
    return rand();
}

class GreetServiceImpl final : public GreetService::Server {
public:
    kj::Promise<void> greet(GreetContext context) override {
        auto name = context.getParams().getName();
        std::string greeting = std::string("Hello, ") + std::string(name.cStr()) + std::string("!");
        context.getResults().setGreeting(greeting.c_str());
        return kj::READY_NOW;
    }

    kj::Promise<void> rand(RandContext context) override {
        int rand_val = Rand() % 10;
        context.getResults().setRandVal(rand_val);
        return kj::READY_NOW;
    }
};

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0]<< " ADDRESS[:PORT]" << std::endl;
        return 1;
    }

    capnp::EzRpcServer server(kj::heap<GreetServiceImpl>(), argv[1], 9060);
    auto& waitScope = server.getWaitScope();

    kj::NEVER_DONE.wait(waitScope);

    return 0;
}

