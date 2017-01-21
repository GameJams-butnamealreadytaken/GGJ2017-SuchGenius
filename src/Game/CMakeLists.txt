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

# Credits
set(SOURCES_GameStateCredits GameStateCredits.cpp GameStateCredits.h)
source_group("State\\Credits" FILES ${SOURCES_GameStateCredits})

# Main menu
set(SOURCES_GameStateMainMenu GameStateMainMenu.cpp GameStateMainMenu.h)
source_group("State\\MainMenu" FILES ${SOURCES_GameStateMainMenu})

# Level Selection
set(SOURCES_GameStateLevelSelection GameStateLevelSelection.cpp GameStateLevelSelection.h)
source_group("State\\LevelSelection" FILES ${SOURCES_GameStateLevelSelection})

# Game
set(SOURCES_GameStateGame GameStateGame.cpp GameStateGame.h)
source_group("State\\Game" FILES ${SOURCES_GameStateGame})

# Win
set(SOURCES_GameStateWin GameStateWin.cpp GameStateWin.h)
source_group("State\\Win" FILES ${SOURCES_GameStateWin})

# Inputs files
set(SOURCES_Inputs inputs.cpp inputs.h)
source_group("Inputs" FILES ${SOURCES_Inputs})

# Application files
set(SOURCES_Application application.cpp application.h)
source_group("Application" FILES ${SOURCES_Application})

# Put everything together before adding platform-specific files
set(SOURCES ${SOURCES_main} ${SOURCES_Game} ${SOURCES_State} ${SOURCES_Inputs} ${SOURCES_Application} ${SOURCES_GameStateCredits} ${SOURCES_GameStateMainMenu} ${SOURCES_GameStateLevelSelection} ${SOURCES_GameStateGame} ${SOURCES_GameStateWin})

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	add_executable(Game WIN32 ${SOURCES})
ELSE()
	add_executable(Game ${SOURCES})
ENDIF()

if (MSVC)
	SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /FORCE:MULTIPLE")
endif (MSVC)

set_property(TARGET Game PROPERTY FOLDER "Runtime")

set_property(TARGET Game APPEND PROPERTY COMPILE_DEFINITIONS "${SHSDK_COMPILE_DEFINITIONS}")
set_property(TARGET Game APPEND PROPERTY COMPILE_FLAGS "${SHSDK_COMPILE_FLAGS}")
set_property(TARGET Game APPEND PROPERTY COMPILE_DEFINITIONS "SH_$<UPPER_CASE:$<CONFIG>>=1")

target_link_libraries(Game PRIVATE ${SHSDK_LIBRARIES})
target_link_libraries(Game PRIVATE Plugin)
target_include_directories(Game PRIVATE "${SHSDK_INCLUDE_DIR}" "$<TARGET_PROPERTY:Box2D,INCLUDE_DIRECTORIES>")
