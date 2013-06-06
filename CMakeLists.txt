cmake_minimum_required(VERSION 2.8.10)

project(sge)
enable_testing()

#SET(BUILD_SHARED_LIBS ON)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(SGE_POSIX true)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread -Wall -Werror")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -Wall -Werror")
    #Compiler is linker, so the option should be prefixed by -Wl
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--fatal-warnings")
    set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} --fatal-warnings")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--fatal-warnings")

elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(SGE_POSIX true)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread -Wall -Werror")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -Wall -Werror")
    #Compiler is linker, so the option should be prefixed by -Wl
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--fatal-warnings")
    set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} --fatal-warnings")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--fatal-warnings")

elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
  # using Intel C++
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(SGE_WIN32 true) 
    foreach(flag_var
        CMAKE_C_FLAGS CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_RELEASE
        CMAKE_C_FLAGS_MINSIZEREL CMAKE_C_FLAGS_RELWITHDEBINFO
        CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
        CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO
        )
        
        if(${flag_var} MATCHES "/Ob0")
            string(REGEX REPLACE "/Ob0" "/Oi /Ob1" ${flag_var} "${${flag_var}}")
        endif(${flag_var} MATCHES "/Ob0")

        #4100: unreferenced parameter, tolua
        #4324: struct alignment, lua
        #4709: comma operator within array index expression, lua
        #4201: nameless union/struct
        if(${flag_var} MATCHES "/W[0-4]")
            string(REGEX REPLACE "/W[0-4]" "/W4 /WX /wd4100 /wd4324 /wd4709 /wd4201" ${flag_var} "${${flag_var}}")
        endif(${flag_var} MATCHES "/W[0-4]")
   
    endforeach(flag_var)

    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /WX")
    set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} /WX")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /WX")

endif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")

SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/None/lib)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/None/bin)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/None/bin)

SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${PROJECT_BINARY_DIR}/Debug/lib)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${PROJECT_BINARY_DIR}/Debug/bin)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_BINARY_DIR}/Debug/bin)

SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${PROJECT_BINARY_DIR}/Release/lib)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${PROJECT_BINARY_DIR}/Release/bin)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_BINARY_DIR}/Release/bin)

SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL ${PROJECT_BINARY_DIR}/MinSizeRel/lib)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY_MINSIZEREL ${PROJECT_BINARY_DIR}/MinSizeRel/bin)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${PROJECT_BINARY_DIR}/MinsizeRel/bin)

SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO ${PROJECT_BINARY_DIR}/RelWithDebInfo/lib)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO ${PROJECT_BINARY_DIR}/RelWithDebInfo/bin)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${PROJECT_BINARY_DIR}/RelWithDebInfo/bin)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory(external)
add_subdirectory(src)
add_subdirectory(test)

