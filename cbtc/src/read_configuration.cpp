#include "read_configuration.hpp"

#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>


using cbtc::utils::simple_logger;


namespace {
    
std::string get_next_line(std::ifstream* const file)
{
    std::string line = "";
    bool end_file = false;

    while(line.length() == 0 and !end_file)
    {
        if(!file->eof()) 
        {
            std::getline(*file >> std::ws,line);
        }
        else
        {
            end_file = true;
        }
    }
    return line;
}

}

const cbtc::utils::configuration_params cbtc::utils::read_configuration(const std::string file_path)
{
    std::ifstream file;     
    std::string line;
    
    file.open(file_path);       
   
    line = get_next_line(&file);
    std::string limboole_path = line;
    
    line = get_next_line(&file);
    file.close();

    simple_logger::level logger_level = simple_logger::level::ERROR;
    
    if (line == "NONE")
    {
        logger_level = simple_logger::level::NONE;
    }
    if (line == "ERROR")
    {
        logger_level = simple_logger::level::ERROR;
    }
    if (line == "WARNING")
    {
        logger_level = simple_logger::level::WARNING;
    }
    if (line == "INFO")
    {
        logger_level = simple_logger::level::INFO;
    }
    if (line == "DEBUG")
    {
        logger_level = simple_logger::level::DEBUG;
    }

    return boost::make_tuple(limboole_path, logger_level);
}

