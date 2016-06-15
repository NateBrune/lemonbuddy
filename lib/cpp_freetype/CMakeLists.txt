cmake_minimum_required(VERSION 3.1)
project(cpp_freetype C CXX)

find_package(PkgConfig REQUIRED)
pkg_check_modules(FREETYPE REQUIRED freetype2)
pkg_check_modules(SIGCPP REQUIRED sigc++-2.0)

add_library(cpp_freetype
  src/Face.cpp
  src/GlyphSlot.cpp
  src/Library.cpp
  src/Memory.cpp
  src/Module.cpp
  src/ModuleClass.cpp
  src/OpenArgs.cpp
  src/Outline.cpp
  src/Untag.cpp)

target_include_directories(cpp_freetype PRIVATE
  ${PROJECT_SOURCE_DIR}/include
  ${SIGCPP_INCLUDE_DIRS}
  ${FREETYPE_INCLUDE_DIRS})

set_property(TARGET cpp_freetype PROPERTY CXX_STANDARD 11)
set_property(TARGET cpp_freetype PROPERTY CXX_STANDARD_REQUIRED ON)

target_compile_options(cpp_freetype PRIVATE $<$<CONFIG:Debug>:-g3>)
target_compile_options(cpp_freetype PRIVATE $<$<CONFIG:Release>:-O3>)

target_link_libraries(cpp_freetype
  ${SIGCPP_LIBRARIES}
  ${FRETYPE_LIBRARIES})
