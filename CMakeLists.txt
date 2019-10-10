cmake_minimum_required (VERSION 2.6)
set(CMAKE_DEBUG_POSTFIX "d" CACHE STRING "add a postfix for Debug mode, usually d on windows")
project (DVA)
file(GLOB CoreSources "include/Core/*.h" "src/Core/*.cpp")
file(GLOB RenderSources "include/Render/*.h" "src/Render/*.cpp")
file(GLOB DVASources "src/App/*.cpp")
file(GLOB GUISources "include/GUI/*.h" "src/GUI/*.cpp")

#find include directory by looking for certain header file
find_path(TINYXMY_INCLUDE_DIR tinyxml2.h
PATHS
$ENV{TINYXML_ROOT}/include
)

#find include directory by looking for certain header file
find_path(TINYXMY_LIB_DIR tinyxml2d.lib
PATHS
$ENV{TINYXML_ROOT}/lib
)

#find library directory by looking for certain library file
find_path(ASSIMP_INCLUDE_DIR assimp/ai_assert.h
PATHS
$ENV{ASSIMP_ROOT}/include
)

#find library directory by looking for certain library file
find_path(ASSIMP_LIB_DIR assimp-vc120-mt.lib
PATHS
$ENV{ASSIMP_ROOT}/lib
)

#find include directory by looking for certain header file
find_path(FREEIMAGE_INCLUDE_DIR FreeImage.h
PATHS
$ENV{FREEIMAGE_ROOT}/x64
)

#find library directory by looking for certain library file
find_path(FREEIMAGE_LIB_DIR FreeImaged.lib
PATHS
$ENV{FREEIMAGE_ROOT}/x64
)

#find include directory by looking for certain header file
find_path(BOOST_INCLUDE_DIR boost/signals2.hpp
PATHS
$ENV{BOOST_ROOT}/include
)

#find library directory by looking for certain library file
find_path(BOOST_LIB_DIR boost_graph-vc120-mt-1_63.lib
PATHS
$ENV{BOOST_ROOT}/lib/
)
#apply them to following projects
include_directories(${TINYXMY_INCLUDE_DIR})
link_directories(${TINYXMY_LIB_DIR})
include_directories(${ASSIMP_INCLUDE_DIR})
link_directories(${ASSIMP_LIB_DIR})
include_directories(${FREEIMAGE_INCLUDE_DIR})
link_directories(${FREEIMAGE_LIB_DIR})
include_directories(${BOOST_INCLUDE_DIR})
link_directories(${BOOST_LIB_DIR})

set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(include)

add_executable(DVA ${DVASources})

set_target_properties(DVA PROPERTIES DEBUG_POSTFIX "${CMAKE_DEBUG_POSTFIX}")

add_library(Core STATIC ${CoreSources})
add_library(Render STATIC ${RenderSources})
add_library(GUI STATIC ${GUISources})

target_link_libraries(DVA Core Render GUI)
target_link_libraries(Render
Core
opengl32.lib
FreeImaged.lib
boost_signals-vc120-mt-1_63.lib
assimp-vc120-mt.lib
tinyxml2d.lib
)
target_link_libraries(GUI
Core
Render
)

