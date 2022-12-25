# nghttp2 - HTTP/2 C Library
#
# Copyright (c) 2012, 2013, 2014, 2015 Tatsuhiro Tsujikawa
# Copyright (c) 2016 Peter Wu <peter@lekensteyn.nl>
#
# Permission is hereby granted, free of charge, to any person obtaining
# a copy of this software and associated documentation files (the
# "Software"), to deal in the Software without restriction, including
# without limitation the rights to use, copy, modify, merge, publish,
# distribute, sublicense, and/or sell copies of the Software, and to
# permit persons to whom the Software is furnished to do so, subject to
# the following conditions:
#
# The above copyright notice and this permission notice shall be
# included in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
# LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
# OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
# WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

cmake_minimum_required(VERSION 3.24)
project(nghttp2 VERSION 1.51.0 DESCRIPTION "HTTP/2 C library" HOMEPAGE_URL "https://github.com/tatsuhiro-t/nghttp2" LANGUAGES C )

option(BUILD_SHARED_LIBS "Build using shared libraries" OFF)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "Choose the build type" FORCE)

  # Include "None" as option to disable any additional (optimization) flags,
  # relying on just CMAKE_C_FLAGS and CMAKE_CXX_FLAGS (which are empty by
  # default). These strings are presented in cmake-gui.
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
    "None" "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

list(APPEND LIBNGHTTP2_SOURCE_FILES
  "${CMAKE_CURRENT_SOURCE_DIR}/src/nghttp2_pq.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/nghttp2_map.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/nghttp2_queue.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/nghttp2_frame.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/nghttp2_buf.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/nghttp2_stream.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/nghttp2_outbound_item.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/nghttp2_session.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/nghttp2_submit.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/nghttp2_helper.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/nghttp2_npn.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/nghttp2_hd.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/nghttp2_hd_huffman.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/nghttp2_hd_huffman_data.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/nghttp2_priority_spec.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/nghttp2_option.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/nghttp2_callbacks.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/nghttp2_mem.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/nghttp2_http.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/nghttp2_rcbuf.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/nghttp2_extpri.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/nghttp2_debug.c")

if(WIN32)
  configure_file("${CMAKE_CURRENT_SOURCE_DIR}/src/version.rc.in" "${CMAKE_CURRENT_BINARY_DIR}/version.rc" @ONLY)
  list (APPEND LIBNGHTTP2_SOURCE_FILES "${CMAKE_CURRENT_BINARY_DIR}/version.rc")
else()
  configure_file("${CMAKE_CURRENT_SOURCE_DIR}/src/${PROJECT_NAME}.pc.in" "${CMAKE_CURRENT_BINARY_DIR}/libnghttp2.pc" @ONLY)
endif()

add_library(${PROJECT_NAME} ${LIBNGHTTP2_SOURCE_FILES})

target_include_directories(${PROJECT_NAME}
  PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src"
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  INTERFACE $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

target_compile_features(${PROJECT_NAME} PUBLIC c_std_17)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})

set_target_properties(${PROJECT_NAME} PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})

set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/include/libnghttp2/nghttp2.h)

if(WIN32)
  set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "lib${PROJECT_NAME}")
  set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX "d")
endif()

if(LIBNGHTTP2_BUILD_STATIC)
  install(TARGETS ${PROJECT_NAME} ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}")
elseif(WIN32)
  install(TARGETS ${PROJECT_NAME} EXPORT "${PROJECT_NAME}Targets" RUNTIME DESTINATION "${CMAKE_INSTALL_LIBDIR}" PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}")
else()
  install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}")
endif()

if(UNIX AND NOT APPLE)
    install(FILES ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.pc DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)
endif()



set(CPACK_PACKAGE_VENDOR "Vendor name")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Some summary")
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENCE")
set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md")

set(CPACK_SOURCE_GENERATOR "TGZ;ZIP")
set(CPACK_SOURCE_IGNORE_FILES
    /.git
    /dist
    /.*build.*
    /\\\\.DS_Store
)

include(CPack)
