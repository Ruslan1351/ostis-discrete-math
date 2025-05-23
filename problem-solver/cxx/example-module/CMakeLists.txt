file(GLOB SOURCES CONFIGURE_DEPENDS
        "*.cpp" "*.hpp"
        "agent/*.cpp" "agent/*.hpp"
        "keynodes/*.hpp"
)

add_library(example-module SHARED ${SOURCES})
target_link_libraries(example-module
        LINK_PUBLIC sc-machine::sc-memory
)
target_include_directories(example-module
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
set_target_properties(example-module PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${SC_EXTENSIONS_DIRECTORY})

if(${SC_CLANG_FORMAT_CODE})
    target_clangformat_setup(example-module)
endif()

if(${SC_BUILD_TESTS})
    set(EXAMPLE_MODULE_SRC_PATH ${CMAKE_CURRENT_SOURCE_DIR})
    add_subdirectory(test)
endif()
