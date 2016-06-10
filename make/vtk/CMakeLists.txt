cmake_minimum_required(VERSION 2.8)

PROJECT(ImageMapper)

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

add_executable(ImageMapper MACOSX_BUNDLE ImageMapper)

if(VTK_LIBRARIES)
  target_link_libraries(ImageMapper ${VTK_LIBRARIES})
else()
  target_link_libraries(ImageMapper vtkHybrid vtkWidgets)
endif()

message( ${VTK_LIBRARIES} )


foreach (incdir ${VTK_INCLUDE_DIRS})
	set(VTK_CPPFLAGS "${VTK_CPPFLAGS} -I${incdir}")
endforeach()

foreach (libdir ${VTK_LIBRARY_DIRS})
	set(VTK_LDFLAGS "${VTK_LDFLAGS} -L${libdir}")
endforeach()

foreach (lib ${VTK_LIBRARIES})
	# this variable does not give the actual linker flags
	#set(VTK_LDLIBS "${VTK_LDLIBS} -l${lib}")
endforeach()

set(VTK_CONFIG_MK_GEN "${CMAKE_BINARY_DIR}/vtk-config.mk.gen" )
file(WRITE ${VTK_CONFIG_MK_GEN} "VTK_CPPFLAGS := ${VTK_CPPFLAGS}\n")
file(APPEND ${VTK_CONFIG_MK_GEN} "VTK_LDFLAGS := ${VTK_LDFLAGS}\n")
file(APPEND ${VTK_CONFIG_MK_GEN} "VTK_LDLIBS := ${VTK_LDLIBS}\n")

#get_cmake_property(_variableNames VARIABLES)
#foreach (_variableName ${_variableNames})
    #message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()
