# load("*.bzl") # bazel includes
load("//build:tests.bzl", "test_copts")

cc_test(
    name  = "rep_tests",
    srcs  = ["rep_tests.cpp"],
    copts = ["-Iexternal/gtest/include"] + test_copts(),
    deps  = [
        "@gtest//:main",
        "//representations",
        "//Utilities",
    ],
    size = "small",
)