#include <stdio.h>
#include "catch.hpp"

#include "tree_loader.hpp"
#include "conditioned_behavior_tree.hpp"

SCENARIO("Error loading BT from YARP XML file")
{
    WHEN("The XML file is not found")
    {
        cbtc::conditioned_behavior_tree cbtree;            
        REQUIRE_THROWS_WITH(cbtc::tree_loader::bt_from_yarp_xml(cbtree, "not_existing_path"), 
            "Exception occurred while opening the file: input xml file not found.");
    }
    
    WHEN("The XML file is malformed")
    {
        cbtc::conditioned_behavior_tree cbtree;            
        REQUIRE_THROWS_WITH(cbtc::tree_loader::bt_from_yarp_xml(cbtree, "./test/data/load_bt_from_xml/inputs/wrong_format/tree_1.xml"), 
            "Tree in input xml file is not well formated.");
    }

    WHEN("The XML file is malformed")
    {
        cbtc::conditioned_behavior_tree cbtree;            
        REQUIRE_THROWS_WITH(cbtc::tree_loader::bt_from_yarp_xml(cbtree, "./test/data/load_bt_from_xml/inputs/wrong_format/tree_2.xml"), 
            "Tree in input xml file is not well formated.");
    }

    WHEN("The XML file is malformed")
    {
        cbtc::conditioned_behavior_tree cbtree;            
        REQUIRE_THROWS_WITH(cbtc::tree_loader::bt_from_yarp_xml(cbtree, "./test/data/load_bt_from_xml/inputs/wrong_format/tree_3.xml"), 
            "Tree in input xml file is not well formated.");
    }

    WHEN("The XML file is malformed")
    {
        cbtc::conditioned_behavior_tree cbtree;            
        REQUIRE_THROWS_WITH(cbtc::tree_loader::bt_from_yarp_xml(cbtree, "./test/data/load_bt_from_xml/inputs/wrong_format/tree_4.xml"), 
            "Tree in input xml file is not well formated.");
    }
}

SCENARIO("Load BT from YARP XML file"){
    
    WHEN("The XML file contains no errors")
    {
        cbtc::conditioned_behavior_tree cbtree;            
        REQUIRE_NOTHROW(cbtc::tree_loader::bt_from_yarp_xml(cbtree, "./test/data/load_bt_from_xml/inputs/valid_format/tree_1.xml"));        
    }
    
    WHEN("The XML file contains no errors")
    {
        cbtc::conditioned_behavior_tree cbtree;            
        REQUIRE_NOTHROW(cbtc::tree_loader::bt_from_yarp_xml(cbtree, "./test/data/load_bt_from_xml/inputs/valid_format/tree_2.xml"));        
    }
    
    WHEN("The XML file contains no errors")
    {
        cbtc::conditioned_behavior_tree cbtree;            
        REQUIRE_NOTHROW(cbtc::tree_loader::bt_from_yarp_xml(cbtree, "./test/data/load_bt_from_xml/inputs/valid_format/tree_3.xml"));        
    }
    
    WHEN("The XML file contains no errors")
    {
        cbtc::conditioned_behavior_tree cbtree;            
        REQUIRE_NOTHROW(cbtc::tree_loader::bt_from_yarp_xml(cbtree, "./test/data/load_bt_from_xml/inputs/valid_format/tree_4.xml"));        
    }
    
    WHEN("The XML file contains no errors")
    {
        cbtc::conditioned_behavior_tree cbtree;            
        REQUIRE_NOTHROW(cbtc::tree_loader::bt_from_yarp_xml(cbtree, "./test/data/load_bt_from_xml/inputs/valid_format/tree_5.xml"));        
    }
    
    WHEN("The XML file contains no errors")
    {
        cbtc::conditioned_behavior_tree cbtree;            
        REQUIRE_NOTHROW(cbtc::tree_loader::bt_from_yarp_xml(cbtree, "./test/data/load_bt_from_xml/inputs/valid_format/tree_6.xml"));        
    }
    
    WHEN("The XML file contains no errors")
    {
        cbtc::conditioned_behavior_tree cbtree;            
        REQUIRE_NOTHROW(cbtc::tree_loader::bt_from_yarp_xml(cbtree, "./test/data/load_bt_from_xml/inputs/valid_format/tree_7.xml"));        
    }
    
    WHEN("The XML file contains no errors")
    {
        cbtc::conditioned_behavior_tree cbtree;            
        REQUIRE_NOTHROW(cbtc::tree_loader::bt_from_yarp_xml(cbtree, "./test/data/load_bt_from_xml/inputs/valid_format/complete_CBT.xml"));        
    }    
}
