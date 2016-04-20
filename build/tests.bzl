# -*-Python -*-

def test_copts():
    return (["-Wall", "-Werror", "-m64", "-std=c++11", "-I.", "-Itests/googletest/googletest/include/", "-O2"])
