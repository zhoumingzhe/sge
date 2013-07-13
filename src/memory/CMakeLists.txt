include_directories(../../include/memory)

AUX_SOURCE_DIRECTORY(. MEMORY_SRC)
add_library(memory SHARED ${MEMORY_SRC})
set_property(TARGET memory PROPERTY FOLDER src)
