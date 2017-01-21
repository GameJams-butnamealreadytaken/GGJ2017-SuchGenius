cmake_minimum_required(VERSION 3.1)

set(SHINE_EDITOR_EXT_DIR "" CACHE PATH "Extension directory")
set(SHSDK_EDITOR_LIBRARIES "" CACHE PATH "ShSDK (editor) path") # FIXME

# main file
if (WIN32)
	set(SOURCES_main dllmain.cpp)
	source_group("" FILES ${SOURCES_main})
else(WIN32)
	set(SOURCES_main )
endif (WIN32)

# Plugin files
set(SOURCES_Plugin Plugin.cpp Plugin.h)
source_group("Plugin" FILES ${SOURCES_Plugin})

# Plugin files
set(SOURCES_Block Block.cpp Block.h)
source_group("Plugin\\Block" FILES ${SOURCES_Block})

# Listener files
set(SOURCES_Listener Box2D_listener.cpp Box2D_listener.h)
source_group("Plugin\\Listener" FILES ${SOURCES_Listener})

# Factory files
set(SOURCES_Factory PluginFactory.cpp PluginFactory.h)
source_group("Factory" FILES ${SOURCES_Factory})

# Put everything together before adding platform-specific files
set(SOURCES ${SOURCES_Plugin} ${SOURCES_Factory} ${SOURCES_Listener} ${SOURCES_Block})

# Compile to use it on Runtime
add_library(Plugin STATIC ${SOURCES})
set_property(TARGET Plugin PROPERTY FOLDER "Runtime")
set_property(TARGET Plugin APPEND PROPERTY COMPILE_DEFINITIONS "${SHSDK_COMPILE_DEFINITIONS} -fno-exceptions -fno-rtti")
set_property(TARGET Plugin APPEND PROPERTY COMPILE_FLAGS "${SHSDK_COMPILE_FLAGS}")

target_link_libraries(Plugin INTERFACE ${SHSDK_LIBRARIES})
target_link_libraries(Plugin INTERFACE Box2D)
target_include_directories(Plugin PRIVATE "${SHSDK_INCLUDE_DIR}" "$<TARGET_PROPERTY:Box2D,INCLUDE_DIRECTORIES>")

# Compile to use it in the Shine Editor
add_library(Plugin_Editor SHARED ${SOURCES_main} ${SOURCES})
set_property(TARGET Plugin_Editor PROPERTY FOLDER "Editor")
set_property(TARGET Plugin_Editor APPEND PROPERTY COMPILE_DEFINITIONS "${SHSDK_COMPILE_DEFINITIONS}")
set_property(TARGET Plugin_Editor APPEND PROPERTY COMPILE_FLAGS "${SHSDK_COMPILE_FLAGS} -fPIC")
set_property(TARGET Plugin_Editor APPEND PROPERTY COMPILE_DEFINITIONS "SH_EDITOR=1" "_INTERNAL_DLL") # FIXME
set_property(TARGET Plugin_Editor APPEND PROPERTY POSITION_INDEPENDENT_CODE True)

target_link_libraries(Plugin_Editor PRIVATE ${SHSDK_EDITOR_LIBRARIES})
target_link_libraries(Plugin_Editor PRIVATE Box2D_shared)
target_include_directories(Plugin_Editor PRIVATE "${SHSDK_INCLUDE_DIR}" "$<TARGET_PROPERTY:Box2D,INCLUDE_DIRECTORIES>")
