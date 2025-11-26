macro(system_info)
    message("============= System Info =============")

    message("CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")

    if(WIN32)
        message("Running on Windows")
    elseif(LINUX)
        message("Running on Linux")
    endif()

    if(MSVC)
        message("Use MSVC: ${MSVC_VERSION}")
        message("MSVC toolset: ${MSVC_TOOLSET_VERSION}")
        #target_compile_options(${PROJECT_NAME} PRIVATE /FAc)
    endif()

    #message(FATAL_ERROR "------------${PROJECT_NAME}-------------------")
    message("${CMAKE_CXX_FLAGS}")
    message("${CMAKE_CXX_FLAGS_DEBUG}")
    message("${CMAKE_CXX_FLAGS_RELEASE}")
    message("${CMAKE_CONFIGURATION_TYPES}")

    message("=======================================")
endmacro()

function(setup_precompiled_headers TARGET PCH_SOURCE PCH_HEADER SOURCE_FILES)

    target_sources(${TARGET} PRIVATE ${PCH_HEADER} ${PCH_SOURCE})
    # вместо set_source_files_properties(... "/Ycpch.h")
    #target_precompile_headers(${PROJECT_NAME}Lib PRIVATE pch.h)

    set_source_files_properties(${PCH_SOURCE} PROPERTIES COMPILE_FLAGS "/Yc${PCH_HEADER}")

    foreach(SOURCE_FILE ${SOURCE_FILES})
        if(${SOURCE_FILE} MATCHES "\\.cpp$")
            set_source_files_properties(${SOURCE_FILE} PROPERTIES COMPILE_FLAGS "/Yu${PCH_HEADER}")
        endif()
    endforeach()

    target_compile_options(${PROJECT_NAME}Lib PRIVATE "/FI${PCH_HEADER}")
    #set_source_files_properties(DoodleJump.cpp PROPERTIES COMPILE_FLAGS "/Ycpch.h")
    
endfunction()

macro(setup_conan HOST_PROFILE BUILD_PROFILE)
    set(CMAKE_CONAN_PATH "${CMAKE_BINARY_DIR}/conan_provider.cmake")
    if(NOT EXISTS ${CMAKE_CONAN_PATH})
        message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
        file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/refs/heads/develop2/conan_provider.cmake" "${CMAKE_CONAN_PATH}")
    endif()

    set(CMAKE_PROJECT_TOP_LEVEL_INCLUDES ${CMAKE_CONAN_PATH})
    set(CONAN_HOST_PROFILE "${HOST_PROFILE}")
    set(CONAN_BUILD_PROFILE "${BUILD_PROFILE}")
    
endmacro()

