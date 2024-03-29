// Utility functions for visualizer_server.cpp utility.h

#pragma once
#ifndef STREAM_UTILITY_H
#define STREAM_UTILITY_H

#include <string>

std::string Exec(
    const char *cmd);  // Execute command line command and get the output text
std::string UserInput(
    int argc,
    char const *argv[]);  // User input handling for visualizer_server.cpp

#endif