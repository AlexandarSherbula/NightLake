project(Sandbox)

# Base output path
set(OUTPUT_DIR "${CMAKE_BINARY_DIR}/bin/${PROJECT_NAME}/${CMAKE_SYSTEM_NAME}/$<CONFIG>")

# These apply to all targets created afterwards
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR})

file(
    GLOB_RECURSE SANDBOX_SRC
    "src/*.cpp"
    "src/*.hpp"
)

add_executable(Sandbox ${SANDBOX_SRC})
target_compile_features(Sandbox PRIVATE cxx_std_20)

target_link_libraries(Sandbox PRIVATE Engine)
