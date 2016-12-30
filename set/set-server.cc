#include <set>
#include <iostream>
#include "set/set-service.capnp.h"
#include "third_party/capnproto/c++/src/capnp/ez-rpc.h"
using namespace std;

class SetServiceImpl final : public SetService::Server {
public:
    kj::Promise<void> contains(ContainsContext ctx) override {
        int x = ctx.getParams().getX();
        ctx.getResults().setVal(has(x));
        return kj::READY_NOW;
    }

    kj::Promise<void> insert(InsertContext ctx) override {
        int x = ctx.getParams().getX();
        if (!has(x)) {
            data.insert(x);
            ctx.getResults().setRes(true);
        } else {
            ctx.getResults().setRes(false);
        }
        return kj::READY_NOW;
    }
    
    kj::Promise<void> remove(RemoveContext ctx) override {
        int x = ctx.getParams().getX();
        auto it = data.find(x);
        if (it != data.end()) {
            data.erase(it);
            ctx.getResults().setRes(true);
        } else {
            ctx.getResults().setRes(false);
        }
        return kj::READY_NOW;
    }

private:
    inline bool has(int x) const {
        auto it = data.find(x);
        return it != data.cend();
    }

private:
    set<int> data;
};


int main() {
    capnp::EzRpcServer server(kj::heap<SetServiceImpl>(), "127.0.0.1", 9070);
    auto& waitScope = server.getWaitScope();

    kj::NEVER_DONE.wait(waitScope);

    return 0;
}

