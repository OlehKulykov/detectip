# MIT License
#
# Copyright (c) 2024 Oleh Kulykov
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.


cmake_minimum_required(VERSION 3.28 FATAL_ERROR)

project(detectip LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)

set(DETECTIP_APP detectip)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")
message("CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}")

include(CheckLibraryExists)
include(CheckFunctionExists)
include(ExternalProject)

set(CURL_USE_STATIC_LIBS TRUE)
find_package(CURL REQUIRED)
message("CURL include dir: ${CURL_INCLUDE_DIRS}")
message("CURL libraries: ${CURL_LIBRARIES}")
message("CURL_USE_STATIC_LIBS: ${CURL_USE_STATIC_LIBS}")

include_directories(BEFORE SYSTEM ${CURL_INCLUDE_DIRS})

# ---- Sources & headers ----

set(DETECTIP_HEADERS
  src/detectip_curl_downloader.hpp
  src/detectip_detectors_ipify_org.hpp
  src/detectip_detectors_jsonip_com.hpp
  src/detectip_detectors_my_ip_io.hpp
  src/detectip_detectors_ip_api_com.hpp
  src/detectip_detectors_seeip_org.hpp
  src/detectip_detectors_bigdatacloud.hpp
  src/detectip_detectors_iplocation_net.hpp
  src/detectip_detectors_ipinfo_io.hpp
  src/detectip_detectors_ipy_ch.hpp
  src/detectip_detector.hpp
  src/detectip_rapid_json_parser.hpp
  src/detectip_rapidjson.hpp
)

set(DETECTIP_SOURCES
  src/main.cpp
  src/detectip_curl_downloader.cpp
  src/detectip_detectors_ipify_org.cpp
  src/detectip_detectors_jsonip_com.cpp
  src/detectip_detectors_my_ip_io.cpp
  src/detectip_detectors_ip_api_com.cpp
  src/detectip_detectors_seeip_org.cpp
  src/detectip_detectors_bigdatacloud.cpp
  src/detectip_detectors_iplocation_net.cpp
  src/detectip_detectors_ipinfo_io.cpp
  src/detectip_detectors_ipy_ch.cpp
  src/detectip_detector.cpp
  src/detectip_rapid_json_parser.cpp
)

# ---- Groups ----

source_group("main"
  FILES
  src/main.cpp
  src/detectip_curl_downloader.cpp
  src/detectip_curl_downloader.hpp
  src/detectip_detectors_ipify_org.cpp
  src/detectip_detectors_ipify_org.hpp
  src/detectip_detectors_jsonip_com.cpp
  src/detectip_detectors_jsonip_com.hpp
  src/detectip_detectors_my_ip_io.cpp
  src/detectip_detectors_my_ip_io.hpp
  src/detectip_detectors_ip_api_com.cpp
  src/detectip_detectors_ip_api_com.hpp
  src/detectip_detectors_seeip_org.cpp
  src/detectip_detectors_seeip_org.hpp
  src/detectip_detectors_bigdatacloud.cpp
  src/detectip_detectors_bigdatacloud.hpp
  src/detectip_detectors_iplocation_net.cpp
  src/detectip_detectors_iplocation_net.hpp
  src/detectip_detectors_ipinfo_io.cpp
  src/detectip_detectors_ipinfo_io.hpp
  src/detectip_detectors_ipy_ch.cpp
  src/detectip_detectors_ipy_ch.hpp
  src/detectip_detector.cpp
  src/detectip_detector.hpp
  src/detectip_rapid_json_parser.cpp
  src/detectip_rapid_json_parser.hpp
  src/detectip_rapidjson.hpp
 )

add_executable(${DETECTIP_APP} ${DETECTIP_HEADERS} ${DETECTIP_SOURCES})
target_link_libraries(${DETECTIP_APP} ${CURL_LIBRARIES})
