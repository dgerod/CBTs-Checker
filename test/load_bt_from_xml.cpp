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

    WHEN("The XML file is malformed")
    {
        cbtc::conditioned_behavior_tree cbtree;            
        REQUIRE_THROWS_WITH(cbtc::tree_loader::bt_from_yarp_xml(cbtree, "./test/data/load_bt_from_xml/inputs/wrong_format/req_f1_1.xml"), 
            "Input XML file bad format: Behavior Tree must have a root");
    }
    
    WHEN("The XML file is malformed")
    {
        cbtc::conditioned_behavior_tree cbtree;            
        REQUIRE_THROWS_WITH(cbtc::tree_loader::bt_from_yarp_xml(cbtree, "./test/data/load_bt_from_xml/inputs/wrong_format/req_f1_2.xml"), 
            "Input XML file bad format: root must be followed by <BehaviorTree>");
    }

    WHEN("The XML file is malformed")
    {
        cbtc::conditioned_behavior_tree cbtree;            
        REQUIRE_THROWS_WITH(cbtc::tree_loader::bt_from_yarp_xml(cbtree, "./test/data/load_bt_from_xml/inputs/wrong_format/req_f1_3.xml"), 
            "Input XML file bad format: Behavior Tree bad format");
    }

    WHEN("The XML file is malformed")
    {
        cbtc::conditioned_behavior_tree cbtree;            
        REQUIRE_THROWS_WITH(cbtc::tree_loader::bt_from_yarp_xml(cbtree, "./test/data/load_bt_from_xml/inputs/wrong_format/req_f2_1.xml"), 
            "Tree in input xml file is not well formated.");
    }
    
    WHEN("The XML file is malformed")
    {
        cbtc::conditioned_behavior_tree cbtree;            
        REQUIRE_THROWS_WITH(cbtc::tree_loader::bt_from_yarp_xml(cbtree, "./test/data/load_bt_from_xml/inputs/wrong_format/req_f2_2.xml"), 
            "Tree in input xml file is not well formated.");
    }
    
    WHEN("The XML file is malformed")
    {
        cbtc::conditioned_behavior_tree cbtree;            
        REQUIRE_THROWS_WITH(cbtc::tree_loader::bt_from_yarp_xml(cbtree, "./test/data/load_bt_from_xml/inputs/wrong_format/req_f2_3.xml"), 
            "Tree in input xml file is not well formated.");
    }
    
    WHEN("The XML file is malformed")
    {
        cbtc::conditioned_behavior_tree cbtree;            
        REQUIRE_THROWS_WITH(cbtc::tree_loader::bt_from_yarp_xml(cbtree, "./test/data/load_bt_from_xml/inputs/wrong_format/req_f3_1.xml"), 
            "Input XML file bad format: after \"not \" Pre and Post conditions cannot contain whitespaces");
    }
    
    WHEN("The XML file is malformed")
    {
        cbtc::conditioned_behavior_tree cbtree;            
        REQUIRE_THROWS_WITH(cbtc::tree_loader::bt_from_yarp_xml(cbtree, "./test/data/load_bt_from_xml/inputs/wrong_format/req_f3_2.xml"), 
            "Input XML file bad format: positive Pre and Post conditions cannot contain whitespaces");
    }
    
    WHEN("The XML file is malformed")
    {
        cbtc::conditioned_behavior_tree cbtree;            
        REQUIRE_THROWS_WITH(cbtc::tree_loader::bt_from_yarp_xml(cbtree, "./test/data/load_bt_from_xml/inputs/wrong_format/req_f3_3.xml"), 
            "Exception occurred while opening the file: input xml file not found.");
    }
    
    WHEN("The XML file is malformed")
    {
        cbtc::conditioned_behavior_tree cbtree;            
        REQUIRE_THROWS_WITH(cbtc::tree_loader::bt_from_yarp_xml(cbtree, "./test/data/load_bt_from_xml/inputs/wrong_format/req_f4_1.xml"), 
            "Action not defined in the vocabulary");
    }
    
    WHEN("The XML file is malformed")
    {
        cbtc::conditioned_behavior_tree cbtree;            
        REQUIRE_THROWS_WITH(cbtc::tree_loader::bt_from_yarp_xml(cbtree, "./test/data/load_bt_from_xml/inputs/wrong_format/req_f4_2.xml"), 
            "Action not defined in the vocabulary");
    }

    WHEN("The XML file is malformed")
    {
        cbtc::conditioned_behavior_tree cbtree;            
        REQUIRE_THROWS_WITH(cbtc::tree_loader::bt_from_yarp_xml(cbtree, "./test/data/load_bt_from_xml/inputs/wrong_format/req_f5.xml"), 
            "Tree in input xml file is not well formated.");
    }
    
    WHEN("The XML file is malformed")
    {
        cbtc::conditioned_behavior_tree cbtree;            
        REQUIRE_THROWS_WITH(cbtc::tree_loader::bt_from_yarp_xml(cbtree, "./test/data/load_bt_from_xml/inputs/wrong_format/req_f6.xml"), 
            "Input XML file bad format: action cannot have 'c' and 'not c' as pre-conditions");
    }
    
    WHEN("The XML file is malformed")
    {
        cbtc::conditioned_behavior_tree cbtree;            
        REQUIRE_THROWS_WITH(cbtc::tree_loader::bt_from_yarp_xml(cbtree, "./test/data/load_bt_from_xml/inputs/wrong_format/req_f7.xml"), 
            "Input XML file bad format: action cannot have 'c' and 'not c' as post-conditions");
    }
    
    
    //WHEN("The XML file is malformed")
    //{
    //  cbtc::conditioned_behavior_tree cbtree;            
    //  REQUIRE_THROWS_WITH(cbtc::tree_loader::bt_from_yarp_xml(cbtree, "./test/data/load_bt_from_xml/inputs/wrong_format/req_f8.xml"), 
    //  "Tree in input xml file is not well formated.");
    //}
    
    //WHEN("The XML file is malformed")
    //{
    //  cbtc::conditioned_behavior_tree cbtree;            
    //  REQUIRE_THROWS_WITH(cbtc::tree_loader::bt_from_yarp_xml(cbtree, "./test/data/load_bt_from_xml/inputs/wrong_format/req_f9.xml"), 
    //  "Tree in input xml file is not well formated.");
    //}    
}

