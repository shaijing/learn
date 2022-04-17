# 若在lib文件夹下配置CMakeLists.txt，则相当于lib为一个单独项目
# 将其和主工程连接
include_directories(.)
cmake_minimum_required(VERSION 3.20.0)
project(lib VERSION 0.0.1)
add_library(static STATIC staticlib.c)
add_library(shared SHARED sharedlib.c)
add_library(same SHARED samelib.c)
# SET_TARGET_PROPERTIES(shared PROPERTIES VERION 1.0 SOVERSION 1) #设置库版本及abi版本

#add_library(same_static STATIC same.c)
#set_target_properties(same_static PROPERTIES OUTPUT_NAME "same")