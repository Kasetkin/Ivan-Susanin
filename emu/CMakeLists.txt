# Main server CMake file
cmake_minimum_required(VERSION 2.6)

PROJECT(Emu)

set(TARGET_NAME Emu)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(Irrlicht)

if (NOT Irrlicht_FOUND)
    message(FATAL "Irrlicht not found, try set Irrlicht_ROOT")
endif (NOT Irrlicht_FOUND)

find_package(PythonLibs)
if (NOT PYTHONLIBS_FOUND)
    message(FATAL "Python not found, try set PythonLibs_ROOT")
endif (NOT PYTHONLIBS_FOUND)

include_directories(include ${Irrlicht_INCLUDE_DIR} ${PYTHON_INCLUDE_PATH})

add_subdirectory(src)


 
