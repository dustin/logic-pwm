# setup workspace
cmake_minimum_required(VERSION 3.11)
include(FetchContent)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

# global setup
project("PWM Analyzer")
add_definitions( -DLOGIC2 )
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# get sdk
FetchContent_Declare(analyzer_sdk GIT_REPOSITORY https://github.com/saleae/AnalyzerSDK.git GIT_TAG master GIT_SHALLOW True GIT_PROGRESS True)
FetchContent_MakeAvailable(analyzer_sdk)
message("Analyzer sdk at " ${analyzer_sdk_SOURCE_DIR})
include(${analyzer_sdk_SOURCE_DIR}/AnalyzerSDKConfig.cmake)

# setup project
file(GLOB_RECURSE srcs_cpp source/*.cpp)
file(GLOB_RECURSE srcs_h source/*.h)
add_library("PWMAnalyzer" MODULE ${srcs_cpp} ${srcs_h})
target_link_libraries("PWMAnalyzer" PRIVATE Saleae::AnalyzerSDK)

