# Main server CMake file
cmake_minimum_required(VERSION 2.6)

PROJECT(Emu)

set(TARGET_NAME Emu)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(Irrlicht)

if (NOT Irrlicht_FOUND)
    message(FATAL "Irrlicht not found, try set Irrlicht_ROOT")
endif (NOT Irrlicht_FOUND)

find_package(QScintilla)

if (NOT QScintilla_FOUND)
    message(FATAL "QScintilla not found, try set QScintilla_ROOT")
endif (NOT QScintilla_FOUND)

find_package(PythonLibs)
if (NOT PYTHONLIBS_FOUND)
    message(FATAL "Python not found, try set PythonLibs_ROOT")
endif (NOT PYTHONLIBS_FOUND)

find_package (Qt4 REQUIRED)
set (QT_USE_QTMAIN true)
set (QT_USE_QTPLUGIN true)
include (${QT_USE_FILE})
include_directories (
      ${QT_INCLUDES}
      ${CMAKE_CURRENT_SOURCE_DIR}/tmp
  )
link_directories (
      ${CMAKE_CURRENT_SOURCE_DIR}/../plugins
  )

include_directories(include ${Irrlicht_INCLUDE_DIR} ${PYTHON_INCLUDE_PATH} ${QScintilla_INCLUDE_DIR})

add_subdirectory(src)


 
