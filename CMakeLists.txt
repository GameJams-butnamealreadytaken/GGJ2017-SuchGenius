cmake_minimum_required(VERSION 3.1)

project(GGJ2017)

#
# Enable some global CMake features
#

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_CXX_STANDARD 11)

IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE Debug)
ENDIF()

#
# Find ShSDK
#

if (NOT DEFINED SHINE_INTERNAL)
	list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules/")
endif (NOT DEFINED SHINE_INTERNAL)

find_package(ShSDK REQUIRED StubUserSystem ShEntryPoint)

#
# Set some additionnal compile flags
#

IF("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Weverything -Wno-padded -Wno-documentation -Wno-weak-vtables -Wno-global-constructors -Wno-exit-time-destructors -Wno-c++98-compat")
ELSEIF("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
ENDIF()

option(ENABLE_ASAN "Enable address sanitizer" OFF)

IF (ENABLE_ASAN)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fno-omit-frame-pointer")
ENDIF (ENABLE_ASAN)

IF (NOT MSVC)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions -fno-rtti") # Disable exceptions / RTTI
ENDIF (NOT MSVC)

#
# Add sources
#

set(BOX2D_INSTALL OFF CACHE BOOL "Install Box2D libs, includes, and CMake scripts" FORCE)
set(BOX2D_BUILD_EXAMPLES OFF CACHE BOOL "Build Box2D examples" FORCE)
set(BOX2D_BUILD_SHARED ON CACHE BOOL "Build Box2D shared libraries" FORCE)

add_subdirectory(Box2D/Box2D Box2D)

add_subdirectory(src)
