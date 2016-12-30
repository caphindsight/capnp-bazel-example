load('//third_party/capnproto:capnproto.bzl', 'cc_capnp_library')

cc_capnp_library(
    name = 'greet-service-lib',
    srcs = ['greet-service.capnp'],
)

cc_binary(
    name = 'greet-server',
    deps = [
        '//third_party/capnproto:kj',
        '//third_party/capnproto:capnp-lib',
        ':greet-service-lib',
    ],
    srcs = ['greet-server.c++'],
)

cc_binary(
    name = 'greet-client',
    deps = [
        '//third_party/capnproto:kj',
        '//third_party/capnproto:capnp-lib',
        ':greet-service-lib',
    ],
    srcs = ['greet-client.c++'],
)

