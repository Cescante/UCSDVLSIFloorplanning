# -*- Python -*-

# TODO: need to specify test vs ship using config_setting
def fp_copts():
    return (["-Wall", "-Werror", "-m64", "-std=c++11", "-I."] + ship_copts())

def ship_copts():
    return (["-O2"])

def test_copts():
    return (["-DDEBUG", "-g", "-O0"])
