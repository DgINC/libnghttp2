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
project(libnghttp2 VERSION 1.51.0 DESCRIPTION "HTTP/2 C library" HOMEPAGE_URL "https://github.com/tatsuhiro-t/nghttp2" LANGUAGES C )

option(LIBNGHTTP2_BUILD_STATIC "Build static lib" ON)

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/include/libnghttp2/nghttp2ver.h.in" "${CMAKE_CURRENT_BINARY_DIR}/include/libnghttp2/nghttp2ver.h")

if(WIN32)
  configure_file("${CMAKE_CURRENT_SOURCE_DIR}/src/version.rc.in" "${CMAKE_CURRENT_BINARY_DIR}/version.rc" @ONLY)
  set(LIBNGHTTP2_RES "${CMAKE_CURRENT_SOURCE_DIR}/src/version.rc")
else()
  configure_file("${CMAKE_CURRENT_SOURCE_DIR}/src/${PROJECT_NAME}.pc.in" "${CMAKE_CURRENT_BINARY_DIR}/libnghttp2.pc" @ONLY)
endif()

include_directories(
  "${CMAKE_CURRENT_SOURCE_DIR}/includes"
  "${CMAKE_CURRENT_BINARY_DIR}/includes")

list (APPEND LIBNGHTTP2_SOURCE_FILES
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
  "${CMAKE_CURRENT_SOURCE_DIR}/src/nghttp2_version.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/nghttp2_priority_spec.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/nghttp2_option.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/nghttp2_callbacks.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/nghttp2_mem.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/nghttp2_http.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/nghttp2_rcbuf.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/nghttp2_extpri.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/nghttp2_debug.c")

if (LIBNGHTTP2_BUILD_STATIC)
  add_library(${PROJECT_NAME} STATIC ${LIBNGHTTP2_SOURCE_FILES})
else()
  add_library(${PROJECT_NAME} SHARED ${LIBNGHTTP2_SOURCE_FILES})
endif()

target_include_directories(${PROJECT_NAME}
  SYSTEM PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>  # <prefix>/include/libnghttp2
)

set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD_REQUIRED ON)
set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 17)

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release
        CACHE STRING "Set build type to Debug o Release (default Release)" FORCE)
endif()

install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
	
install(FILES ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.pc DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)