# Find QJSON - JSON handling library for Qt
#
# This module defines
#  QJSON_FOUND - whether the qsjon library was found
#  QJSON_LIBRARIES - the qjson library
#  QJSON_INCLUDE_DIR - the include path of the qjson library
#

if (QJSON_INCLUDE_DIR AND QJSON_LIBRARIES)
   # in cache already
   set(QJSON_FIND_QUIETLY TRUE)
endif (QJSON_INCLUDE_DIR AND QJSON_LIBRARIES)

if (NOT WIN32)
   # use pkg-config to get the directories and then use these values
   # in the FIND_PATH() and FIND_LIBRARY() calls
   find_package(PkgConfig)
   pkg_check_modules(PC_QJSON QJson)
   set(QJSON_DEFINITIONS ${PC_QJSON_CFLAGS_OTHER})
endif (NOT WIN32)

find_path(QJSON_INCLUDE_DIR parser.h
   HINTS
   ${PC_QJSON_INCLUDEDIR}
   ${PC_QJSON_INCLUDE_DIRS}
   ${INCLUDE_INSTALL_DIR}
   ${KDE4_INCLUDE_DIR}
   PATH_SUFFIXES qjson
   )

find_library(QJSON_LIBRARIES NAMES qjson
   HINTS
   ${PC_QJSON_LIBDIR}
   ${PC_QJSON_LIBRARY_DIRS}
   ${LIB_INSTALL_DIR}
   ${KDE4_LIB_DIR}
   )

include(FindPackageHandleStandardArgs)

# handle the QUIETLY and REQUIRED arguments and set QJSON_FOUND to TRUE if
# all listed variables are TRUE
find_package_handle_standard_args(QJSON DEFAULT_MSG QJSON_LIBRARIES QJSON_INCLUDE_DIR)

mark_as_advanced(QJSON_INCLUDE_DIR QJSON_LIBRARIES)
