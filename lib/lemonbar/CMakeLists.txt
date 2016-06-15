cmake_minimum_required(VERSION 3.0)
project(lemonbar)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

find_package(Freetype REQUIRED)
find_package(X11 REQUIRED Xft)
find_package(X11_XCB REQUIRED)
find_package(XCB REQUIRED)

add_library(lemonbar src/lemonbar.c)

set_property(TARGET lemonbar PROPERTY C_STANDARD 99)
set_property(TARGET lemonbar PROPERTY C_STANDARD_REQUIRED ON)

target_link_libraries(lemonbar
  ${FREETYPE_LIBRARIES}
  ${X11_X11_LIB}
  ${X11_Xft_LIB}
  ${X11_XCB_LIBRARIES}
  ${XCB_XCB_LIBRARY})

target_include_directories(lemonbar PUBLIC
  ${PROJECT_SOURCE_DIR}/include
  ${FREETYPE_INCLUDE_DIRS}
  ${X11_INCLUDE_DIRS}
  ${X11_XCB_INCLUDE_DIR}
  ${XCB_XCB_INCLUDE_DIR})

target_compile_definitions(lemonbar PUBLIC
  ${X11_XCB_DEFINITIONS}
  ${XCB_DEFINITIONS})

target_compile_options(lemonbar PRIVATE -Wall)
target_compile_options(lemonbar PRIVATE $<$<CONFIG:Debug>:-g3 -DDEBUG -Wunused-parameter -Wlong-long -Wsign-conversion -Wconversion -Wimplicit-function-declaration>)
target_compile_options(lemonbar PRIVATE $<$<CONFIG:Release>:-O3>)

# Export lists to the parent scope if there are any
get_directory_property(HAS_PARENT PARENT_DIRECTORY)
if(HAS_PARENT)
  set(LEMONBAR_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include PARENT_SCOPE)
  set(LEMONBAR_LIBRARIES lemonbar PARENT_SCOPE)
endif()
