cmake_minimum_required(VERSION 3.1)

set(CMAKE_INSTALL_PREFIX ${PROJECT_BINARY_DIR})

project(SWOS_CC)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

set(CMAKE_C_STANDARD 99)

if( CMAKE_SIZEOF_VOID_P EQUAL 8 )
  MESSAGE(FATAL_ERROR "64 compiling not allowed!")
endif( CMAKE_SIZEOF_VOID_P EQUAL 8 )

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  MESSAGE(FATAL_ERROR "GCC compiling not allowed!")
endif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")

set(ROOTSRC ${PROJECT_SOURCE_DIR}/src)
set(ROOTINC ${PROJECT_SOURCE_DIR}/include)

set(SWSASIINC ${PROJECT_SOURCE_DIR}/include/swosasi)
set(WINMMSRC ${PROJECT_SOURCE_DIR}/src/winmm)
set(WINMMINC ${PROJECT_SOURCE_DIR}/include/winmm)

set(SWSCCSRC ${PROJECT_SOURCE_DIR}/src/swscc)
set(SWSCCINC ${PROJECT_SOURCE_DIR}/include/swscc)

set(SWSSAVERSRC ${PROJECT_SOURCE_DIR}/src/swssaver)

set(DEPS ${PROJECT_SOURCE_DIR}/deps)


if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  set(CMAKE_CXX_FLAGS "-Wall -Wextra -masm=intel")
  set(CMAKE_CXX_FLAGS_DEBUG "-g -DDEBUG")
  set(CMAKE_CXX_FLAGS_RELEASE "-O3 -s -DNDEBUG")
  set(CMAKE_CXX_FLAGS_MINSIZEREL "-O3 -s -DNDEBUG")
  set(CMAKE_CXx_FLAGS_RELWITHDEBINFO "-O2 -g -DNDEBUG")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  set(CMAKE_CXX_FLAGS "/DWIN32 /D_WINDOWS /W3 /GR /EHsc /D_CRT_SECURE_NO_WARNINGS")
  set(CMAKE_CXX_FLAGS_DEBUG "/MDd /Zi /Ob0 /Od /RTC1")
  set(CMAKE_CXX_FLAGS_MINSIZEREL "/MD /O1 /Ob1 /DNDEBUG")
  set(CMAKE_CXX_FLAGS_RELEASE "/MD /O2 /Ob2 /DNDEBUG")
  set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/MD /Zi /O2 /Ob1 /DNDEBUG")
endif()


include_directories(${WINMMSRC})
include_directories(${WINMMINC})
include_directories(${DEPS}/pugixml)

include_directories(${SWSASIINC})


include_directories(${SWSCCINC})
include_directories(${SWSCCSRC})


set(CMAKE_SHARED_LIBRARY_PREFIX "")
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  #WINMM WRAPPER
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

  set(WINMM_FILES
    ${WINMMSRC}/winmmmain.cc
    ${WINMMINC}/winmmmain.def
  )

  add_library(winmm SHARED ${WINMM_FILES})
endif()
#ASI PLUGINS
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/plugins)

set(SWSCCSRC_FILES
  ${SWSCCSRC}/swscc.cc
  ${SWSCCSRC}/swscomp.cc
  ${DEPS}/pugixml/pugixml.cpp
  )

add_library(swscc SHARED ${SWSCCSRC_FILES})
target_compile_definitions(swscc PUBLIC MAKEDLL)
target_link_options(swscc PUBLIC -static)
set_target_properties(swscc PROPERTIES SUFFIX ".asi")


