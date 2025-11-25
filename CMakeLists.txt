# general info

cmake_minimum_required(VERSION 3.28)

set(PROJECT_NAME CMakeLearning)

project(${PROJECT_NAME} VERSION 1.0.0)

include(${CMAKE_BINARY_DIR}/conan_toolchain.cmake)

set(VS_STARTUP_PROJECT_NAME FightClubGame)

# common options
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${VS_STARTUP_PROJECT_NAME})

# cpp option

message("${CMAKE_CXX_COMPILER_ID}")

set(CMAKE_CXX_STANDARD 23)

#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /FA")


#find package

find_package(nlohmann_json)
find_package(cpr)
find_package(GTest)
find_package(raylib)

include_directories(Source)


add_subdirectory(Source/ChuckNorrisJokes)
add_subdirectory(Source/RaylibTest)
add_subdirectory(Source/Utils)
add_subdirectory(Source/FightClubGame)
add_subdirectory(Source/DoodleJumpGame)


# includes
#target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Source)
#target_include_directories(${PROJECT_NAME}TestRunner PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Source)
#target_include_directories(${PROJECT_NAME}Lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Source)

include(${CMAKE_SOURCE_DIR}/Automation/CMAKE/CMakeHelpers.cmake)
system_info()