//
//
// Stage 1: read the XML file
//
//

#include <stdio.h>
#include "catch.hpp"

#include "tree_loader.hpp"
#include "conditioned_behavior_tree.hpp"


SCENARIO("Load BT from YARP XML file"){
        
    // First read_file tries to open the file
    // Check the branch given by file not found
    WHEN("The XML file is not found"){
        cbtc::conditioned_behavior_tree cbtree;            
        REQUIRE_THROWS_WITH(cbtc::tree_loader::bt_from_yarp_xml(cbtree, "not_existing_path"), 
            "Exception occurred while opening the file: input xml file not found.");
    }
    
    // If it manages it starts to read the actions
    // We have to check all the branches given by errors in the XML file
    WHEN("The XML file contains a bad formed action"){
        cbtc::conditioned_behavior_tree cbtree;            
        REQUIRE_THROWS_WITH(cbtc::tree_loader::bt_from_yarp_xml(cbtree, "./test/test_strutturali/load_bt_from_xml/inputs/stage_1_no_ActionTemplate.xml"), 
            "Input XML file bad format: object ActionTemplate must contain object YARPAction");
    }

    WHEN("The XML file contains actions with contrastant preconditions"){
        cbtc::conditioned_behavior_tree cbtree;            
         REQUIRE_THROWS_WITH(cbtc::tree_loader::bt_from_yarp_xml(cbtree, "./test/test_strutturali/load_bt_from_xml/inputs/stage_1_contrastant_preconditions0.xml"), 
            "Input XML file bad format: action cannot have 'c' and 'not c' as pre-conditions");
    }

    WHEN("The XML file contains actions with contrastant preconditions"){
        cbtc::conditioned_behavior_tree cbtree;            
        REQUIRE_THROWS_WITH(cbtc::tree_loader::bt_from_yarp_xml(cbtree, "./test/test_strutturali/load_bt_from_xml/inputs/stage_1_contrastant_preconditions1.xml"), 
            "Input XML file bad format: action cannot have 'c' and 'not c' as pre-conditions");
    }

    WHEN("The XML file contains actions with contrastant postconditions"){
        cbtc::conditioned_behavior_tree cbtree;            
        REQUIRE_THROWS_WITH(cbtc::tree_loader::bt_from_yarp_xml(cbtree, "./test/test_strutturali/load_bt_from_xml/inputs/stage_1_contrastant_postconditions0.xml"), 
            "Input XML file bad format: action cannot have 'c' and 'not c' as post-conditions");
    }

    WHEN("The XML file contains actions with contrastant postconditions"){
        cbtc::conditioned_behavior_tree cbtree;            
        REQUIRE_THROWS_WITH(cbtc::tree_loader::bt_from_yarp_xml(cbtree, "./test/test_strutturali/load_bt_from_xml/inputs/stage_1_contrastant_postconditions1.xml"), 
            "Input XML file bad format: action cannot have 'c' and 'not c' as post-conditions");
    }
    
    // Once completed the actions read_file starts to read the BT
    // We have to check all the branches given by errors in the XML file
    // CBT beginning
    WHEN("The XML file contains a BT not starting with the root"){
        cbtc::conditioned_behavior_tree cbtree;            
        REQUIRE_THROWS_WITH(cbtc::tree_loader::bt_from_yarp_xml(cbtree, "./test/test_strutturali/load_bt_from_xml/inputs/stage_1_no_root.xml"), 
            "Input XML file bad format: Behavior Tree must have a root");
    }

    WHEN("The XML file contains a BT without the tag <BehaviorTree> following the tag <root>"){
        cbtc::conditioned_behavior_tree cbtree;            
        REQUIRE_THROWS_WITH(cbtc::tree_loader::bt_from_yarp_xml(cbtree, "./test/test_strutturali/load_bt_from_xml/inputs/stage_1_no_BehaviorTree.xml"), 
            "Input XML file bad format: root must be followed by <BehaviorTree>");
    }

    // CBT internal
    WHEN("The XML file contains a BT with a not recognized CFN"){
        cbtc::conditioned_behavior_tree cbtree;            
        REQUIRE_THROWS_WITH(cbtc::tree_loader::bt_from_yarp_xml(cbtree, "./test/test_strutturali/load_bt_from_xml/inputs/stage_1_not_recognized_CFN.xml"), 
            "Input XML file bad format: Behavior Tree bad format");
    }

    WHEN("The XML file contains a BT with a not closed sequence tag"){
        cbtc::conditioned_behavior_tree cbtree;            
        REQUIRE_THROWS_WITH(cbtc::tree_loader::bt_from_yarp_xml(cbtree, "./test/test_strutturali/load_bt_from_xml/inputs/stage_1_not_recognized_CFN.xml"), 
            "Input XML file bad format: Behavior Tree bad format");
    }

    WHEN("The XML file contains a BT with a not closed fallback tag"){
        cbtc::conditioned_behavior_tree cbtree;            
        REQUIRE_THROWS_WITH(cbtc::tree_loader::bt_from_yarp_xml(cbtree, "./test/test_strutturali/load_bt_from_xml/inputs/stage_1_not_recognized_CFN.xml"), 
            "Input XML file bad format: Behavior Tree bad format");
    }

    WHEN("The XML file contains a BT with a not closed parallel tag"){
        cbtc::conditioned_behavior_tree cbtree;            
        REQUIRE_THROWS_WITH(cbtc::tree_loader::bt_from_yarp_xml(cbtree, "./test/test_strutturali/load_bt_from_xml/inputs/stage_1_not_recognized_CFN.xml"), 
        "Input XML file bad format: Behavior Tree bad format");
    }

    // CBT ending
    WHEN("The XML file contains a BT in which the tag <Behavior Tree> is not closed"){
        cbtc::conditioned_behavior_tree cbtree;            
        REQUIRE_THROWS_WITH(cbtc::tree_loader::bt_from_yarp_xml(cbtree, "./test/test_strutturali/load_bt_from_xml/inputs/stage_1_no_closed_BehaviorTree.xml"), 
            "Input XML file bad format: object <Behavior Tree> must be closed");
    }

    WHEN("The XML file contains a BT in which the tag <root> is not closed"){
        cbtc::conditioned_behavior_tree cbtree;            
        REQUIRE_THROWS_WITH(cbtc::tree_loader::bt_from_yarp_xml(cbtree, "./test/test_strutturali/load_bt_from_xml/inputs/stage_1_no_closed_root.xml"), 
            "Input XML file bad format: object <root> must be closed");
    }
    
    // Case of XML file with no errors --> we need to build a CBT that allows as to cover all the statements still uncovered
    WHEN("The XML file contains no errors"){
        cbtc::conditioned_behavior_tree cbtree;            
        REQUIRE_NOTHROW(cbtc::tree_loader::bt_from_yarp_xml(cbtree, "./test/test_strutturali/load_bt_from_xml/inputs/complete_CBT.xml"));
        REQUIRE(cbtree.get_actions().size() == 4);
    }
}
