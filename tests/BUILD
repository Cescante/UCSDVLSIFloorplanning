# load("*.bzl") # bazel includes
load("//build:tests.bzl", "test_copts")

cc_library(
    name = "gtestmain",
    srcs = glob(
        ["googletest/googletest/src/*.cc"],
        exclude = ["googletest/googletest/gtest-all.cc"],
    ),
    hdrs = glob([
        "googletest/googletest/include/**/*.h",
        "googletest/googletest/src/*.h",
    ]),

    copts = ["-Itests/googletest/googletest/include", "-Itests/googletest/googletest"],
    linkopts = ["-pthread"],
    visibility = ["//visibility:public"],
)

cc_test(
    name  = "rep_tests",
    srcs  = ["rep_tests.cpp"],
    copts = ["-Itests/googletest/googletest/include"] + test_copts(),
    deps  = [
        ":gtestmain",
        "//representations",
    ],
)