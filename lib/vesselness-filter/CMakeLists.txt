# vim: ft=cmake
cmake_minimum_required(VERSION 2.8)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

include_directories(${LIBDIR})
include_directories(.)

add_library( EigenFrangi frangi/EigenFrangi.cxx PixelAccessors.hxx FilterCommon.hxx )
add_library( EigenSato sato/EigenSato.cxx  PixelAccessors.hxx FilterCommon.hxx )
