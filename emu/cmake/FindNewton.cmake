# - Find Newton
include(FindPkgMacros)

set(Newton_ROOT ${Newton_HOME} ${Newton_ROOT})

findpkg_begin(Newton)

FIND_PATH(Newton_INCLUDE_DIR Newton.h
    ${Newton_ROOT}/include
    /usr/include/
    /usr/local/include/
)

FIND_LIBRARY(Newton_LIBRARY Newton PATHS
    ${Newton_ROOT}/lib
    ${Newton_ROOT}/lib/Release
    ${Newton_ROOT}/bin
    /usr/lib/
    /usr/local/lib
)

FIND_LIBRARY(Newton_LIBRARY_d Newton PATHS
    ${Newton_ROOT}/lib
    ${Newton_ROOT}/lib/Debug
    ${Newton_ROOT}/bin
    /usr/lib/
    /usr/local/lib
)

INCLUDE(FindPackageHandleStandardArgs)

set(Newton_FOUND false)
if(Newton_INCLUDE_DIR AND (Newton_LIBRARY AND Newton_LIBRARY_d))
    set(Newton_FOUND true)
endif()

set(Newton_INCLUDE_PATH ${Newton_INCLUDE_DIR})

IF (Newton_FOUND)
    SET (Newton_LIBRARIES_REL ${Newton_LIBRARY})
    SET (Newton_LIBRARIES_DBG ${Newton_LIBRARY_d})
ENDIF (Newton_FOUND)

make_library_set(Newton_LIBRARIES)

findpkg_finish(Newton)

#MARK_AS_ADVANCED(MyGUI_LIBRARY MyGUI_INCLUDE_PATH)