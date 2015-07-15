# vim: ft=cmake
cmake_minimum_required(VERSION 2.8)

project(SubsampleVolume)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

include_directories(${LIBDIR})

add_executable(SubsampleVolume SubsampleVolume.cxx )
target_link_libraries(SubsampleVolume  ${ITK_LIBRARIES})
