
AUX_SOURCE_DIRECTORY(src/startup STARTUP_SRC)

if(SGE_WIN32)
    aux_source_directory(src/platform/win PLATFORM_SRC)
elseif(SGE_POSIX)
    aux_source_directory(src/platform/posix PLATFORM_SRC)
endif(SGE_WIN32)

include_directories(../../include)
include_directories(include/platform)
add_library(test_framework ${STARTUP_SRC} ${PLATFORM_SRC})
set_property(TARGET test_framework PROPERTY FOLDER test)
