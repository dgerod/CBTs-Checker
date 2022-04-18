#include <stdio.h>
#include <boost/filesystem.hpp> 
#include <boost/tuple/tuple.hpp>

#include "catch.hpp"
#include "simple_logger.hpp"
#include "read_configuration.hpp"

#include "tree_loader.hpp"
#include "cbt_validator.hpp"
#include "conditioned_behavior_tree.hpp"


const std::string TEST_ROOT_DIRECTORY = "./test";
const std::string CONFIG_FILE_PATH = "./config.txt";

const std::string DATA_DIRECTORY = TEST_ROOT_DIRECTORY + "/data/check_bt_valid";
const std::string TMP_DIRECTORY = TEST_ROOT_DIRECTORY + "/_temp_/check_bt_valid";
const cbtc::utils::configuration_params CONFIG_PARAMS = cbtc::utils::read_configuration(CONFIG_FILE_PATH);
const std::string LIMBOOLE_PATH = boost::get<0>(CONFIG_PARAMS);
const cbtc::utils::simple_logger::level LOGGER_LEVEL = boost::get<1>(CONFIG_PARAMS);


void create_directory(const std::string path)
{
    if (!boost::filesystem::exists(path))
    {
        boost::filesystem::create_directories(path);
    }    
}

SCENARIO("BT is valid")
{    
    cbtc::utils::simple_logger::enabled_level_ = LOGGER_LEVEL;

    WHEN("Tree 1")
    {
        const std::string tree_file = DATA_DIRECTORY + "/valid/tree_1.xml";
        const std::string init_state_file = DATA_DIRECTORY + "/valid/empty_state.txt";
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
        const std::string tree_file = DATA_DIRECTORY + "/valid/tree_2.xml";
        const std::string init_state_file = DATA_DIRECTORY + "/valid/tree_2.txt";        
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
        const std::string tree_file = DATA_DIRECTORY + "/valid/tree_3.xml";
        const std::string init_state_file = DATA_DIRECTORY + "/valid/empty_state.txt";        
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
    cbtc::utils::simple_logger::enabled_level_ = LOGGER_LEVEL;

    WHEN("Tree 1")
    {
        const std::string tree_file = DATA_DIRECTORY + "/no_valid/tree_1.xml";
        const std::string init_state_file = DATA_DIRECTORY + "/no_valid/empty_state.txt";        
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
        const std::string tree_file = DATA_DIRECTORY + "/no_valid/tree_2.xml";
        const std::string init_state_file = DATA_DIRECTORY + "/no_valid/empty_state.txt";
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
        const std::string tree_file = DATA_DIRECTORY + "/no_valid/tree_3.xml";
        const std::string init_state_file = DATA_DIRECTORY + "/no_valid/empty_state.txt";
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
        const std::string tree_file = DATA_DIRECTORY + "/no_valid/tree_4.xml";
        const std::string init_state_file = DATA_DIRECTORY + "/no_valid/empty_state.txt";
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