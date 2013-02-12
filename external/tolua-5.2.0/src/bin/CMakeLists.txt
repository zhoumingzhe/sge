include_directories(../../include ../../../lua-5.2.1/src)
aux_source_directory(. TOLUA_SRCS) 
add_executable(tolua ${TOLUA_SRCS})
target_link_libraries(tolua lua tolualib)