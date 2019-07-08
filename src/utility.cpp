// Utility functions used in visualizer_server utility.cpp

#include <string.h>
#include <string>
#include <array>
#include <memory>
#include <iostream>

#include "utility.h"

/**
 * @brief Execute a command line command and get the stdout
 */
std::string Exec(const char *cmd)
{
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe)
    {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
    {
        result += buffer.data();
    }
    return result;
}

/**
 * @brief Handle the user input from the given parameters argc and argv
 */
std::string UserInput(int argc, char const *argv[]){
    std::cout << "NOTE: The visualizer might require the sound settings form the computer side to be quite loud to work correctly." << std::endl;
    std::string device = "output";
    if (argc == 2)
    {
        if (strcmp(argv[1], "--bluetooth") == 0)
        {
            device = "blue";
        }
        else if (strcmp(argv[1], "-h") == 0 | strcmp(argv[1], "--help") == 0)
        {
            std::string command = Exec(("pactl list | grep -A2 'Source #' | grep '" + device + "' | cut -d\" \" -f2").c_str());
            std::cout << "Help:" << std::endl
                      << " Commands:" << std::endl
                      << "   --bluetooth" << std::endl
                      << "     Tries to detect bluetooth device instead of the output monitor." << std::endl
                      << "   -h --help" << std::endl
                      << "     Print this help" << std::endl
                      << std::endl
                      << "Default audio monitor:" << std::endl
                      << "  " << command << std::endl;
            device = "blue";
            command = Exec(("pactl list | grep -A2 'Source #' | grep '" + device + "' | cut -d\" \" -f2").c_str());
            std::cout << "Bluetooth device:" << std::endl;
            if (command == "")
            {
                std::cout << "  No bluetooth device found!" << std::endl;
            }
            else
            {
                std::cout << "  " << command << std::endl;
            }
            return "";
        }
        else
        {
            std::cout << "Unknown command. Give -h or --help for help." << std::endl;
            return "";
        }
    }
    else if (argc > 2)
    {
        std::cout << "Incorrect amount of commands. Give -h or --help for help." << std::endl;
        return "";
    }
    return device;
}