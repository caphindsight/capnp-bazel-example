#include <iostream>
#include <string>
#include "set/set-service.capnp.h"
#include "third_party/capnproto/c++/src/capnp/ez-rpc.h"

using namespace std;

int main() {
    capnp::EzRpcClient client("127.0.0.1", 9070);
    auto& waitScope = client.getWaitScope();

    SetService::Client rpc = client.getMain<SetService>();

    for (;;) {
        string cmd; int x;
        cout << "> ";
        cout.flush();
        cin >> cmd >> x;

        if (cmd == "check") {
            auto req = rpc.containsRequest();
            bool res = req.send().wait(waitScope).getVal();
            cout << (res ? "contains" : "does not contain") << endl;
        } else if (cmd == "insert") {
            auto req = rpc.insertRequest();
            bool res = req.send().wait(waitScope).getRes();
            cout << (res ? "success" : "failure") << endl;
        } else if (cmd == "remove") {
            auto req = rpc.removeRequest();
            bool res = req.send().wait(waitScope).getRes();
            cout << (res ? "success" : "failure") << endl;
        } else if (cmd == "quit") {
            return 0;
        } else {
            cout << "Unsupported command" << endl;
        }
    }

    return 0;
}

