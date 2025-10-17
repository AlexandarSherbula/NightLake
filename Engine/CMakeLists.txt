project(Engine)

# Base output path
set(OUTPUT_DIR "${CMAKE_BINARY_DIR}/bin/${PROJECT_NAME}/${CMAKE_SYSTEM_NAME}/$<CONFIG>")

# These apply to all targets created afterwards
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR})

file(
    GLOB_RECURSE ENGINE_SRC
    "Source/*.cpp"
    "Source/*.hpp"
)

add_library(Engine STATIC ${ENGINE_SRC})
target_compile_features(Engine PRIVATE cxx_std_20)

target_precompile_headers(Engine PRIVATE
    "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_SOURCE_DIR}/Engine/Source/aio_pch.hpp>"
)

#make folders visible in IDE
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${ENGINE_SRC})

if(WIN32)
    target_compile_definitions(Engine PUBLIC AIO_WINDOWS)
elseif(UNIX)
    target_compile_definitions(Engine PUBLIC AIO_LINUX)
endif()

target_compile_definitions(Engine PUBLIC
    $<$<CONFIG:Debug>:AIO_DEBUG>
    $<$<CONFIG:Release>:AIO_RELEASE>
    $<$<CONFIG:Dist>:AIO_DIST>
)

target_include_directories(Engine PUBLIC ${CMAKE_SOURCE_DIR}/Engine/Source)
target_include_directories(Engine PUBLIC ${CMAKE_SOURCE_DIR}/Engine/vendor/spdlog/include)
target_include_directories(Engine PUBLIC ${CMAKE_SOURCE_DIR}/Engine/vendor/SDL/include)
target_include_directories(Engine PUBLIC ${CMAKE_SOURCE_DIR}/Engine/vendor/stb/include)
target_include_directories(Engine PUBLIC ${CMAKE_SOURCE_DIR}/Engine/vendor/glm)

# SDL setup
set(SDL_SHARED OFF CACHE BOOL "" FORCE)  
set(SDL_STATIC ON CACHE BOOL "" FORCE) # build static SDL
add_subdirectory(vendor/SDL EXCLUDE_FROM_ALL)
target_link_libraries(Engine PRIVATE SDL3::SDL3)

# GLAD setup
set(GLAD_SRC
    "vendor/glad/include/glad/glad.h"
    "vendor/glad/src/glad.c"
)

add_library(glad STATIC ${GLAD_SRC})
target_include_directories(glad PUBLIC ${CMAKE_SOURCE_DIR}/Engine/vendor/glad/include)
target_link_libraries(Engine PRIVATE glad)

if (WIN32)
    target_link_libraries(Engine PRIVATE DXGI D3D11)
	target_link_libraries(Engine PRIVATE dwmapi)
endif()

# ImGui Setup
add_subdirectory(vendor/imgui EXCLUDE_FROM_ALL)
target_link_libraries(Engine PRIVATE imgui)

# Put SDL submodules under Dependencies folder
foreach(t SDL3-static SDL3_test SDL3_Headers SDL_uclibc)
    if (TARGET ${t})
        set_target_properties(${t} PROPERTIES FOLDER "Dependencies")
    endif()
endforeach()

set_target_properties(glad PROPERTIES FOLDER "Dependencies")
set_target_properties(imgui PROPERTIES FOLDER "Dependencies")
