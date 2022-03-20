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
#include "tree_loader.hpp"
#include "simple_logger.hpp"


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

bool find_text_in_file(const std::string file_path, const std::string text)
{
    bool found = false;

    std::ifstream file;     
    file.open(file_path);       
   
    std::string line;
    line = get_next_line(&file);
    if (line.substr(0,11).find(text) != std::string::npos)
    {
        found = true;
    }

    file.close();
    return found;
}

bool execute_limboole(const std::string limboole_path, const std::string output_path_bt_plans, const std::string output_path_gen_req){

    std::string command = limboole_path + " -s " + output_path_bt_plans + ">> " + output_path_gen_req;

    std::array<char, 128> buffer;
    std::string result;
    
    FILE* pipe = popen(command.c_str(), "r");
    
    while (fgets(buffer.data(), 128, pipe) != NULL) 
    {
        result += buffer.data();
    }
    pclose(pipe);    

    return find_text_in_file(output_path_gen_req, "SATISFIABLE");
}

bool validate_cbt_plan(const std::string limboole_path, std::string const output_folder) 
{
    std::string output_path_bt_plans = output_folder + cbtc::name_path_bt_plans;
    std::string output_path_gen_req = output_folder + cbtc::name_path_gen_req;
    
    remove(output_path_gen_req.c_str());
    return execute_limboole(limboole_path, output_path_bt_plans, output_path_gen_req);    
}

const std::string read_configuration(const std::string file_path)
{
    std::string limboole_path = "../dependencies/limboole/limboole";
    return limboole_path;
}

int main(int argc, const char * argv[]) 
{
    cbtc::utils::simple_logger::enabled_level_ = cbtc::utils::simple_logger::level::DEBUG;
    
    if (argc != 4)
    {
        std::cerr << "Input Error: expected 4 inputs to the program\n";
        std::cout << "  configuration file" << std::endl;
        std::cout << "  tree" << std::endl;
        std::cout << "  initial state" << std::endl;
        std::cout << "  output directory" << std::endl;
        
        return 1;
    }
    
    std::string limboole_path = read_configuration(argv[1]);
    std::string input_path = argv[2];
    std::string input_req = argv[3]; 
    std::string output_folder = argv[4];
        
    std::cout << "Parameters" << std::endl;
    std::cout << "  - limboole path: " << limboole_path << std::endl;
    std::cout << "  - tree: " << input_path << std::endl;
    std::cout << "  - initial state: " << input_req << std::endl;
    std::cout << "  - output directory: " << output_folder << std::endl;
    std::cout << std::endl;

    bool valid = false;

    try
    {
        cbtc::conditioned_behavior_tree cbtree;    
        cbtc::tree_loader::bt_from_yarp_xml(cbtree, input_path);
        cbtree.generate_initial_requirements(input_req, output_folder);
        valid = validate_cbt_plan(limboole_path, output_folder);
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        exit(1);
    }

    std::cout << "CBT is valid? " << (valid ? "YES" : "NO") << std::endl;
    return 0;
}
