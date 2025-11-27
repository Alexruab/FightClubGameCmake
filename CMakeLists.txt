# general info

cmake_minimum_required(VERSION 3.28)

#setup conan profile
set(PROFILE_PATH_Windows_Release "${CMAKE_CURRENT_SOURCE_DIR}/ConanProfiles/WindowsRelease")
set(PROFILE_PATH_Windows_Debug "${CMAKE_CURRENT_SOURCE_DIR}/ConanProfiles/WindowsDebug")
set(PROFILE_PATH_Linux_Release "${CMAKE_CURRENT_SOURCE_DIR}/ConanProfiles/linuxRelease")
set(PROFILE_PATH_Linux_Debug "${CMAKE_CURRENT_SOURCE_DIR}/ConanProfiles/linuxDebug")

set(CURRENT_PROFILE "PROFILE_PATH_${CMAKE_HOST_SYSTEM_NAME}_${CMAKE_BUILD_TYPE}")
message(STATUS "Set conan profile: ${CURRENT_PROFILE}")

if(DEFINED ${CURRENT_PROFILE})
    set(CONAN_PROFILE "${${CURRENT_PROFILE}}")
    message(STATUS "Using conan profile: ${CONAN_PROFILE}")
else()
    message(FATAL_ERROR "Unsupported config: ${CURRENT_PROFILE}")
endif()

include(${CMAKE_SOURCE_DIR}/Automation/CMAKE/CMakeHelpers.cmake)
setup_conan(${CONAN_PROFILE} ${CONAN_PROFILE})

set(PROJECT_NAME CMakeLearning)

project(${PROJECT_NAME} VERSION 1.0.0)

#include(${CMAKE_BINARY_DIR}/conan_toolchain.cmake)

set(VS_STARTUP_PROJECT_NAME FightClubGame)

# common options
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${STARTUP_PROJECT_NAME})

# cpp option
message("${CMAKE_CXX_COMPILER_ID}")
set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /FA")

#find package
#find_package(nlohmann_json REQUIRED)
find_package(GTest REQUIRED)
find_package(raylib)

include_directories(Source)

add_subdirectory(Source/RaylibTest)
add_subdirectory(Source/Utils)
add_subdirectory(Source/FightClubGame)
add_subdirectory(Source/DoodleJumpGame)

# includes
#target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Source)
#target_include_directories(${PROJECT_NAME}TestRunner PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Source)
#target_include_directories(${PROJECT_NAME}Lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Source)

system_info()