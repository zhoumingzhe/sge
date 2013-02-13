
AUX_SOURCE_DIRECTORY(src/startup STARTUP_SRC)

if(MSVC)
    aux_source_directory(src/platform/win PLATFORM_SRC)
endif(MSVC)

if(CMAKE_COMPILER_IS_GNUCC)
    include_directories(../../include)
    aux_source_directory(src/platform/posix PLATFORM_SRC)
endif(CMAKE_COMPILER_IS_GNUCC)

include_directories(include/platform)
add_library(test_framework ${STARTUP_SRC} ${PLATFORM_SRC})
set_property(TARGET test_framework PROPERTY FOLDER test)