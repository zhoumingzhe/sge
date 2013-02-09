include_directories(../../include/basedefine)

AUX_SOURCE_DIRECTORY(. BASEDEFINE_SRC)
add_library(basedefine ${BASEDEFINE_SRC})
