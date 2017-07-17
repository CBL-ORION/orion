cmake_minimum_required(VERSION 2.8)
 
find_package(ITK REQUIRED)
include(${ITK_USE_FILE})
if (ITKVtkGlue_LOADED)
  find_package(VTK REQUIRED)
  include(${VTK_USE_FILE})
endif()

add_executable(Pi Pi.cxx )
target_link_libraries(Pi ${ITK_LIBRARIES})

#message( ${ITK_LIBRARIES} ) 


foreach (incdir ${ITK_INCLUDE_DIRS})
	set(ITK_CPPFLAGS "${ITK_CPPFLAGS} -I${incdir}")
endforeach()

foreach (libdir ${ITK_LIBRARY_DIRS})
	set(ITK_LDFLAGS "${ITK_LDFLAGS} -L${libdir}")
endforeach()

foreach (lib ${ITK_LIBRARIES})
	# this variable does not give the actual linker flags
	#set(ITK_LDLIBS "${ITK_LDLIBS} -l${lib}-4.8")
endforeach()

set(ITK_CONFIG_MK_GEN "${CMAKE_BINARY_DIR}/itk-config.mk.gen" )
file(WRITE ${ITK_CONFIG_MK_GEN} "ITK_CPPFLAGS := ${ITK_CPPFLAGS}\n")
file(APPEND ${ITK_CONFIG_MK_GEN} "ITK_LDFLAGS := ${ITK_LDFLAGS}\n")
file(APPEND ${ITK_CONFIG_MK_GEN} "ITK_LDLIBS := ${ITK_LDLIBS}\n")

#get_cmake_property(_variableNames VARIABLES)
#foreach (_variableName ${_variableNames})
    #message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()
