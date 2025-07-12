# general info

cmake_minimum_required(VERSION 3.30)

set(PROJECT_NAME FightClubGame)

project(${PROJECT_NAME} VERSION 1.0.0)

# common options
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

# cpp option

message("${CMAKE_CXX_COMPILER_ID}")

set(CMAKE_CXX_STANDARD 23)

#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /FA")

set(SOURCES Source/main.cpp)
# set(INCLUDES Source/Game/Weapon.h Source/Game/Character.h)

set(MATH_SOURCES Source/Utils/Math.cpp)
set(MATH_INCLUDES Source/Utils/Math.h)

set(DLL_GAME_SOURCES Source/Game/Weapon.cpp Source/Game/Character.cpp)
set(DLL_GAME_INCLUDES Source/Game/Weapon.h Source/Game/Character.h)

# source_group("Source files/Utils" FILES "Source/Utils/Math.cpp")
# source_group("Header files/Utils" FILES "Source/Utils/Math.h")

source_group("Source files/Game" FILES "Source/Game/Weapon.cpp", "Source/Game/Character.cpp")
source_group("Header files/Game" FILES "Source/Game/Weapon.h", "Source/Game/Character.h")

# tergets
add_executable(${PROJECT_NAME} ${SOURCES} ${INCLUDES})

add_library(MathLib STATIC ${MATH_SOURCES} ${MATH_INCLUDES})
add_library(${PROJECT_NAME}Lib SHARED ${DLL_GAME_SOURCES} ${DLL_GAME_INCLUDES})

add_executable(${PROJECT_NAME}TestRunner Source/Tests/main.cpp)

target_compile_definitions(${PROJECT_NAME}Lib PRIVATE _EXPORTING)
target_compile_definitions(${PROJECT_NAME} PUBLIC _IMPORTING)

option(SKIP_GAME_OPT "Skip game" OFF)
if(SKIP_GAME_OPT)
    target_compile_definitions(${PROJECT_NAME} PUBLIC SKIP_GAME)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}Lib)
target_link_libraries(${PROJECT_NAME}Lib PRIVATE MathLib)
target_link_libraries(${PROJECT_NAME}TestRunner PRIVATE ${PROJECT_NAME}Lib)
target_link_libraries(${PROJECT_NAME}TestRunner PRIVATE MathLib)


# includes
#target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Source)
#target_include_directories(${PROJECT_NAME}TestRunner PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Source)
#target_include_directories(${PROJECT_NAME}Lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Source)

set(TARGET ${PROJECT_NAME} ${PROJECT_NAME}TestRunner ${PROJECT_NAME}Lib)

foreach(target IN LISTS TARGET)
    target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Source)
endforeach()


message("CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")

if(WIN32)
    message("Running on Windows")
elseif(LINUX)
    message("Running on Linux")
endif()

if(MSVC)
    message("Use MSVC: ${MSVC_VERSION}")
    message("MSVC toolset: ${MSVC_TOOLSET_VERSION}")
    target_compile_options(${PROJECT_NAME} PRIVATE /FAc)
endif()

#message(FATAL_ERROR "------------${PROJECT_NAME}-------------------")
message("${CMAKE_CXX_FLAGS}")
message("${CMAKE_CXX_FLAGS_DEBUG}")
message("${CMAKE_CXX_FLAGS_RELEASE}")
message("${CMAKE_CONFIGURATION_TYPES}")