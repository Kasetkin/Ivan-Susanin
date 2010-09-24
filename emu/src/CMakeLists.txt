cmake_minimum_required(VERSION 2.6)

set(SOURCES
    controller.cpp
    main.cpp
    world.cpp
    hardware.cpp

    mainwindow.cpp
)

set(MOC_HEADERS
    ../include/mainwindow.h
    #../include/mainwindow.ui
)

set(UI
    ../include/mainwindows.ui
)

QT4_WRAP_CPP (MOC_SOURCES ${MOC_HEADERS})
qt4_wrap_ui(UI_HEADERS ${UI} )

add_executable(emu ${SOURCES} ${MOC_SOURCES})
target_link_libraries(emu
    ${Irrlicht_LIBRARIES}
    ${PYTHON_LIBRARIES}
    ${QScintilla_LIBRARIES}
    png
    jpeg
    glut
    bz2
    boost_thread
    boost_python
    ${QT_LIBRARIES}

)