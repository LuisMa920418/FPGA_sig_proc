#-----------------------------------------
# CMakeLists
#-----------------------------------------

cmake_minimum_required(VERSION 2.4)
project(design)

message(STATUS "DIR vivado : $ENV{XILINX_VIVADO}")
message(STATUS "DIR bin : $ENV{dir_bin}")
message(STATUS "DIR systc lib : $ENV{lib_systemc}")

#-----------------------------------------
# Config
#-----------------------------------------

if(CMAKE_BUILD_TYPE STREQUAL Debug)
  message(STATUS "MODE Debug")
  set(CMAKE_BUILD_TYPE Debug)
	set(lib_dir $ENV{dir_lib_debug})
elseif(CMAKE_BUILD_TYPE STREQUAL Release)
  message(STATUS "MODE Release")
  set(CMAKE_BUILD_TYPE Release)
	set(lib_dir $ENV{dir_lib_release})
endif()

#set(EXECUTABLE_OUTPUT_PATH $ENV{dir_bin})
set(LIBRARY_OUTPUT_PATH ${lib_dir})

#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY $ENV{dir_bin})

#-----------------------------------------
# Project includes + libs
#-----------------------------------------

include_directories(
  include
	$ENV{XILINX_VIVADO}/include
	$ENV{XILINX_VIVADO}/lnx64/tools/systemc/include
  )

link_directories($ENV{lib_systemc} ${lib_dir})

#if(CMAKE_BUILD_TYPE STREQUAL Debug)
#  set(EXE top_project_debug.exe)
#  elseif(CMAKE_BUILD_TYPE STREQUAL Release)
#  set(EXE top_project.exe)
#endif()

#-----------------------------------------
# Files
#-----------------------------------------

#file(
#  GLOB
#  files
#  *.cpp
#  )
#
#
#add_executable(
#  ${EXE}
#  ${files}
#  )

#-----------------------------------------
# Link
#-----------------------------------------

#target_link_libraries(
#  ${EXE}
#  top_polyphase
#  fft
#  )

#add_subdirectory(stim)
add_subdirectory(filter)
#add_subdirectory(polyphase)
#add_subdirectory(fft)
