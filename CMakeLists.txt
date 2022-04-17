cmake_minimum_required(VERSION 3.20.0)
project(learn
        VERSION 0.0.1
        DESCRIPTION "C AND CXX LEARN"
        HOMEPAGE_URL "www.etamin.xyz"
        LANGUAGES C
        )



# CONFIGURATION
set(CMAKE_C_STANDARD 99)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CMAKE_BUILD_TYPE Debug CACHE STRING "set build type to debug")
#set(CMAKE_BUILD_TYPE "Debug”)
set(CMAKE_VERBOSE_MAKEFILEON ON)


# 指定头文件搜索路径
include_directories(lib)
# 指定lib目录
link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY}) #添加动态连接库的路径
include(CTest)
enable_testing()

add_executable(main
        main.c main.h
headers/chapter_10.h sources/chapter_10.c
)

# NORMAL
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME})
# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/bin)
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/bin)
# set(CMAKE_C_FLAGS "-std=c99 -ldl")


#编译模式判断
if(CMAKE_BUILD_TYPE AND (CMAKE_BUILD_TYPE STREQUAL "Debug"))
 #DEBUG模式下的编译指令
 #CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG在arch-linux+gcc11.2+cmake3.23.1无效，main会出现在build下
 set(EXECUTABLE_OUTPUT_PATH  ${CMAKE_CURRENT_BINARY_DIR}/debug/${PROJECT_NAME})
 set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}/debug//${PROJECT_NAME}/bin)
 set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}/debug/${PROJECT_NAME}/bin)
 set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0 -Wall -g -ggdb -ldl")
 message("Debug mode:${CMAKE_C_FLAGS_DEBUG}")
elseif(CMAKE_BUILD_TYPE AND (CMAKE_BUILD_TYPE STREQUAL "Release"))
 #RELEASE模式下的编译指令
 set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/release/${PROJECT_NAME})
 set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR}/release/${PROJECT_NAME}/bin)
 set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR}/release/${PROJECT_NAME}/bin)
 set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Wall -O3 -ldl")
 message("Release mode:${CMAKE_C_FLAGS_RELEASE}")
else()
 set(EXECUTABLE_OUTPUT_PATH  ${CMAKE_CURRENT_BINARY_DIR}/debug/${PROJECT_NAME})
 set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}/debug//${PROJECT_NAME}/bin)
 set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}/debug/${PROJECT_NAME}/bin)
 set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0 -Wall -g -ggdb -ldl")
 message("Default Mode(Debug):${CMAKE_C_FLAGS_DEBUG}")
endif()

# 若在lib文件夹下配置CMakeLists.txt，则相当于lib为一个单独项目即子项目,TODO 测试是否能解决clion不生成shared的问题,失败
# add_library(static STATIC lib/staticlib.c) # 生成静态库
# add_library(shared SHARED lib/sharedlib.c) # 生成动态库或共享库
# add_library(same SHARED lib/samelib.c)
# set_target_properties(shared PROPERTIES VERION 1.0 SOVERSION 1) #设置库版本及abi版本
# add_library(same_static STATIC lib/same.c)
# set_target_properties(same_static PROPERTIES OUTPUT_NAME "same")
target_link_libraries(main static same) # 将动态库或共享库加入到程序中(使用有文件则加入),动态库使用dlopen则不用加入
add_subdirectory(lib ${CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG})

include(CPack)



# 为了分行确定输出内容
#message("**********************************************************")
#message("-1.PROJECT_NAME = ${PROJECT_NAME}")
#message("0.CMAKE_SOURCE_DIR = ${CMAKE_SOURCE_DIR}")
#message("1.PROJECT_BINARY_DIR = ${PROJECT_BINARY_DIR}")
#message("2.PROJECT_SOURCE _DIR = ${PROJECT_SOURCE_DIR}")
#message("3.CMAKE_CURRENT_SOURCE_DIR = ${CMAKE_CURRENT_SOURCE_DIR}")
#message("4.CMAKE_CURRENT_BINARY_DIR = ${CMAKE_CURRENT_BINARY_DIR}")
#message("4.CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG = ${CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG}")
#message("5.CMAKE_CURRENT_LIST_FILE = ${CMAKE_CURRENT_LIST_FILE}")
#message("6.CMAKE_CURRENT_LIST_LINE = ${CMAKE_CURRENT_LIST_LINE}")
#message("7.CMAKE_MODULE_PATH = ${CMAKE_MODULE_PATH}")
#message("8.CMAKE_SOURCE_DIR = ${CMAKE_SOURCE_DIR}")
#message("9.EXECUTABLE_OUTPUT_PATH = ${EXECUTABLE_OUTPUT_PATH}")
#message("10.LIBRARY_OUTPUT_PATH = ${LIBRARY_OUTPUT_PATH}")
#message("11.PROJECT_NAME = ${PROJECT_NAME}")
#message("12.CMAKE_SOURCE_DIR = ${CMAKE_SOURCE_DIR}")
#message("13.PROJECT_VERSION_MINOR = ${PROJECT_VERSION_MINOR}")
#message("14.PROJECT_VERSION_PATCH = ${PROJECT_VERSION_PATCH}")
#message("15.CMAKE_SYSTEM = ${CMAKE_SYSTEM}")
#message("16.CMAKE_SYSTEM_NAME = ${CMAKE_SYSTEM_NAME}")
#message("17.CMAKE_SYSTEM_VERSION = ${CMAKE_SYSTEM_VERSION}")
#message("18.BUILD_SHARED_LIBS = ${BUILD_SHARED_LIBS}")
#message("19.CMAKE_C_FLAGS = ${CMAKE_C_FLAGS}")
#message("20.CMAKE_CXX_FLAGS = ${CMAKE_CXX_FLAGS}")
#message("21.CMAKE_SYSTEM_PROCESSOR   = ${CMAKE_SYSTEM_PROCESSOR}")
#message("22.CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG = ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}")
#message("23.CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE = ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}")
#message("**********************************************************")