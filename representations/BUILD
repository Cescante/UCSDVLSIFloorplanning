# need to load gtest using new_git_repository instead of a submodule
# load("*.bzl") # bazel includes
load("//build:rep.bzl", "rep_copts")

cc_library(
    name  = "representations",
    srcs  = ["Representations.cpp"],
    hdrs  = ["rep.h"],
    visibility = ["//visibility:public"], # prob. just bin and test
    copts = rep_copts(),
    deps  = [
        "//Utilities",
    ],
)
