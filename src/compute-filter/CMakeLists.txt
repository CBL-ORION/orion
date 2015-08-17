# vim: ft=cmake
cmake_minimum_required(VERSION 2.8)

project(ComputeFilter)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

include_directories(${LIBDIR})
include_directories(${LIBDIR}/filter/vesselness)
include_directories(${LIBDIR}/filter/vesselness/frangi)
include_directories(${LIBDIR}/filter/vesselness/sato)
link_directories(${BUILDDIR}/filter/vesselness)

#PixelAccessors.hxx EigenFrangi.hxx EigenSato.hxx

add_executable(ComputeFilter ComputeFilter.cxx )
target_link_libraries(ComputeFilter ${ITK_LIBRARIES} EigenFrangi EigenSato)
