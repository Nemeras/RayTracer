cmake_minimum_required(VERSION 3.1)
project(RayTracer)
#Merci Jean-Yves pour le CMakeLists.txt

set(CMAKE_BUILD_TYPE Release)


# Verification of the support of C++11
set(CMAKE_CXX_STANDARD 11)


# Find OpenMP
find_package(OpenMP)
if (OPENMP_FOUND)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()


if (NOT WIN32)
	find_package(X11)
	find_package(Threads REQUIRED)
endif()
if (X11_FOUND)
	link_directories(${X11_LIB_DIRS})
	include_directories(${X11_INCLUDE_DIR})
	set(SYSTEM_LIBS ${SYSTEM_LIBS} ${X11_LIBRARIES})
endif()
if (NOT WIN32)
	set(SYSTEM_LIBS ${SYSTEM_LIBS} ${CMAKE_THREAD_LIBS_INIT})
endif()
if (WIN32)
	set(SYSTEM_LIBS ${SYSTEM_LIBS} gdi32)
endif()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CIMG_CFLAGS}")


# Source files
file(GLOB SOURCES src/*)


# Executable
set(
	EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}
)
add_executable(
	raytracer
	${SOURCES}
	${X11_LIB_DIRS}
)
if (NOT WIN32)
	target_link_libraries(
		raytracer
		X11
	)
endif()
