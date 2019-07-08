#############################################################################
# File: FindCerberoGStreamer.cmake                                          #
#                                                                           #
# Notes: The cerbero is assumed to be in either ~/cerbero or ~/git/cerbero. #
# If it is not, change the FIND_PATH(CERBERO_DIR ...) hints for your system.#
#                                                                           #
# The build system is also assumed linux_x86_64, so the actual macro        #
# FIND_PATH(${_prefix}_INCLUDES ...) hint might need change according to    #
# the system.                                                               #
#                                                                           #
# You might need to run the built program in cerbero shell for it to work   #
# correctly.                                                                #
#############################################################################



#############################################################################
# REUSABLE PORTION                                                          #
#############################################################################
# Find Cerbero and make a macro to easily find cerbero installed packages   #
# Macro parameters:                                                         #
#  _prefix: Name for the cmake variable, _INCLUDES and _LIBS added after    #
#           given prefix for the include directories and libraries          #
#  _header: The header file name (partial paths are ok too)                 #
#  _lib: The library to find                                                #
#  _path_suffix: A subdirectory to search from, if the header isn't exactly #
#           in the include directory root                                   #
#                                                                           #
# Makes a list of all searched libraries and include directories with names #
# CERB_ALL_INCLUDES and CERB_ALL_LIBS. You can also include the libraries   #
# and include directories separately by the name you give them as the       #
# _prefix.                                                                  #
#############################################################################
message(STATUS "Checking for cerbero in home directory...")

# The typical places I'd imageine cerbero to be pulled from git
FIND_PATH(CERBERO_DIR
    NAMES cerbero-uninstalled
    HINTS $ENV{HOME}/cerbero $ENV{HOME}/git/cerbero)


IF(CERBERO_DIR)
    message(STATUS "Cerbero found in ${CERBERO_DIR}")
    message(STATUS "Assuming GStreamer and its deps to be built with cerbero")

ELSE ()
message(WARNING "Cerbero not found!")
ENDIF ()


# Macro for easing the search of cerbero installed packages
MACRO(FIND_CERBERO_BUILT_COMPONENT _prefix _header _lib _path_suffix)

FIND_PATH(${_prefix}_INCLUDES
    NAMES ${_header}
    HINTS ${CERBERO_DIR}/build/dist/linux_x86_64/include
    PATH_SUFFIXES ${_path_suffix})

LIST(APPEND CERB_ALL_INCLUDES ${${_prefix}_INCLUDES})

FIND_LIBRARY(${_prefix}_LIBS
    NAMES ${_lib}
    HINTS ${CERBERO_DIR}/build/dist/linux_x86_64/lib)

LIST(APPEND CERB_ALL_LIBS ${${_prefix}_LIBS})

ENDMACRO ()
#############################################################################
# REUSABLE PORTION END                                                      #
#############################################################################

# Searching for the components:
#   GStreamer(GStreamer core library)
#   GLib(required by GStreamer libraries)
#   GObject(required by GStreamer plugins)
FIND_CERBERO_BUILT_COMPONENT(CERB_GSTREAMER gst/gst.h gstreamer-1.0 gstreamer-1.0)
FIND_CERBERO_BUILT_COMPONENT(CERB_GLIB glib.h glib-2.0 glib-2.0)
FIND_CERBERO_BUILT_COMPONENT(CERB_GOBJECT gobject/gobject.h gobject-2.0 glib-2.0)

# Also searching for glibconfig.h(required by GLib)
FIND_PATH(CERB_GLIB_CONFIG_INCLUDES glibconfig.h
    ${CERBERO_DIR}/build/dist/linux_x86_64/lib/glib-2.0/include)
LIST(APPEND CERB_ALL_INCLUDES ${CERB_GLIB_CONFIG_INCLUDES})