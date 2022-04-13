#include <stdio.h>
#include "catch.hpp"

#include "tree_loader.hpp"
#include "cbt_validator.hpp"
#include "conditioned_behavior_tree.hpp"


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

const std::string CONFIG_FILE_PATH = "./test/config.txt";
const std::string LIMBOOLE_PATH = read_configuration(CONFIG_FILE_PATH);
const std::string TMP_DIRECTORY = "./test/_temp_";

SCENARIO("BT is valid")
{    
    WHEN("Tree 1")
    {
        std::string tree_file = "./test/data/check_bt_valid/valid/tree_1.xml";
        std::string init_state_file = "./test/data/check_bt_valid/no_valid/init_state.txt";
        
        cbtc::conditioned_behavior_tree cbtree;       
        cbtc::tree_loader::bt_from_yarp_xml(cbtree, tree_file);
        
        THEN("valid")
        {
            cbtc::cbt_validator validator(LIMBOOLE_PATH, TMP_DIRECTORY);            
            REQUIRE(validator.validate(cbtree, init_state_file));
        }
    }
}

SCENARIO("BT is NOT valid")
{
    WHEN("Tree 1")
    {
        std::string tree_file = "./test/data/check_bt_valid/no_valid/tree_1.xml";
        std::string init_state_file = "./test/data/check_bt_valid/no_valid/init_state.txt";

        cbtc::conditioned_behavior_tree cbtree;       
        cbtc::tree_loader::bt_from_yarp_xml(cbtree, tree_file);
        
        THEN("NOT valid")
        {
            cbtc::cbt_validator validator(LIMBOOLE_PATH, TMP_DIRECTORY);            
            REQUIRE_FALSE(validator.validate(cbtree, init_state_file));
        }
    }
       
    WHEN("Tree 2")
    {
        std::string tree_file = "./test/data/check_bt_valid/no_valid/tree_2.xml";
        std::string init_state_file = "./test/data/check_bt_valid/no_valid/init_state.txt";

        cbtc::conditioned_behavior_tree cbtree;       
        cbtc::tree_loader::bt_from_yarp_xml(cbtree, tree_file);
        
        THEN("NOT valid")
        {
            cbtc::cbt_validator validator(LIMBOOLE_PATH, TMP_DIRECTORY);            
            REQUIRE_FALSE(validator.validate(cbtree, init_state_file));
        }
    }
        
    WHEN("Tree 3")
    {
        std::string tree_file = "./test/data/check_bt_valid/no_valid/tree_3.xml";
        std::string init_state_file = "./test/data/check_bt_valid/no_valid/init_state.txt";

        cbtc::conditioned_behavior_tree cbtree;       
        cbtc::tree_loader::bt_from_yarp_xml(cbtree, tree_file);
        
        THEN("NOT valid")
        {
            cbtc::cbt_validator validator(LIMBOOLE_PATH, TMP_DIRECTORY);            
            REQUIRE_FALSE(validator.validate(cbtree, init_state_file));
        }
    }  
}
