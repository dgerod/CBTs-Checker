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
#include <boost/tuple/tuple.hpp>

#include "simple_logger.hpp"
#include "read_configuration.hpp"
#include "conditioned_behavior_tree.hpp"
#include "cbt_validator.hpp"
#include "tree_loader.hpp"


const std::string RESULT_FILE_NAME = "cbt_valid.txt";   


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

int main(int argc, const char * argv[]) 
{    
    if (argc != 6)
    {
        std::cerr << "Input Error: expected 4 inputs to the program\n";
        std::cout << "  configuration file" << std::endl;        
        std::cout << "  tree" << std::endl;
        std::cout << "  initial state" << std::endl;
        std::cout << "  temp directory" << std::endl;
        std::cout << "  output directory" << std::endl;
        
        return 1;
    }

    const cbtc::utils::configuration_params configuration_params = cbtc::utils::read_configuration(argv[1]);
    const std::string limboole_app_path = boost::get<0>(configuration_params);
    const cbtc::utils::simple_logger::level logger_level = boost::get<1>(configuration_params);

    const std::string input_tree_file = argv[2];
    const std::string input_requirements_file = argv[3]; 
    const std::string temp_folder = argv[4];
    const std::string output_folder = argv[5];
    cbtc::utils::simple_logger::enabled_level_ = logger_level;        

    std::cout << "Check if a Conditional Behavior Tree (CBT) could be executed" << std::endl;    
    std::cout << std::endl;
    std::cout << "Parameters" << std::endl;
    std::cout << "  - limboole path: " << limboole_app_path << std::endl;
    std::cout << "  - tree file: " << input_tree_file << std::endl;
    std::cout << "  - initial state file: " << input_requirements_file << std::endl;
    std::cout << "  - temp directory: " << temp_folder << std::endl;
    std::cout << "  - output directory: " << output_folder << std::endl;
    std::cout << "  - logger: " << static_cast<int>(cbtc::utils::simple_logger::enabled_level_) << std::endl;
    std::cout << std::endl;
    
    cbtc::conditioned_behavior_tree cbt;   
    bool well_formated = true;
    bool bt_valid = true;

    try
    {
        cbtc::tree_loader::bt_from_yarp_xml(cbt, input_tree_file);
    }
    catch(const std::exception &e)
    {
        well_formated = false;
    }

    try
    {
        if (well_formated)
        {
            cbtc::cbt_validator cbt_validator(limboole_app_path, temp_folder);    
            bt_valid = cbt_validator.validate(cbt, input_requirements_file);
        }
    }
    catch(const std::exception &e)
    {
        bt_valid = false;
    }

    write_result(output_folder, bt_valid);

    std::cout << std::endl;
    std::cout << "CBT is well formated? " << (well_formated ? "YES" : "NO") << std::endl;
    std::cout << "CBT is valid? " << (bt_valid ? "YES" : "NO") << std::endl;

    return EXIT_SUCCESS;
}
