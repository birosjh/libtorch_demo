add_library(dataset Dataset/dataset.cpp)

target_link_libraries(dataset "${TORCH_LIBRARIES}" ${OpenCV_LIBS})
