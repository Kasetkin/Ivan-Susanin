# - Find QScintilla
include(FindPkgMacros)

set(QScintilla_ROOT ${QScintilla_HOME} ${QScintilla_ROOT})

findpkg_begin(QScintilla)

FIND_PATH(QScintilla_INCLUDE_DIR irrlicht.h
    ${QScintilla_ROOT}/include
    /usr/include/irrlicht/
    /usr/local/include/irrlicht/
)

FIND_LIBRARY(QScintilla_LIBRARY qscintilla2 PATHS
    ${QScintilla_ROOT}/lib
    ${QScintilla_ROOT}/lib/Release
    ${QScintilla_ROOT}/bin
    /usr/lib/
    /usr/local/lib
    /usr/lib/qt4/
    /usr/local/lib/qt4/
)

FIND_LIBRARY(QScintilla_LIBRARY_d qscintilla2 PATHS
    ${QScintilla_ROOT}/lib
    ${QScintilla_ROOT}/lib/Release
    ${QScintilla_ROOT}/bin
    /usr/lib/
    /usr/local/lib
    /usr/lib/qt4/
    /usr/local/lib/qt4/
)

INCLUDE(FindPackageHandleStandardArgs)

set(QScintilla_FOUND false)
if(QScintilla_INCLUDE_DIR AND (QScintilla_LIBRARY AND QScintilla_LIBRARY_d))
    set(QScintilla_FOUND true)
endif()

set(QScintilla_INCLUDE_PATH ${QScintilla_INCLUDE_DIR})

IF (QScintilla_FOUND)
    SET (QScintilla_LIBRARIES_REL ${QScintilla_LIBRARY})
    SET (QScintilla_LIBRARIES_DBG ${QScintilla_LIBRARY_d})
ENDIF (QScintilla_FOUND)

make_library_set(QScintilla_LIBRARIES)

findpkg_finish(QScintilla)

#MARK_AS_ADVANCED(MyGUI_LIBRARY MyGUI_INCLUDE_PATH)