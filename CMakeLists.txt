cmake_minimum_required(VERSION 3.10)
project(Detector)
find_package(OpenCV REQUIRED)
#add_executable(Detector DepthDetector.cpp Process.cpp ImageModifier.cpp)
add_executable(Detector TestFile.cpp)

target_link_libraries(Detector ${OpenCV_LIBS})