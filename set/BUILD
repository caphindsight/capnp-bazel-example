load("//third_party/capnproto:capnproto.bzl", "cc_capnp_library")

cc_capnp_library(
    name = "set-service-lib",
    srcs = ["set-service.capnp"],
)

cc_binary(
    name = "set-server",
    deps = [
        "//third_party/capnproto:kj",
        "//third_party/capnproto:capnp-lib",
        ":set-service-lib"
    ],
    srcs = ["set-server.cc"],
)

cc_binary(
    name = "set-client",
    deps = [
        "//third_party/capnproto:kj",
        "//third_party/capnproto:capnp-lib",
        ":set-service-lib"
    ],
    srcs = ["set-client.cc"],
)

