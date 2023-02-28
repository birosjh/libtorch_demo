cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

project(demo)

list(APPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/include/libtorch")
find_package(Torch REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

add_executable(demo src/demo.cpp)
target_link_libraries(demo "${TORCH_LIBRARIES}")
set_property(TARGET demo PROPERTY CXX_STANDARD 17)

find_package(OpenCV REQUIRED)
target_link_libraries(demo ${OpenCV_LIBS})
include_directories(${OpenCV_INCLUDE_DIRS})

add_subdirectory(src)

target_include_directories(${PROJECT_NAME}
                            PUBLIC dataset)

target_link_directories(${PROJECT_NAME} 
                        PRIVATE dataset)

target_link_libraries(${PROJECT_NAME} 
                        dataset)