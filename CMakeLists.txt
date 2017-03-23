cmake_minimum_required (VERSION 2.6)
set(CMAKE_DEBUG_POSTFIX "d" CACHE STRING "add a postfix for Debug mode, usually d on windows")
set(CMAKE_PREFIX_PATH "C:\\Qt\\5.8\\msvc2013_64\\")
project (DVA)
file(GLOB CoreSources "include/Core/*.h" "src/Core/*.cxx")
file(GLOB RenderSources "include/Render/*.h" "src/Render/*.cxx")
file(GLOB CoreQtSources "include/CoreQt/*.h" "src/CoreQt/*.cpp")
file(GLOB DVASources "src/App/*.cxx")
file(GLOB CoreQt_moc_src "include/CoreQt/*.h")
file(GLOB CoreQt_form_src "src/CoreQt/*.ui")


find_package(Qt5Widgets)
find_package(Qt5OpenGL)

#find_package(OpenGL)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

QT5_WRAP_CPP(CoreQt_moc ${CoreQt_moc_src})
QT5_WRAP_UI(CoreQt_form ${CoreQt_form_src})

include_directories(include)

add_executable(DVA ${DVASources})

set_target_properties(DVA PROPERTIES DEBUG_POSTFIX "${CMAKE_DEBUG_POSTFIX}")

add_library(CoreQt STATIC ${CoreQt_moc} ${CoreQt_form} ${CoreQtSources})
add_library(Core STATIC ${CoreSources})
add_library(Render STATIC ${RenderSources})

target_link_libraries(CoreQt opengl32.lib Qt5::Core Qt5::Widgets Qt5::OpenGL)
target_link_libraries(DVA Core Render CoreQt )
target_link_libraries(Render
Core
opengl32.lib
)

add_custom_command(TARGET DVA
                   POST_BUILD
                   COMMAND xcopy "..\bin64"  "$(ProjectDir)Debug" /y /q
                   COMMENT "copy dlls")