cmake_minimum_required(VERSION 3.10)
project(fencer C)

set(CMAKE_C_STANDARD 11)

find_package(json-c CONFIG REQUIRED)
find_package(Cargs CONFIG REQUIRED)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(RESOURCES_DIR ${SRC_DIR}/resources)
set(MAIN_DIR ${SRC_DIR}/main)

add_library(
        fencer_core STATIC
        ${MAIN_DIR}/core/arithmetics/int.c
        ${MAIN_DIR}/core/errors.c
)
target_include_directories(fencer_core PUBLIC ${MAIN_DIR}/core)

add_executable(
        fencer
        ${MAIN_DIR}/main.c
        ${MAIN_DIR}/destreza/destreza.h ${MAIN_DIR}/destreza/destreza.c
        ${MAIN_DIR}/destreza/destreza_version.h ${MAIN_DIR}/destreza/destreza_version.c
        ${MAIN_DIR}/destreza/destreza_errors.h ${MAIN_DIR}/destreza/destreza_errors.c
        ${MAIN_DIR}/exec_stack.h ${MAIN_DIR}/exec_stack.c
        ${MAIN_DIR}/code_space/code_space.h ${MAIN_DIR}/code_space/code_space.c
        ${MAIN_DIR}/code_space/code_space_errors.h ${MAIN_DIR}/code_space/code_space_errors.c
        ${MAIN_DIR}/commands/arithmetic.h ${MAIN_DIR}/commands/arithmetic.c
        ${MAIN_DIR}/commands/int.h ${MAIN_DIR}/commands/int.c
        ${MAIN_DIR}/commands/command.h ${MAIN_DIR}/commands/command.c
)

target_link_libraries(fencer PRIVATE fencer_core)
target_link_libraries(fencer PRIVATE json-c::json-c)
target_link_libraries(fencer PRIVATE cargs)


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


find_package(unofficial-cunit CONFIG REQUIRED)

set(TESTS_DIR ${CMAKE_SOURCE_DIR}/tests)
set(TESTS_MAIN_DIR ${TESTS_DIR}/main)

add_executable(
        fencer_tests
        ${TESTS_MAIN_DIR}/main.c
        ${TESTS_MAIN_DIR}/core/arithmetics/int_add.test.h ${TESTS_MAIN_DIR}/core/arithmetics/int_add.test.c
        ${TESTS_MAIN_DIR}/core/arithmetics/int_multiply.test.h ${TESTS_MAIN_DIR}/core/arithmetics/int_multiply.test.c
        ${TESTS_MAIN_DIR}/core/arithmetics/int_divide.test.h ${TESTS_MAIN_DIR}/core/arithmetics/int_divide.test.c
)

target_link_libraries(fencer_tests PRIVATE fencer_core)
target_link_libraries(fencer_tests PRIVATE unofficial::cunit::cunit)