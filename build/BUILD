# BUILD file for all build settings

package(default_visibility = [":internal"])

# licenses(["file?"])

# config_setting(
#     name = "darwin",
#     values = {"cpu": "darwin"},
#     visibility = ["//visibility:public"],
# )

pubckage_group(
    name = "build",
    packages = ["//build/..."]
)

filegroup(
    name = "build_files",
    srcs = glob(
        ["**/*"],
        exclude = [
            "**/METADATA",
            "**/OWNERS",        ],
    ),
    visibility = ["//build:__subpackages__"],
)
