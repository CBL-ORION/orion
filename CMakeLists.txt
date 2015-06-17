cmake_minimum_required(VERSION 2.8)
 
project(ComputeFilter)
 
find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

 
add_executable(ComputeFilter ComputeFilter.cxx PixelAccessors.h EigenFrangi.h EigenSato.h)
target_link_libraries(ComputeFilter ${ITK_LIBRARIES})