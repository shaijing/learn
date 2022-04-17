cmake_minimum_required(VERSION 3.0.0)
project(learn VERSION 0.1.0)


set(CMAKE_C_STANDARD 99)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/bin)
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/bin)
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/debug/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/debug/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/debug)
set(CMAKE_BUILD_TYPE Debug CACHE STRING "set build type to debug")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0 -Wall -g -ggdb -ldl")  # Debug模式下的编译指令
set(CMAKE_C_FLAGS "-std=c99 -ldl")
message("CMAKE_C_FLAGS_DEBUG:${CMAKE_C_FLAGS_DEBUG}")
set(CMAKE_VERBOSE_MAKEFILEON ON)

add_subdirectory(lib ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}) 
# include_directories(lib)
link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY}) #添加动态连接库的路径
include(CTest)
enable_testing()

add_executable(main main.c 
headers/chapter_10.h sources/chapter_10.c

)
#迁入子目录lib CMakeLists.txt
# add_library(static STATIC lib/staticlib.c) # 生成静态库
# add_library(shared SHARED lib/sharedlib.c) # 生成动态库或共享库
# add_library(same SHARED lib/same.c)
# add_library(same_static STATIC lib/same.c)
# set_target_properties(same_static PROPERTIES OUTPUT_NAME "same")



#target_link_libraries(main ${CMAKE_CURRENT_BINARY_DIR}/lib/libsharedlib.so)
target_link_libraries(main shared static same) # 将动态库或共享库加入到程序中


#SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")         # Release模式下的编译指令

#SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../bin)       #设置可执行文件的输出目录
 
#SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../lib)           #设置库文件的输出目录
 
 
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/bin)   
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/../bin) 

#上面两条语句分别设置了Debug版本和Release版本可执行文件的输出目录,
#一旦设置上面的属性,在任何环境下生成的可执行文件都将直接放在你所设置的目录.
#四. set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/../lib)    
#    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/../lib) 
#上面两条语句分别设置了Debug版本和Release版本库文件的输出目录,
#一旦设置上面的属性,在任何环境下生成的库文件都将直接放在你所设置的目录.
include(CPack)
# 为了分行确定输出内容
# message("**********************************************************")
# message("0.CMAKE_SOURCE_DIR = ${CMAKE_SOURCE_DIR}")
# message("1.PROJECT_BINARY_DIR = ${PROJECT_BINARY_DIR}")
# message("2.PROJECT_SOURCE _DIR = ${PROJECT_SOURCE_DIR}")
# message("3.CMAKE_CURRENT_SOURCE_DIR = ${CMAKE_CURRENT_SOURCE_DIR}")
# message("4.CMAKE_CURRRENT_BINARY_DIR = ${CMAKE_CURRRENT_BINARY_DIR}")
# message("5.CMAKE_CURRENT_LIST_FILE = ${CMAKE_CURRENT_LIST_FILE}")
# message("6.CMAKE_CURRENT_LIST_LINE = ${CMAKE_CURRENT_LIST_LINE}")
# message("7.CMAKE_MODULE_PATH = ${CMAKE_MODULE_PATH}")
# message("8.CMAKE_SOURCE_DIR = ${CMAKE_SOURCE_DIR}")
# message("9.EXECUTABLE_OUTPUT_PATH = ${EXECUTABLE_OUTPUT_PATH}")
# message("10.LIBRARY_OUTPUT_PATH = ${LIBRARY_OUTPUT_PATH}")
# message("11.PROJECT_NAME = ${PROJECT_NAME}")
# message("12.PROJECT_VERSION_MAJOR = ${PROJECT_VERSION_MAJOR}")
# message("13.PROJECT_VERSION_MINOR = ${PROJECT_VERSION_MINOR}")
# message("14.PROJECT_VERSION_PATCH = ${PROJECT_VERSION_PATCH}")
# message("15.CMAKE_SYSTEM = ${CMAKE_SYSTEM}")
# message("16.CMAKE_SYSTEM_NAME = ${CMAKE_SYSTEM_NAME}")
# message("17.CMAKE_SYSTEM_VERSION = ${CMAKE_SYSTEM_VERSION}")
# message("18.BUILD_SHARED_LIBS = ${BUILD_SHARED_LIBS}")
# message("19.CMAKE_C_FLAGS = ${CMAKE_C_FLAGS}")
# message("20.CMAKE_CXX_FLAGS = ${CMAKE_CXX_FLAGS}")
# message("21.CMAKE_SYSTEM_PROCESSOR   = ${CMAKE_SYSTEM_PROCESSOR}")
# # 为了分行确定输出内容
# message("**********************************************************")