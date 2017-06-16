INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_EFFECTS effects)

FIND_PATH(
    EFFECTS_INCLUDE_DIRS
    NAMES effects/api.h
    HINTS $ENV{EFFECTS_DIR}/include
        ${PC_EFFECTS_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    EFFECTS_LIBRARIES
    NAMES gnuradio-effects
    HINTS $ENV{EFFECTS_DIR}/lib
        ${PC_EFFECTS_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(EFFECTS DEFAULT_MSG EFFECTS_LIBRARIES EFFECTS_INCLUDE_DIRS)
MARK_AS_ADVANCED(EFFECTS_LIBRARIES EFFECTS_INCLUDE_DIRS)

