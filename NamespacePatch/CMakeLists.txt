cmake_minimum_required(VERSION 3.20)
project(UnityNamespacePatch)

# Find Microsoft Detours
find_path(DETOURS_INCLUDE_DIRS detours.h PATH_SUFFIXES detours REQUIRED)
find_library(DETOURS_LIBRARIES detours REQUIRED)

# Find source files
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "source/*.cpp")
file(GLOB_RECURSE INCLUDES CONFIGURE_DEPENDS "include/*.h")

# Initialize target
set(TARGET_NAME "version")
add_library(${TARGET_NAME} SHARED ${SOURCES} ${INCLUDES})
target_include_directories(${TARGET_NAME} PRIVATE include ${DETOURS_INCLUDE_DIRS})
target_link_directories(${TARGET_NAME} PRIVATE libraries)
target_link_libraries(${TARGET_NAME} PRIVATE delayimp dbghelp pathcch Unity CSharpHelper ${DETOURS_LIBRARIES})

# Enable delay loading for Unity
target_link_options(${TARGET_NAME} PRIVATE "/DELAYLOAD:Unity.exe")
