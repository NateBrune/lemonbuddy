#
# Build configuration
#
cmake_minimum_required(VERSION 3.1)
project(lemonbuddy C CXX)

# Include the local cmake modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake/modules)

if(NOT CMAKE_BUILD_TYPE)
  message(STATUS "No build type specified; using Release")
  set(CMAKE_BUILD_TYPE "Release")
endif()

string(ASCII 27 ANSI)

#
# Figure out default option values
#
find_package(ALSA QUIET)
find_package(Libiw QUIET)
find_package(LibMPDClient QUIET)
find_program(CCACHE_BINARY ccache)
if(CCACHE_BINARY)
  set(CCACHE_FOUND ON)
endif()
find_program(I3_BINARY i3)
if(I3_BINARY)
  set(I3_FOUND ON)
endif()

option(ENABLE_CCACHE  "Enable ccache support"  ${CCACHE_FOUND})
option(ENABLE_ALSA    "Enable alsa support"    ${ALSA_FOUND})
option(ENABLE_I3      "Enable i3 support"      ${I3_FOUND})
option(ENABLE_MPD     "Enable mpd support"     ${LIBMPDCLIENT_FOUND})
option(ENABLE_NETWORK "Enable network support" ${LIBIW_FOUND})

if(ENABLE_ALSA)
  set(SETTING_ALSA_SOUNDCARD "default"
    CACHE STRING "Name of the ALSA soundcard driver")
endif()
set(SETTING_CONNECTION_TEST_IP "8.8.8.8"
  CACHE STRING "Address to ping when testing network connection")
set(SETTING_PATH_BACKLIGHT_VAL "/sys/class/backlight/%card%/brightness"
  CACHE STRING "Path to file containing the current backlight value")
set(SETTING_PATH_BACKLIGHT_MAX "/sys/class/backlight/%card%/max_brightness"
  CACHE STRING "Path to file containing the maximum backlight value")
set(SETTING_PATH_BATTERY_CAPACITY "/sys/class/power_supply/%battery%/capacity"
  CACHE STRING "Path to file containing the current battery capacity")
set(SETTING_PATH_ADAPTER_STATUS "/sys/class/power_supply/%adapter%/online"
  CACHE STRING "Path to file containing the current adapter status")
set(SETTING_BSPWM_SOCKET_PATH "/tmp/bspwm_0_0-socket"
  CACHE STRING "Path to bspwm socket")
set(SETTING_BSPWM_STATUS_PREFIX "W"
  CACHE STRING "Prefix prepended to the bspwm status line")
set(SETTING_PATH_CPU_INFO "/proc/stat"
  CACHE STRING "Path to file containing cpu info")
set(SETTING_PATH_MEMORY_INFO "/proc/meminfo"
  CACHE STRING "Path to file containing memory info")

if(ENABLE_CCACHE)
  set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "ccache")
  set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK "ccache")
endif()

#
# Add source tree to the build
#
add_subdirectory(${PROJECT_SOURCE_DIR}/man)
add_subdirectory(${PROJECT_SOURCE_DIR}/src ${PROJECT_BINARY_DIR}/bin)
add_subdirectory(${PROJECT_SOURCE_DIR}/examples ${PROJECT_BINARY_DIR}/examples)

#
# Execute versioning script
#
execute_process(COMMAND ./version.sh WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} OUTPUT_QUIET ERROR_QUIET)

#
# Build summary
#
message(STATUS "---------------------------")
message(STATUS " Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS " Compiler C: ${CMAKE_C_COMPILER}")
message(STATUS " Compiler C++: ${CMAKE_CXX_COMPILER}")
message(STATUS "---------------------------")
message(STATUS " Enable ccache support  ${ENABLE_CCACHE}")
message(STATUS " Enable alsa support    ${ENABLE_ALSA}")
message(STATUS " Enable i3 support      ${ENABLE_I3}")
message(STATUS " Enable mpd support     ${ENABLE_MPD}")
message(STATUS " Enable network support ${ENABLE_NETWORK}")
message(STATUS "---------------------------")

#
# Uninstall target
#
configure_file(
  ${PROJECT_SOURCE_DIR}/cmake/uninstall.cmake.in
  ${PROJECT_BINARY_DIR}/cmake/uninstall.cmake
  IMMEDIATE @ONLY)

add_custom_target(uninstall COMMAND ${CMAKE_COMMAND}
  -P ${PROJECT_BINARY_DIR}/cmake/uninstall.cmake)
