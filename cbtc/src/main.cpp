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


using namespace cbt::utils;


int main(int argc, const char * argv[]) 
{
    simple_logger::enabled_level_ = simple_logger::level::DEBUG;

    if (argc != 5)
    {
        std::cerr << "Input Error: expected 4 inputs to the program\n";
        std::cout << "  tree" << std::endl;
        std::cout << "  initial state" << std::endl;
        std::cout << "  output directory" << std::endl;
        std::cout << "  limboole path" << std::endl;

        return 1;
    }
    
    std::string input_path = argv[1];
    std::string input_req = argv[2]; 
    std::string output_folder = argv[3];
    std::string limboole_path = argv[4];
    
    std::cout << "Parameters" << std::endl;
    std::cout << "  - tree: " << input_path << std::endl;
    std::cout << "  - initial state: " << input_req << std::endl;
    std::cout << "  - output directory: " << output_folder << std::endl;
    std::cout << "  - limboole path: " << limboole_path << std::endl;
    std::cout << std::endl;

    try
    {
        cbt::conditioned_behavior_tree cbtree;
        cbtree.compute_initial_requirements(input_path, input_req, output_folder, limboole_path);
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        exit(1);
    }

    std::cout << "Computation of requirements completed" << std::endl;
    return 0;
}
