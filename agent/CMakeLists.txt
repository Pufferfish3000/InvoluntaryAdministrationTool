set(AGENT "agent_x86_64")

set (RELEASE_FLAGS -Wall -Werror -Wextra -Wpedantic -Wconversion -Wunreachable-code -Werror -Os)
set (DEBUG_FLAGS -Wall -Werror -Wextra -Wpedantic -Wconversion -Wunreachable-code -Werror -g -O0)

add_executable(${AGENT})
target_include_directories(${AGENT} PUBLIC ${CMAKE_SOURCE_DIR}/agent/include)

add_subdirectory(src/)
add_subdirectory(core/)

if(NDEBUG)
target_compile_options(${AGENT} PUBLIC ${RELEASE_FLAGS})
target_compile_definitions(${AGENT} PUBLIC NDEBUG)
else()
target_compile_options(${AGENT} PUBLIC ${DEBUG_FLAGS})
endif(NDEBUG)
unset(NDEBUG)

add_library(bearssl STATIC IMPORTED)
set_target_properties(bearssl PROPERTIES
    IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/external/bearssl/build/libbearssl.a"
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/external/bearssl/inc"
)
target_link_libraries(${AGENT} PRIVATE bearssl)
