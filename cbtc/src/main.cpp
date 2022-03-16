//
//  main.cpp
//  CBT_Requirements_Calculator
//
//  Created by E.Giunchiglia on 02/06/18.
//  Copyright © 2018 Eleonora Giunchiglia. All rights reserved.
//

#include <stdio.h>
#include <string>
#include "conditioned_behavior_tree.hpp"
#include "simple_logger.hpp"


const std::string read_configuration(const std::string file_path)
{
    std::string limboole_path = "../dependencies/limboole/limboole";
    return limboole_path;
}

void execute_limboole(const std::string limboole_path, const std::string output_path_bt_plans, const std::string output_path_gen_req){

    std::string command = limboole_path + " -s " + output_path_bt_plans + ">> " + output_path_gen_req;

    std::array<char, 128> buffer;
    std::string result;
    
    FILE* pipe = popen(command.c_str(), "r");
    
    while (fgets(buffer.data(), 128, pipe) != NULL) 
    {
        result += buffer.data();
    }
    pclose(pipe);    
}

void validate_cbt_plan(const std::string limboole_path, std::string const output_folder) 
{
    std::string output_path_bt_plans = output_folder + cbt::name_path_bt_plans;
    std::string output_path_gen_req = output_folder + cbt::name_path_gen_req;
    
    remove(output_path_gen_req.c_str());
    execute_limboole(limboole_path, output_path_bt_plans, output_path_gen_req);
    
    std::ifstream general_requirements;     
    general_requirements.open(output_path_gen_req);        
    general_requirements.close();
}

int main(int argc, const char * argv[]) 
{
    cbt::utils::simple_logger::enabled_level_ = cbt::utils::simple_logger::level::DEBUG;
    
    if (argc != 4)
    {
        std::cerr << "Input Error: expected 4 inputs to the program\n";
        std::cout << "  tree" << std::endl;
        std::cout << "  initial state" << std::endl;
        std::cout << "  output directory" << std::endl;

        return 1;
    }
    
    std::string input_path = argv[1];
    std::string input_req = argv[2]; 
    std::string output_folder = argv[3];
    std::string limboole_path = read_configuration("config.txt");
    
    std::cout << "Parameters" << std::endl;
    std::cout << "  - tree: " << input_path << std::endl;
    std::cout << "  - initial state: " << input_req << std::endl;
    std::cout << "  - output directory: " << output_folder << std::endl;
    std::cout << "  - limboole path: " << limboole_path << std::endl;
    std::cout << std::endl;

    try
    {
        cbt::conditioned_behavior_tree cbtree;
        cbtree.compute_initial_requirements(input_path, input_req, output_folder);
        validate_cbt_plan(limboole_path, output_folder);
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        exit(1);
    }

    std::cout << "Computation of requirements completed" << std::endl;
    return 0;
}
