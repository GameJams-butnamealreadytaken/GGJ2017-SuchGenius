cmake_minimum_required(VERSION 3.1)

# main files
set(SOURCES_main main.cpp)
source_group("" FILES ${SOURCES_main})

# Game files
set(SOURCES_Game Game.cpp Game.h)
source_group("Game" FILES ${SOURCES_Game})

# State files
set(SOURCES_State State.cpp State.h)
source_group("State" FILES ${SOURCES_State})

# Inputs files
set(SOURCES_Inputs inputs.cpp inputs.h)
source_group("Inputs" FILES ${SOURCES_Inputs})

# Application files
set(SOURCES_Application application.cpp application.h)
source_group("Application" FILES ${SOURCES_Application})

# Put everything together before adding platform-specific files
set(SOURCES ${SOURCES_main} ${SOURCES_Game} ${SOURCES_State} ${SOURCES_Inputs} ${SOURCES_Application})

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	add_executable(Game WIN32 ${SOURCES})
ELSE()
	add_executable(Game ${SOURCES})
ENDIF()

set_property(TARGET Game PROPERTY FOLDER "Runtime")

set_property(TARGET Game APPEND PROPERTY COMPILE_DEFINITIONS "${SHSDK_COMPILE_DEFINITIONS}")
set_property(TARGET Game APPEND PROPERTY COMPILE_FLAGS "${SHSDK_COMPILE_FLAGS}")
set_property(TARGET Game APPEND PROPERTY COMPILE_DEFINITIONS "SH_$<UPPER_CASE:$<CONFIG>>=1")

target_link_libraries(Game ${SHSDK_LIBRARIES})
target_include_directories(Game PRIVATE ${SHSDK_INCLUDE_DIR})
