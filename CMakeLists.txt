cmake_minimum_required(VERSION 2.8)
 
project(ComputeFilter)
 
find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

add_library( EigenFrangi EigenFrangi.cxx )
add_library( EigenSato EigenSato.cxx )
 
add_executable(ComputeFilter ComputeFilter.cxx PixelAccessors.h EigenFrangi.h EigenSato.h)
target_link_libraries(ComputeFilter ${ITK_LIBRARIES} EigenFrangi EigenSato)