#
# Handle dependencies
#
find_package(Boost REQUIRED)
find_package(Threads REQUIRED)
find_package(ALSA)
find_package(LibMPDClient)
find_package(Libiw)

if(NOT ALSA_FOUND)
  set(ENABLE_ALSA OFF PARENT_SCOPE)
  message(WARNING "${ANSI}[41;1mDisabling \"volume module\" support (prerequisites failed)${ANSI}[0m")
endif()
if(NOT LIBMPDCLIENT_FOUND)
  set(ENABLE_MPD OFF PARENT_SCOPE)
  message(WARNING "${ANSI}[41;1mDisabling \"mpd module\" support (prerequisites failed)${ANSI}[0m")
endif()
if(NOT LIBIW_FOUND)
  set(ENABLE_NETWORK OFF PARENT_SCOPE)
  message(WARNING "${ANSI}[41;1mDisabling \"network module\" support (prerequisites failed)${ANSI}[0m")
endif()

set(XCB_PROTOS xproto randr)
add_subdirectory(${PROJECT_SOURCE_DIR}/lib/xpp ${PROJECT_BINARY_DIR}/lib/xpp)
add_subdirectory(${PROJECT_SOURCE_DIR}/lib/lemonbar ${PROJECT_BINARY_DIR}/lib/lemonbar)
add_subdirectory(${PROJECT_SOURCE_DIR}/lib/cpp_freetype ${PROJECT_BINARY_DIR}/lib/cpp_freetype)
if(ENABLE_I3)
  add_subdirectory(${PROJECT_SOURCE_DIR}/lib/i3ipcpp ${PROJECT_BINARY_DIR}/lib/i3ipcpp EXCLUDE_FROM_ALL)
endif()

#
# Create runtime target
#
add_executable(lemonbuddy
  $<$<BOOL:${ENABLE_ALSA}>:interfaces/alsa.cpp modules/volume.cpp>
  $<$<BOOL:${ENABLE_MPD}>:interfaces/mpd.cpp modules/mpd.cpp>
  $<$<BOOL:${ENABLE_NETWORK}>:interfaces/net.cpp modules/network.cpp>
  $<$<BOOL:${ENABLE_I3}>:modules/i3.cpp>
  interfaces/lemonbar.cpp
  drawtypes/animation.cpp
  drawtypes/bar.cpp
  drawtypes/icon.cpp
  drawtypes/label.cpp
  drawtypes/ramp.cpp
  modules/backlight.cpp
  modules/base.cpp
  modules/battery.cpp
  modules/bspwm.cpp
  modules/counter.cpp
  modules/cpu.cpp
  modules/date.cpp
  modules/memory.cpp
  modules/menu.cpp
  modules/script.cpp
  modules/text.cpp
  services/builder.cpp
  services/command.cpp
  services/event_throttler.cpp
  services/inotify.cpp
  services/logger.cpp
  utils/cli.cpp
  utils/config.cpp
  utils/io.cpp
  utils/proc.cpp
  utils/string.cpp
  utils/xcb.cpp
  bar.cpp
  eventloop.cpp
  lemonbuddy.cpp
  registry.cpp)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)

target_link_libraries(lemonbuddy
  ${ALSA_LIBRARY}
  ${BOOST_LIBRARIES}
  ${CMAKE_THREAD_LIBS_INIT}
  ${I3IPCPP_LIBRARIES}
  ${LEMONBAR_LIBRARIES}
  ${LIBIW_LIBRARY}
  ${LIBMPDCLIENT_LIBRARY}
  ${XPP_LIBRARIES})

target_include_directories(lemonbuddy PRIVATE ${PROJECT_SOURCE_DIR}/include
  ${ALSA_INCLUDE_DIR}
  ${BOOST_INCLUDE_DIR}
  ${I3IPCPP_INCLUDE_DIRS}
  ${LEMONBAR_INCLUDE_DIRS}
  ${LIBIW_INCLUDE_DIR}
  ${LIBMPDCLIENT_INCLUDE_DIR}
  ${SIGCPP_INCLUDE_DIRS}
  ${XPP_INCLUDE_DIRS})

target_compile_options(lemonbuddy PRIVATE $<$<CONFIG:Debug>:-g3 -DDEBUG>)
target_compile_options(lemonbuddy PRIVATE $<$<CONFIG:Release>:-O3>)

configure_file(
  ${PROJECT_SOURCE_DIR}/include/config.hpp.cmake
  ${CMAKE_SOURCE_DIR}/include/config.hpp
  ESCAPE_QUOTES @ONLY)

install(TARGETS lemonbuddy RUNTIME
  DESTINATION bin
  COMPONENT binaries)
