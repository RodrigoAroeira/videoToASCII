cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME "videoToASCII")

project("${PROJECT_NAME}" VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SRC_DIR "src")
file(GLOB SRC_FILES "${SRC_DIR}/*.cpp")

add_executable(${PROJECT_NAME} ${SRC_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE headers)

find_package(OpenCV REQUIRED COMPONENTS core videoio imgproc)

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})

add_custom_target(
  run
  COMMAND ${PROJECT_NAME}
  DEPENDS ${PROJECT_NAME}
  WORKING_DIRECTORY ${CMAKE_PROJECT_DIR})
