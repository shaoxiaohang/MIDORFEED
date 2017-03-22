cmake_minimum_required (VERSION 2.6)
set(CMAKE_DEBUG_POSTFIX "d" CACHE STRING "add a postfix for Debug mode, usually d on windows")
project (DVA)
file(GLOB CoreSources "include/Core/*.h" "src/Core/*.cxx")
file(GLOB RenderSources "include/Render/*.h" "src/Render/*.cxx")
file(GLOB DVASources "src/App/*.cxx")

#find QtCore
find_path(QT_INCLUDE_DIR QtCore/QtCore
PATHS
$ENV{QT_ROOT}/include
)
find_path(QT_LIB_DIR Qt5Core.lib
PATHS
$ENV{QT_ROOT}/lib
)

include_directories(include)
link_directories(${QT_LIB_DIR})

add_executable(DVA ${DVASources})
set_target_properties(DVA PROPERTIES DEBUG_POSTFIX "${CMAKE_DEBUG_POSTFIX}")

add_library(Core STATIC ${CoreSources})
add_library(Render STATIC ${RenderSources})

target_include_directories(Render PUBLIC ${QT_INCLUDE_DIR})

target_link_libraries(DVA Core Render)
target_link_libraries(Render
debug Qt5Core${CMAKE_DEBUG_POSTFIX} optimized Qt5Core
debug Qt5Widgets${CMAKE_DEBUG_POSTFIX} optimized Qt5Widgets
debug Qt5Gui${CMAKE_DEBUG_POSTFIX} optimized Qt5Gui
Core
opengl32.lib
)