add_definitions(-D_CRT_SECURE_NO_WARNINGS)
include_directories(../../../include)
add_library(lua
lapi.c
lauxlib.c
lbaselib.c
lbitlib.c
lcode.c
lcorolib.c
lctype.c
ldblib.c
ldebug.c
ldo.c
ldump.c
lfunc.c
lgc.c
linit.c
liolib.c
llex.c
lmathlib.c
lmem.c
loadlib.c
lobject.c
lopcodes.c
loslib.c
lparser.c
lstate.c
lstring.c
lstrlib.c
ltable.c
ltablib.c
ltm.c
lundump.c
lvm.c
lzio.c
)
set(lua_dependency basedefine)
if(CMAKE_COMPILER_IS_GNUCC)
    set(lua_dependency "${lua_dependency} m")
endif(CMAKE_COMPILER_IS_GNUCC)
target_link_libraries(lua ${lua_dependency})
set_property(TARGET lua PROPERTY FOLDER external/lua)