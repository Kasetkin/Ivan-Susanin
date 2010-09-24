cmake_minimum_required(VERSION 2.6)

set(SOURCES
    controller.cpp
    main.cpp
    world.cpp
    hardware.cpp
)

add_executable(emu ${SOURCES})
target_link_libraries(emu
    ${Irrlicht_LIBRARIES}
    ${PYTHON_LIBRARIES}
    png
    jpeg
    glut
    bz2
    boost_thread
    boost_python
)