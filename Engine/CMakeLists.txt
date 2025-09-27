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
    "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_SOURCE_DIR}/Engine/Source/nle_pch.hpp>"
)

#make folders visible in IDE
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${ENGINE_SRC})

if(WIN32)
    target_compile_definitions(Engine PUBLIC NLE_WINDOWS)
elseif(UNIX)
    target_compile_definitions(Engine PUBLIC NLE_LINUX)
endif()

target_compile_definitions(Engine PUBLIC
    $<$<CONFIG:Debug>:NLK_DEBUG>
    $<$<CONFIG:Release>:NLK_RELEASE>
    $<$<CONFIG:Dist>:NLK_DIST>
)

target_include_directories(Engine PUBLIC ${CMAKE_SOURCE_DIR}/Engine/Source)
