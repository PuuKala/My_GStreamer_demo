# GStreamer visualizer demo CMakeLists.txt

cmake_minimum_required(VERSION 3.0)

file(GLOB SERVER_SRC "src/visualizer_server.cpp" "src/utility.cpp" "src/AVStream.cpp")
file(GLOB CLIENT_SRC "src/ogg_client.cpp")

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR})

FIND_PACKAGE(CerberoGStreamer)

INCLUDE_DIRECTORIES(${CERB_ALL_INCLUDES} "include")

ADD_EXECUTABLE(GST_visualizer_demo ${SERVER_SRC})
TARGET_LINK_LIBRARIES(GST_visualizer_demo ${CERB_ALL_LIBS})

ADD_EXECUTABLE(GST_ogg_client ${CLIENT_SRC})
TARGET_LINK_LIBRARIES(GST_ogg_client ${CERB_ALL_LIBS})