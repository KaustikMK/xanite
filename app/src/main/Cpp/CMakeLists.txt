cmake_minimum_required(VERSION 3.18.6)
project("Xanite")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Android NDK log + native
find_library(log-lib log)
find_library(android-lib android)
find_library(vulkan-lib vulkan)

if (CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64")
    add_subdirectory(libadrenotools)
else()
    add_library(adrenotools INTERFACE)
endif()

include_directories(${ANDROID_NDK}/sources/third_party/vulkan/include)

# Native **
add_library(${CMAKE_PROJECT_NAME} SHARED
    native-lib.cpp
)

target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE USE_VULKAN=1)

target_link_libraries(${CMAKE_PROJECT_NAME}
    ${log-lib}
    ${android-lib}
    ${vulkan-lib}
    adrenotools
)
