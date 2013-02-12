include_directories(../../include ../../../lua-5.2.0/src)
add_definitions(-D_CRT_SECURE_NO_WARNINGS)
aux_source_directory(. TOLUALIB_SRCS) 
add_library(tolualib ${TOLUALIB_SRCS}) 