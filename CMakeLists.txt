cmake_minimum_required(VERSION 3.20.0)
project(
  learn
  VERSION 0.0.1
  DESCRIPTION "C AND CXX LEARN"
  HOMEPAGE_URL "www.etamin.xyz"
  LANGUAGES C)
#方式一:直接包含路径及.cmake文件
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/demo.cmake)
 
#方式二:先设置CMAKE_MODULE_PATH变量，这个变量是定义.cmake文件的搜索目录的
# set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/)
# include(test)  ##不要写成test.cmake
 
print_message()

# ##############################################################################
# Normal Configure
# ##############################################################################
set(CMAKE_C_STANDARD 99)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CMAKE_BUILD_TYPE
    Debug
    CACHE STRING "set build type to debug")
# set(CMAKE_BUILD_TYPE "Debug”)
set(CMAKE_VERBOSE_MAKEFILEON ON)
# include(${CMAKE_CURRENT_SOURCE_DIR}/vInstallCpack.cmake)

# ##############################################################################
# Install Pack Configure
# ##############################################################################
SET(CMAKE_INSTALL_PREFIX "/home/user-yu/test")
# Install Configurations 7Z(.7z) 7Zzip(.7z) TBZ2(tar.bz2) TGZ(.tar.gz)
# TXZ(.tar.xz) TZ(.tar.Z) ZIP(.zip) 设置生成的安装包名字
set(CPACK_PACKAGE_NAME "learn")
# 设置支持指定安装目录的控制为 ON
set(CPACK_SET_DESTDIR ON)
set(CPACK_OUTPUT_FILE_PREFIX "/home/user-yu/test")
# 设置打包压缩包的内部目录前缀
set(CPACK_INSTALL_PREFIX "./")
# 这是生成的安装的版本号信息
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
# 设置 group 名字
set(CPACK_RPM_PACKAGE_GROUP "learn")
# 设置 vendor 名字
set(CPACK_PACKAGE_VENDOR "learn")
# 设置维护者信息
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "YuLing")
# 设置 license 信息
set(CPACK_RPM_PACKAGE_LICENSE "Apache 2.0 + Common Clause 1.0")
# 设置打包方式
set(CPACK_GENERATOR "TGZ")
# 变量的设置需要在include(CPack)语句
include(CPack)

# unsused set(CMAKE_INSTALL_RPATH ${ORIGIN}/bin) message("CMAKE_INSTALL_RPATH =
# ${CMAKE_INSTALL_RPATH}") add_compile_options命令可以为所有编译器配置编译选项（同时对多个编译器生效）
# add_compile_options(-Wall -Wextra -pedantic -Werror) 指定头文件搜索路径
# include_directories(lib) 指定lib目录
# link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY}) #添加自定义动态连接库的路径

# ##############################################################################
# Compiler Configure
# ##############################################################################
if(CMAKE_BUILD_TYPE AND (CMAKE_BUILD_TYPE STREQUAL "Debug"))
  # DEBUG模式下的编译指令
  # CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG在arch-linux+gcc11.2+cmake3.23.1无效，main会出现在build下
  set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/debug/${PROJECT_NAME})
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG
      ${CMAKE_CURRENT_BINARY_DIR}/debug//${PROJECT_NAME}/bin)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG
      ${CMAKE_CURRENT_BINARY_DIR}/debug/${PROJECT_NAME}/bin)
  set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0 -Wall -g -ggdb -ldl")
  # 添加子项目，将自动找到子目录中的CMakeLists.txt
  add_subdirectory(lib ${CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG})
  message("Debug mode:${CMAKE_C_FLAGS_DEBUG}")
elseif(CMAKE_BUILD_TYPE AND (CMAKE_BUILD_TYPE STREQUAL "Release"))
  # RELEASE模式下的编译指令
  set(EXECUTABLE_OUTPUT_PATH
      ${CMAKE_CURRENT_BINARY_DIR}/release/${PROJECT_NAME})
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE
      ${CMAKE_CURRENT_BINARY_DIR}/release/${PROJECT_NAME}/bin)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE
      ${CMAKE_CURRENT_BINARY_DIR}/release/${PROJECT_NAME}/bin)
  set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Wall -O3 -ldl")
  # 添加子项目，将自动找到子目录中的CMakeLists.txt
  add_subdirectory(lib ${CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE})
  message("Release mode:${CMAKE_C_FLAGS_RELEASE}")
else()
  set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/debug/${PROJECT_NAME})
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG
      ${CMAKE_CURRENT_BINARY_DIR}/debug//${PROJECT_NAME}/bin)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG
      ${CMAKE_CURRENT_BINARY_DIR}/debug/${PROJECT_NAME}/bin)
  set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0 -Wall -g -ggdb -ldl")
  # 添加子项目，将自动找到子目录中的CMakeLists.txt
  add_subdirectory(lib ${CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG})
  message("Default Mode(Debug):${CMAKE_C_FLAGS_DEBUG}")
endif()

# ##############################################################################
# Build
# ##############################################################################
# GLOB 表示不递归 GLOB_RECURSE表示执行递归查找，查找目录下所有符合指定正则表达式的文件。
file(GLOB SRC_TOP ${PROJECT_SOURCE_DIR}/*.c)
file(GLOB_RECURSE SRC_SUBF ${PROJECT_SOURCE_DIR}/sources/*.c
     ${PROJECT_SOURCE_DIR}/headers/*.h)
set(libbb CMAKE_L)
set(ALL_SRC ${SRC_TOP} ${RC_SUB})

add_executable(main ${ALL_SRC})
# 设置可执行文件到相对路径寻找库
set_target_properties(main PROPERTIES LINK_FLAGS "-Wl,-rpath,./bin")

# 将动态库或共享库加入到程序中(使用有文件头则加入),动态库使用dlopen则不用加入
target_link_libraries(main static same)
add_dependencies(main static)

# ##############################################################################
# Test Configure
# ##############################################################################
option(CMAKE_TEMPLATE_ENABLE_TEST "Whether to enable unit tests" OFF)
if(CMAKE_TEMPLATE_ENABLE_TEST)
  message(STATUS "Unit tests enabled")
  enable_testing()
  add_executable(test_add test/test_add.c)
  add_test(NAME test_add COMMAND test_add 10 24 34)
endif()

# ##############################################################################
# Install Pack
# ##############################################################################
find_library(libvar shared ${CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG})
if(${libvar} STREQUAL "libvar-NOTFOUND")
  message(STATUS"required shared library but not found!")
else()
  message(STATUS "library found in ${libvar}")
endif()

if(CMAKE_BUILD_TYPE AND (CMAKE_BUILD_TYPE STREQUAL "Debug"))
  install(
    TARGETS main same static
    CONFIGURATIONS Debug
    RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/debug/
    LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/debug/bin
    ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/debug/bin
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_PREFIX}/debug/include # 头文件安装路径
  )
else()
  install(
    TARGETS main same static
    CONFIGURATIONS Release
    RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/release/
    LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/release/bin
    ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/release/bin
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_PREFIX}/release/include # 头文件安装路径
  )
endif()
