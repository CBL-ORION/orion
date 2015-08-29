# vim: ft=cmake
cmake_minimum_required(VERSION 2.8)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

include_directories(${LIBDIR})
include_directories(${LIBDIR}/filter/vesselness)
include_directories(${LIBDIR}/filter/vesselness/frangi)
include_directories(${LIBDIR}/filter/vesselness/sato)
link_directories(${BUILDDIR}/filter/vesselness)
link_directories(${BUILDDIR}/ndarray)

include_directories(${LIBDIR})
include_directories(.)

add_library( IntegrationITK itk.cxx )
target_link_libraries(IntegrationITK ${ITK_LIBRARIES} EigenFrangi EigenSato ndarray3.o array_ndarray3.o)
