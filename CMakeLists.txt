project(fontio)

cmake_minimum_required(VERSION 2.8)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11")

if(CMAKE_BUILD_TYPE MATCHES "Debug")
    message(STATUS "Debug mode")

    add_definitions(
        -DDEBUG=1
    )
endif()

include_directories(
    ./src/
)

# Main library
file(GLOB LIBRARY_LIST
    src/${PROJECT_NAME}/*.?pp
    src/${PROJECT_NAME}/logic/*.?pp
    src/${PROJECT_NAME}/logic/cff/*.?pp
    src/${PROJECT_NAME}/logic/otf/*.?pp
    src/${PROJECT_NAME}/logic/type2/*.?pp
    src/${PROJECT_NAME}/model/*.?pp
    src/${PROJECT_NAME}/model/cff/*.?pp
    src/${PROJECT_NAME}/model/otf/*.?pp
    src/${PROJECT_NAME}/model/type2/*.?pp
)

# Library
add_library(${PROJECT_NAME} ${LIBRARY_LIST})

# Google tests
find_package(GTest)
if(GTEST_FOUND)
    file(GLOB_RECURSE UNITTEST_LIST src/${PROJECT_NAME}_tests/*)
    enable_testing()
    add_executable(${PROJECT_NAME}_tests ${UNITTEST_LIST})
    target_link_libraries(${PROJECT_NAME}_tests ${PROJECT_NAME} ${GTEST_MAIN_LIBRARIES} ${GTEST_LIBRARIES})

    # Copy test files to build directory
    add_custom_command(TARGET ${PROJECT_NAME}_tests PRE_BUILD
                       COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/test_data $<TARGET_FILE_DIR:${PROJECT_NAME}_tests>/test_data)
endif()
