cmake_minimum_required(VERSION 3.1)

# define some defaults for compiler options
set(CMAKE_USER_MAKE_RULES_OVERRIDE "platform.cmake")

project(molecular_simulation CXX)

find_package(Boost "1.58" QUIET REQUIRED COMPONENTS
  program_options
  system
  )

include_directories(${molecular_simulation_SOURCE_DIR}/include)
include_directories(${Boost_INCLUDE_DIR})

add_subdirectory(src)
