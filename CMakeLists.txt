cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME "videoToASCII")

project("${PROJECT_NAME}" VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SRC_DIR "src")
file(GLOB SRC_FILES "${SRC_DIR}/*.cpp")

add_executable(${PROJECT_NAME} ${SRC_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE headers includes/usr/include)
target_compile_options(${PROJECT_NAME} PRIVATE -O3)

find_package(PkgConfig REQUIRED)

pkg_check_modules(DEPENDENCIES REQUIRED opencv4)

# set(DEPENDENCIES_LIBRARIES ${DEPENDENCIES_LIBRARIES} -static)

target_include_directories(${PROJECT_NAME} PRIVATE ${DEPENDENCIES_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME}  ${DEPENDENCIES_LIBRARIES})

add_custom_target(run
COMMAND ${PROJECT_NAME}
DEPENDS ${PROJECT_NAME}
WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
