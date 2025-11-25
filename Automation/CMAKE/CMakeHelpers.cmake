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