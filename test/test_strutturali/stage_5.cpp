//
//
//  Stage 5: compute a model of the representation and derive the initial requirements
//
//

#include <stdio.h>
#include "catch.hpp"

#include "conditioned_behavior_tree.hpp"


SCENARIO("Test of the fifth stage of the pipeline: call limboole and write model on file"){

    cbtc::conditioned_behavior_tree cbtree;
    
    // Here there is a unique branch
    REQUIRE_NOTHROW(
        cbtree.generate_initial_requirements("./test/test_strutturali/stage_5/initial_req.tx", 
            "./test/test_strutturali/stage_5/sym_output/BTplants.txt"));
    
    std::ifstream CBT_plans("./test/test_strutturali/stage_5/sym_output/BTplans.txt");
    REQUIRE(CBT_plans.good());
    
    std::ifstream general_req("./test/test_strutturali/stage_5/sym_output/general_requirements.txt");
    REQUIRE(general_req.good());
    
    std::ifstream initial_req("./test/test_strutturali/stage_5/sym_output/initial_requirements.txt");
    REQUIRE(initial_req.good());
}
