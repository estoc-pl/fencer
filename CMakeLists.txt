cmake_minimum_required(VERSION 3.10)
project(fencer C)

set(CMAKE_C_STANDARD 11)

find_package(json-c CONFIG REQUIRED)
find_package(Cargs CONFIG REQUIRED)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(RESOURCES_DIR ${SRC_DIR}/resources)
set(MAIN_DIR ${SRC_DIR}/main)

add_executable(
        fencer
        ${MAIN_DIR}/main.c
        ${MAIN_DIR}/destreza.h
        ${MAIN_DIR}/destreza.c
        ${MAIN_DIR}/exec_stack.h
        ${MAIN_DIR}/exec_stack.c
)


file(GLOB_RECURSE RES_FILES CONFIGURE_DEPENDS "${RESOURCES_DIR}/*")

add_custom_command(
        OUTPUT "${CMAKE_BINARY_DIR}/.resources.stamp"
        COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/resources"
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${RESOURCES_DIR}" "${CMAKE_BINARY_DIR}/resources"
        COMMAND ${CMAKE_COMMAND} -E touch "${CMAKE_BINARY_DIR}/.resources.stamp"
        DEPENDS ${RES_FILES}
        COMMENT "Sync resources beside executable"
        VERBATIM
)

add_custom_target(stage_resources DEPENDS "${CMAKE_BINARY_DIR}/.resources.stamp")
add_dependencies(fencer stage_resources)


target_link_libraries(fencer PRIVATE json-c::json-c)
target_link_libraries(fencer PRIVATE cargs)