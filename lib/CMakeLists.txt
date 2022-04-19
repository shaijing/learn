message(STATUS "Enter library project")
include_directories(.)
cmake_minimum_required(VERSION 3.20.0)
project(library VERSION 0.0.1)
add_library(static STATIC staticlib.c)
add_library(shared SHARED sharedlib.c)
add_library(same SHARED samelib.c)
# set_target_properties(shared PROPERTIES VERION 1.0 SOVERSION 1) #设置库版本及abi版本

# add_library(same_static STATIC same.c) set_target_properties(same_static
# PROPERTIES OUTPUT_NAME "same")
message(STATUS "Finish building libraries")
message("library's install path:${CMAKE_INSTALL_PREFIX}")
install(
  TARGETS shared
  CONFIGURATIONS Debug
  LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/debug/bin
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_PREFIX}/debug/include # 头文件安装路径
)
install(
  TARGETS shared
  CONFIGURATIONS Release
  # 安装正常
  # LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/${MAIN_PROJECIT_NAME}/bin
  # 安装，打包正常
  LIBRARY DESTINATION ${MAIN_PROJECIT_NAME}/bin
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_PREFIX}/include # 头文件安装路径
)
message(STATUS "Exit library project")
