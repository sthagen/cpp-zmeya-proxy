cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

# ---- Project ----

project(zmeya_proxy LANGUAGES CXX)

option(ZMEYA_EXAMPLES "whether or not to build the examples" ON)

# ---- Fetch CPM ----

set(CPM_DOWNLOAD_VERSION 0.27.2)
set(CPM_DOWNLOAD_LOCATION "${CMAKE_BINARY_DIR}/cmake/CPM_${CPM_DOWNLOAD_VERSION}.cmake")

if(NOT (EXISTS ${CPM_DOWNLOAD_LOCATION}))
    message(STATUS "Downloading CPM.cmake v${CPM_DOWNLOAD_VERSION}")
    file(DOWNLOAD https://github.com/TheLartians/CPM.cmake/releases/download/v${CPM_DOWNLOAD_VERSION}/CPM.cmake ${CPM_DOWNLOAD_LOCATION})
endif()

include(${CPM_DOWNLOAD_LOCATION})

# ---- Add dependencies via CPM ----
# See https://github.com/TheLartians/CPM.cmake for details and examples

CPMAddPackage(
  NAME zmeya
  VERSION 2021.09  
  # not using the repo as it takes longer to clone
  URL https://github.com/sthagen/Zmeya/archive/refs/tags/2021.09.zip
  URL_HASH SHA256=7caffa04dcabfe3d013ffdfe9c0ad2e08132de710b3d1163df0a1f28baeaf11a
)

if(zmeya_ADDED)
#   add_library(zmeya INTERFACE)
#   target_include_directories(zmeya INTERFACE ${zmeya_SOURCE_DIR})
    execute_process(COMMAND ${CMAKE_COMMAND} -E copy_if_different "${zmeya_SOURCE_DIR}/Zmeya.h" "${zmeya_SOURCE_DIR}/zmeya.h")
endif()

CPMAddPackage(
  NAME doctest
  GITHUB_REPOSITORY sthagen/doctest
  GIT_TAG 2020.12
)

# ---- Create binary ----

add_executable(zmeya_test main.cpp)
target_link_libraries(zmeya_test doctest)
set_target_properties(zmeya_test PROPERTIES CXX_STANDARD 17)

# ---- Enable testing ----

enable_testing() 
add_test(zmeya_test zmeya_test)

# ---- HACK A DID ACK ----

execute_process(COMMAND ${CMAKE_COMMAND} -E copy_if_different "examples/basic.zm" "${CMAKE_BINARY_DIR}/examples/basic.zm")

# ---- Create the examples ----

message(STATUS "Note the fetched includes are taken from below: ${FETCHCONTENT_BASE_DIR}")
if (ZMEYA_EXAMPLES )
    macro(zmeya_examples EXAMPLENAME)
        add_executable(${EXAMPLENAME} ${ARGN})
        set_target_properties(${EXAMPLENAME} PROPERTIES FOLDER examples)
        set_target_properties(${EXAMPLENAME} PROPERTIES CXX_STANDARD 17)
        target_include_directories(${EXAMPLENAME} PUBLIC "${FETCHCONTENT_BASE_DIR}/Zmeya-src")
        add_test(NAME ${EXAMPLENAME} COMMAND ${EXAMPLENAME})
    endmacro()
    add_subdirectory(examples)
endif()
