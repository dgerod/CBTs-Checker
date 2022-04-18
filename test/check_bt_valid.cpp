#include <stdio.h>
#include <boost/filesystem.hpp> 

#include "catch.hpp"
#include "simple_logger.hpp"

#include "tree_loader.hpp"
#include "cbt_validator.hpp"
#include "conditioned_behavior_tree.hpp"


void create_directory(const std::string path)
{
    if (!boost::filesystem::exists(path))
    {
        boost::filesystem::create_directories(path);
    }    
}

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
const std::string TMP_DIRECTORY = "./test/_temp_/check_bt_valid";

SCENARIO("BT is valid")
{    
    using cbtc::utils::simple_logger;
    simple_logger::enabled_level_ = simple_logger::level::ERROR;

    WHEN("Tree 1")
    {
        const std::string tree_file = "./test/data/check_bt_valid/valid/tree_1.xml";
        const std::string init_state_file = "./test/data/check_bt_valid/valid/empty_state.txt";
        const std::string tmp_directory = TMP_DIRECTORY + "/valid/1";

        create_directory(tmp_directory);
        
        cbtc::conditioned_behavior_tree cbtree;       
        cbtc::tree_loader::bt_from_yarp_xml(cbtree, tree_file);
        
        THEN("valid")
        {
            cbtc::cbt_validator validator(LIMBOOLE_PATH, tmp_directory);            
            REQUIRE(validator.validate(cbtree, init_state_file));
        }
    }
    
    WHEN("Tree 2")
    {
        const std::string tree_file = "./test/data/check_bt_valid/valid/tree_2.xml";
        const std::string init_state_file = "./test/data/check_bt_valid/valid/empty_state.txt";        
        const std::string tmp_directory = TMP_DIRECTORY + "/valid/2";

        create_directory(tmp_directory);

        cbtc::conditioned_behavior_tree cbtree;       
        cbtc::tree_loader::bt_from_yarp_xml(cbtree, tree_file);
        
        THEN("valid")
        {
            cbtc::cbt_validator validator(LIMBOOLE_PATH, tmp_directory);            
            REQUIRE(validator.validate(cbtree, init_state_file));
        }
    } 

    WHEN("Tree 3")
    {
        const std::string tree_file = "./test/data/check_bt_valid/valid/tree_3.xml";
        const std::string init_state_file = "./test/data/check_bt_valid/valid/empty_state.txt";        
        const std::string tmp_directory = TMP_DIRECTORY + "/valid/3";

        create_directory(tmp_directory);

        cbtc::conditioned_behavior_tree cbtree;       
        cbtc::tree_loader::bt_from_yarp_xml(cbtree, tree_file);
        
        THEN("valid")
        {
            cbtc::cbt_validator validator(LIMBOOLE_PATH, tmp_directory);            
            REQUIRE(validator.validate(cbtree, init_state_file));
        }
    } 
}

SCENARIO("BT is NOT valid")
{
    using cbtc::utils::simple_logger;
    simple_logger::enabled_level_ = simple_logger::level::DEBUG;

    WHEN("Tree 1")
    {
        const std::string tree_file = "./test/data/check_bt_valid/no_valid/tree_1.xml";
        const std::string init_state_file = "./test/data/check_bt_valid/no_valid/empty_state.txt";        
        const std::string tmp_directory = TMP_DIRECTORY + "/no_valid/1";

        create_directory(tmp_directory);

        cbtc::conditioned_behavior_tree cbtree;       
        cbtc::tree_loader::bt_from_yarp_xml(cbtree, tree_file);
        
        THEN("NOT valid")
        {
            cbtc::cbt_validator validator(LIMBOOLE_PATH, tmp_directory);            
            REQUIRE_FALSE(validator.validate(cbtree, init_state_file));
        }
    }
       
    WHEN("Tree 2")
    {
        const std::string tree_file = "./test/data/check_bt_valid/no_valid/tree_2.xml";
        const std::string init_state_file = "./test/data/check_bt_valid/no_valid/empty_state.txt";
        const std::string tmp_directory = TMP_DIRECTORY + "/no_valid/2";

        create_directory(tmp_directory);

        cbtc::conditioned_behavior_tree cbtree;       
        cbtc::tree_loader::bt_from_yarp_xml(cbtree, tree_file);
        
        THEN("NOT valid")
        {
            cbtc::cbt_validator validator(LIMBOOLE_PATH, tmp_directory);            
            REQUIRE_FALSE(validator.validate(cbtree, init_state_file));
        }
    }
    
    WHEN("Tree 3")
    {
        const std::string tree_file = "./test/data/check_bt_valid/no_valid/tree_3.xml";
        const std::string init_state_file = "./test/data/check_bt_valid/no_valid/empty_state.txt";
        const std::string tmp_directory = TMP_DIRECTORY + "/no_valid/3";

        create_directory(tmp_directory);

        cbtc::conditioned_behavior_tree cbtree;       
        cbtc::tree_loader::bt_from_yarp_xml(cbtree, tree_file);
        
        THEN("NOT valid")
        {
            cbtc::cbt_validator validator(LIMBOOLE_PATH, tmp_directory);            
            REQUIRE_FALSE(validator.validate(cbtree, init_state_file));
        }
    }  
 
    WHEN("Tree 4")
    {
        const std::string tree_file = "./test/data/check_bt_valid/no_valid/tree_4.xml";
        const std::string init_state_file = "./test/data/check_bt_valid/no_valid/empty_state.txt";
        const std::string tmp_directory = TMP_DIRECTORY + "/no_valid/4";

        create_directory(tmp_directory);

        cbtc::conditioned_behavior_tree cbtree;       
        cbtc::tree_loader::bt_from_yarp_xml(cbtree, tree_file);
        
        THEN("NOT valid")
        {
            cbtc::cbt_validator validator(LIMBOOLE_PATH, tmp_directory);            
            REQUIRE_FALSE(validator.validate(cbtree, init_state_file));
        }
    }      
}