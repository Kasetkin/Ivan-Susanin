cmake_minimum_required(VERSION 2.6)

set(SOURCES
    controller.cpp
    main.cpp
    world.cpp
    hardware.cpp

    mainwindow.cpp

    newton_utils.cpp

    grid.cpp
)

set(MOC_HEADERS
    ../include/mainwindow.h
    #../include/mainwindow.ui
)

set(UI
    ../include/mainwindow.ui
)

QT4_WRAP_CPP (MOC_SOURCES ${MOC_HEADERS})
qt4_wrap_ui(UI_HEADERS ${UI} )

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(emu ${SOURCES} ${MOC_SOURCES} ${UI_HEADERS})
target_link_libraries(emu
    ${Irrlicht_LIBRARIES}
    ${PYTHON_LIBRARIES}
    ${QScintilla_LIBRARIES}
    ${Newton_LIBRARIES}
    png
    jpeg
    glut
    bz2
    boost_thread
    boost_python
    ${QT_LIBRARIES}

)

add_executable(grid grid.cpp grid_test.cpp)
