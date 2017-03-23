cmake_minimum_required (VERSION 2.6)
set(CMAKE_DEBUG_POSTFIX "d" CACHE STRING "add a postfix for Debug mode, usually d on windows")
project (DVA)
file(GLOB CoreSources "include/Core/*.h" "src/Core/*.cxx")
file(GLOB RenderSources "include/Render/*.h" "src/Render/*.cxx")
file(GLOB DVASources "src/App/*.cxx")
file(GLOB CoreQt_moc_src "include/CoreQt/*.h")
file(GLOB CoreQt_form_src "src/CoreQt/*.ui")
file(GLOB CoreQt_cpp_src "src/CoreQt/*.cpp")

find_package(Qt5Widgets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

QT5_WRAP_CPP(CoreQt_moc ${CoreQt_moc_src})
QT5_WRAP_UI(CoreQt_form ${CoreQt_form_src})

add_library(CoreQt STATIC ${CoreQt_moc} ${CoreQt_form} ${CoreQt_cpp_src})
qt5_use_modules(CoreQt Widgets)


include_directories(include)

add_executable(DVA ${DVASources})
qt5_use_modules(DVA Core Gui Widgets)
set_target_properties(DVA PROPERTIES DEBUG_POSTFIX "${CMAKE_DEBUG_POSTFIX}")

add_library(Core STATIC ${CoreSources})
add_library(Render STATIC ${RenderSources})

target_link_libraries(DVA Core Render CoreQt)
target_link_libraries(Render
Core
opengl32.lib
)