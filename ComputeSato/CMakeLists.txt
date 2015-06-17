cmake_minimum_required(VERSION 2.8)
 
project(ComputeEigenValue_Sorted_Sato)
 
find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

 
add_executable(ComputeEigenValue_Sorted_Sato ComputeEigenValue_Sorted_Sato.cxx PixelAccessors.h)
target_link_libraries(ComputeEigenValue_Sorted_Sato ${ITK_LIBRARIES})