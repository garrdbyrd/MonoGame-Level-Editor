cmake_minimum_required(VERSION 3.5.0)
project(caspian VERSION 0.1.0 LANGUAGES C CXX)


set(QT_INCLUDE_DIR "/usr/include/qt")

file(GLOB QT_SUBDIRS "${QT_INCLUDE_DIR}/Qt*")
set(QT_COMPONENTS "")

foreach(dir ${QT_SUBDIRS})
    get_filename_component(dir_name ${dir} NAME)
    string(REPLACE "Qt" "" component ${dir_name})
    list(APPEND QT_COMPONENTS ${component})
endforeach()

find_package(Qt5 REQUIRED COMPONENTS ${QT_COMPONENTS})

add_executable(caspian main.cpp)

target_include_directories(caspian PRIVATE ${CMAKE_SOURCE_DIR})
# target_include_directories(caspian PRIVATE /usr/include/qt/)

foreach(component ${QT_COMPONENTS})
    target_link_libraries(caspian Qt5::${component})
endforeach()
