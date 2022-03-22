//
//  main.cpp
//  CBT_Requirements_Calculator
//
//  Created by E.Giunchiglia on 02/06/18.
//  Copyright © 2018 Eleonora Giunchiglia. All rights reserved.
//

#include <stdio.h>
#include <string>
#include <iostream>

#include "conditioned_behavior_tree.hpp"
#include "cbt_validator.hpp"
#include "tree_loader.hpp"
#include "simple_logger.hpp"


const std::string RESULT_FILE_NAME = "cbt_valid.txt";   


using cbtc::utils::simple_logger;


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

void write_result(std::string const output_folder, bool valid)
{
    std::string file_path = output_folder + "/" + RESULT_FILE_NAME;

    std::ofstream file;
    file.exceptions (std::ofstream::failbit | std::ofstream::badbit );      
    file.open(file_path, std::ios::out);       
    if (!file.good())
    {
        throw std::runtime_error("Exception occurred while creating output file for BT plans.");	
    }

    file << std::string(valid ? "YES" : "NO") << std::endl;

    file.close();
}

const std::string read_configuration(const std::string file_path)
{
    std::ifstream file;     
    file.open(file_path);       
   
    std::string line;
    line = get_next_line(&file);
    std::string limboole_path = line;

    file.close();
    return limboole_path;
}

int main(int argc, const char * argv[]) 
{
    simple_logger::enabled_level_ = simple_logger::level::INFO;
    
    if (argc != 5)
    {
        std::cerr << "Input Error: expected 4 inputs to the program\n";
        std::cout << "  configuration file" << std::endl;
        std::cout << "  tree" << std::endl;
        std::cout << "  initial state" << std::endl;
        std::cout << "  output directory" << std::endl;
        
        return 1;
    }
    
    std::string limboole_app_path = read_configuration(argv[1]);
    std::string input_tree_file = argv[2];
    std::string input_requirements_file = argv[3]; 
    std::string output_folder = argv[4];

    std::cout << "Check if a Conditional Behavior Tree (CBT) could be executed" << std::endl;    
    std::cout << std::endl;
    std::cout << "Parameters" << std::endl;
    std::cout << "  - limboole path: " << limboole_app_path << std::endl;
    std::cout << "  - tree: " << input_tree_file << std::endl;
    std::cout << "  - initial state: " << input_requirements_file << std::endl;
    std::cout << "  - output directory: " << output_folder << std::endl;
    std::cout << std::endl;

    bool valid = false;

    try
    {
        cbtc::conditioned_behavior_tree cbt;    
        cbtc::tree_loader::bt_from_yarp_xml(cbt, input_tree_file);

        cbtc::cbt_validator cbt_validator(limboole_app_path, output_folder);    
        valid = cbt_validator.validate(cbt, input_requirements_file);
        write_result(output_folder, valid);
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        exit(1);
    }

    std::cout << std::endl;
    std::cout << "CBT is valid? " << (valid ? "YES" : "NO") << std::endl;
    return 0;
}
