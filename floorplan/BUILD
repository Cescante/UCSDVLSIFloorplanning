# bazel build specification for floor plan executables

package(default_visibility = ["//visibility:public"])

# license(["?"])
# exports_files(["LICENSE"])a

# load("*.bzl") # bazel includes
load("//build:floorplan.bzl", "fp_copts")

# cc_library(
#     name = "floorplanlibs.cpp",
#     srcs = [],
#     hdrs = [],
#     copts = "-opt"
#     deps = [],
#     )

cc_binary(
    name = "Floorplan",
    srcs = ["Floorplan.cpp"],
    copts = fp_copts(), # need to use 
    deps = [],
)