SCENARIO("Load BT from YARP XML file"){
    
    WHEN("The XML file contains no errors")
    {
        cbtc::conditioned_behavior_tree cbtree;            
        REQUIRE_NOTHROW(cbtc::tree_loader::bt_from_yarp_xml(cbtree, "./test/data/load_bt_from_xml/inputs/correct_format/tree_1.xml"));        
    }
    
    WHEN("The XML file contains no errors")
    {
        cbtc::conditioned_behavior_tree cbtree;            
        REQUIRE_NOTHROW(cbtc::tree_loader::bt_from_yarp_xml(cbtree, "./test/data/load_bt_from_xml/inputs/correct_format/tree_2.xml"));        
    }
    
    WHEN("The XML file contains no errors")
    {
        cbtc::conditioned_behavior_tree cbtree;            
        REQUIRE_NOTHROW(cbtc::tree_loader::bt_from_yarp_xml(cbtree, "./test/data/load_bt_from_xml/inputs/correct_format/tree_3.xml"));        
    }
    
    WHEN("The XML file contains no errors")
    {
        cbtc::conditioned_behavior_tree cbtree;            
        REQUIRE_NOTHROW(cbtc::tree_loader::bt_from_yarp_xml(cbtree, "./test/data/load_bt_from_xml/inputs/correct_format/tree_4.xml"));        
    }
    
    WHEN("The XML file contains no errors")
    {
        cbtc::conditioned_behavior_tree cbtree;            
        REQUIRE_NOTHROW(cbtc::tree_loader::bt_from_yarp_xml(cbtree, "./test/data/load_bt_from_xml/inputs/correct_format/tree_5.xml"));        
    }
    
    WHEN("The XML file contains no errors")
    {
        cbtc::conditioned_behavior_tree cbtree;            
        REQUIRE_NOTHROW(cbtc::tree_loader::bt_from_yarp_xml(cbtree, "./test/data/load_bt_from_xml/inputs/correct_format/tree_6.xml"));        
    }
    
    WHEN("The XML file contains no errors")
    {
        cbtc::conditioned_behavior_tree cbtree;            
        REQUIRE_NOTHROW(cbtc::tree_loader::bt_from_yarp_xml(cbtree, "./test/data/load_bt_from_xml/inputs/correct_format/tree_7.xml"));        
    }
    
    WHEN("The XML file contains no errors")
    {
        cbtc::conditioned_behavior_tree cbtree;            
        REQUIRE_NOTHROW(cbtc::tree_loader::bt_from_yarp_xml(cbtree, "./test/data/load_bt_from_xml/inputs/correct_format/complete_CBT.xml"));        
    }    
}
