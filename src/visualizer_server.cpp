// GStreamer visualizer for fun visualizer_server.cpp

#include <string>
#include <iostream>

#include <gst/gst.h>
#include "utility.h"
#include "AVStream.h"

int main(int argc, char const *argv[])
{
    // Set GST_DEBUG to 3 for viewing warning messages if there isn't GST_DEBUG set
    if(getenv("GST_DEBUG") == nullptr)
        setenv("GST_DEBUG", "3", 1);;

    // Taking the additional parameters given on command line
    std::string device = UserInput(argc, argv);

    // Getting the full pulse device name
    std::string command = Exec(("pactl list | grep -A2 'Source #' | grep '" + device + "' | cut -d\" \" -f2").c_str());

    std::cout << std::endl
              << "NOTE: There is no exit programmed in, so the only way to stop this program is to just kill it with Ctrl-C or something else." << std::endl
              << "The messages following this are from GStreamer." << std::endl
              << std::endl;

    // Running the AVStream given the full pulse device name
    AVStream stream(command);
    stream.run(); // The program loops in here

    return EXIT_SUCCESS;
}