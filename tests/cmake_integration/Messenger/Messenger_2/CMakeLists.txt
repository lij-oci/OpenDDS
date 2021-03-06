# Distributed under the OpenDDS License. See accompanying LICENSE
# file or http://www.opendds.org/license.html for details.
#

project(OpenDDS_Messenger2_cmake CXX)
cmake_minimum_required(VERSION 3.8.2)

find_package(OpenDDS)

set(CMAKE_CXX_COMPILER ${OPENDDS_COMPILER})

if (NOT OPENDDS_OWNERSHIP_PROFILE)
  message(FATAL_ERROR "These tests require OpenDDS to be built with Ownership Profile enabled")
endif()

set(src "${CMAKE_CURRENT_SOURCE_DIR}/../../../DCPS/Messenger")
set(dst ${CMAKE_CURRENT_BINARY_DIR})
set(all_targets publisher subscriber messenger)

foreach(file
  Messenger.idl subscriber.cpp publisher.cpp Writer.cpp Writer.h Args.h
  DataReaderListener.cpp DataReaderListener.h)
  configure_file(${src}/${file} ${dst}/${file} COPYONLY)
endforeach()

# Messenger library
add_library(messenger)
OPENDDS_TARGET_SOURCES(messenger ${dst}/Messenger.idl)

# Publisher
add_executable(publisher
    ${dst}/publisher.cpp
    ${dst}/Writer.cpp
    ${dst}/Writer.h
)

# Subscriber
add_executable(subscriber
    ${dst}/subscriber.cpp
    ${dst}/DataReaderListener.cpp
    ${dst}/DataReaderListener.h
)

foreach(t ${all_targets})
  target_link_libraries(${t} OpenDDS::OpenDDS)

  if (NOT "${t}" STREQUAL "messenger")
    target_link_libraries(${t} messenger)
  endif()
endforeach()

# Copy configs/scripts into build-output directory
file(GLOB ini "${src}/*.ini")
file(GLOB pl "${src}/*.pl")
file(GLOB xml "${src}/*.xml")
file(GLOB p7s "${src}/*.p7s")

add_custom_target(Copy_ini_and_scripts
  ALL
  COMMAND_EXPAND_LISTS
  VERBATIM
  COMMENT "Copying configs/scripts into build-output directory"
  COMMAND ${CMAKE_COMMAND} -E copy ${ini} ${pl} ${xml} ${p7s} ${dst}/$<CONFIG>
)

add_dependencies(Copy_ini_and_scripts ${all_targets})
