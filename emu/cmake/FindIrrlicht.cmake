# - Find Irrlicht
include(FindPkgMacros)

set(Irrlicht_ROOT ${Irrlicht_HOME} ${Irrlicht_ROOT})

findpkg_begin(Irrlicht)

FIND_PATH(Irrlicht_INCLUDE_DIR irrlicht.h
	${Irrlicht_ROOT}/include
	/usr/include/irrlicht/
	/usr/local/include/irrlicht/
)

FIND_LIBRARY(Irrlicht_LIBRARY Irrlicht PATHS
	${Irrlicht_ROOT}/lib
	${Irrlicht_ROOT}/lib/Release
	${Irrlicht_ROOT}/bin
	/usr/lib/
	/usr/local/lib
)

FIND_LIBRARY(Irrlicht_LIBRARY_d Irrlicht PATHS
    ${Irrlicht_ROOT}/lib
    ${Irrlicht_ROOT}/lib/Debug
    ${Irrlicht_ROOT}/bin
    /usr/lib/
    /usr/local/lib
)

INCLUDE(FindPackageHandleStandardArgs)

set(Irrlicht_FOUND false)
if(Irrlicht_INCLUDE_DIR AND (Irrlicht_LIBRARY AND Irrlicht_LIBRARY_d))
	set(Irrlicht_FOUND true)
endif()

set(Irrlicht_INCLUDE_PATH ${Irrlicht_INCLUDE_DIR})

IF (Irrlicht_FOUND)
	SET (Irrlicht_LIBRARIES_REL ${Irrlicht_LIBRARY})
	SET (Irrlicht_LIBRARIES_DBG ${Irrlicht_LIBRARY_d})
ENDIF (Irrlicht_FOUND)

make_library_set(Irrlicht_LIBRARIES)

findpkg_finish(Irrlicht)

#MARK_AS_ADVANCED(MyGUI_LIBRARY MyGUI_INCLUDE_PATH)