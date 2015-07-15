# vim: ft=cmake
cmake_minimum_required(VERSION 2.8)

project(ComputeFilter)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

include_directories(${LIBDIR})
include_directories(${LIBDIR}/vesselness-filter)
include_directories(${LIBDIR}/vesselness-filter/frangi)
include_directories(${LIBDIR}/vesselness-filter/sato)
link_directories(${BUILDDIR}/vesselness-filter)

#PixelAccessors.h EigenFrangi.h EigenSato.h

add_executable(ComputeFilter ComputeFilter.cxx )
target_link_libraries(ComputeFilter ${ITK_LIBRARIES} EigenFrangi EigenSato)
