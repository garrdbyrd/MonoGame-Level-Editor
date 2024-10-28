cmake_minimum_required(VERSION 3.5.0)
project(caspian VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Import all Qt components ---------------------------------------
set(QT_INCLUDE_DIR "/usr/include/qt")

file(GLOB QT_SUBDIRS "${QT_INCLUDE_DIR}/Qt*")
set(QT_COMPONENTS "")

foreach(dir ${QT_SUBDIRS})
    get_filename_component(dir_name ${dir} NAME)
    string(REPLACE "Qt" "" component ${dir_name})
    list(APPEND QT_COMPONENTS ${component})
endforeach()

find_package(Qt5 REQUIRED COMPONENTS ${QT_COMPONENTS})
# ----------------------------------------------------------------

add_executable(caspian main.cpp)

target_include_directories(caspian PRIVATE ${CMAKE_SOURCE_DIR})

foreach(component ${QT_COMPONENTS})
    target_link_libraries(caspian Qt5::${component})
endforeach()

# Use qt5_wrap_ui or qt6_wrap_ui depending on the version of Qt
qt5_wrap_ui(UI_SOURCES ${CORE_FORMS} ${PREFERENCES_FORMS})

# Add generated UI sources to the target
target_sources(caspian PRIVATE ${UI_SOURCES})

target_include_directories(caspian PRIVATE 
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/src/core
    ${CMAKE_SOURCE_DIR}/src/level
    ${CMAKE_SOURCE_DIR}/src/preferences
)

# include all src/ subdirs
# target_include_directories(caspian PRIVATE
#     "${CMAKE_SOURCE_DIR}/src/command"
#     "${CMAKE_SOURCE_DIR}/src/core"
#     "${CMAKE_SOURCE_DIR}/src/preferences"
# )

