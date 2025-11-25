set(PROJECT_NAME DoodleJumpGame)

add_executable(${PROJECT_NAME} main.cpp)

set(SOURCE_FILES
    DoodleJump.cpp
    DoodleJump.h
    Player.cpp
    Player.h
    Types.h
    PlatformManager.cpp
    PlatformManager.h
)
add_library(${PROJECT_NAME}Lib ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}Lib)
target_link_libraries(${PROJECT_NAME}Lib raylib MathLib)

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER ${PROJECT_NAME})
set_target_properties(${PROJECT_NAME}Lib PROPERTIES FOLDER ${PROJECT_NAME})

target_sources(${PROJECT_NAME}Lib PRIVATE pch.cpp pch.h)
# вместо set_source_files_properties(... "/Ycpch.h")
target_precompile_headers(${PROJECT_NAME}Lib PRIVATE pch.h)
