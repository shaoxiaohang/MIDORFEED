cmake_minimum_required (VERSION 3.10)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project (DVA)
file(GLOB CoreSources "include/Core/*.h" "src/Core/*.cpp")
file(GLOB RenderSources "include/Render/*.h" "src/Render/*.cpp")
file(GLOB DVASources "src/App/*.cpp")
file(GLOB GUISources "include/GUI/*.h" "src/GUI/*.cpp")

set(TINYXML_INCLUDE_DIR $ENV{TINYXML_ROOT}/include)
set(TINYXML_LIB_DIR $ENV{TINYXML_ROOT}/lib)

set(ASSIMP_INCLUDE_DIR $ENV{ASSIMP_ROOT}/include)
set(ASSIMP_LIB_DIR $ENV{ASSIMP_ROOT}/lib)


#apply them to following projects
include_directories(${TINYXML_INCLUDE_DIR})
link_directories(${TINYXML_LIB_DIR})
include_directories(${ASSIMP_INCLUDE_DIR})
link_directories(${ASSIMP_LIB_DIR})


include_directories(include)

add_executable(DVA ${DVASources})

add_library(Core STATIC ${CoreSources})
add_library(Render STATIC ${RenderSources})
add_library(GUI STATIC ${GUISources})

target_include_directories(Core PUBLIC include/Core)
target_include_directories(Render PUBLIC include/Render)
target_include_directories(GUI PUBLIC include/GUI)

target_link_libraries(DVA Core Render GUI)
target_link_libraries(Render
Core
opengl32.lib
assimp-vc140-mt.lib
tinyxml2d.lib
zlibstaticd.lib
)
target_link_libraries(GUI
Core
Render
)


