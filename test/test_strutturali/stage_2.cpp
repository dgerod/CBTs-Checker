//
//
// Stage 2: compute the sequence length of each node
//
//

#include <stdio.h>
#include "catch.hpp"

#include "tree_loader.hpp"
#include "conditioned_behavior_tree.hpp"


SCENARIO("Test of the second stage of the pipeline: compute sequence length for each node"){
        
    // In this case if we take the CBT with every type of node
    WHEN("completed the computations"){
        cbtc::conditioned_behavior_tree cbtree;            
        cbtc::tree_loader::bt_from_yarp_xml(cbtree, "./test/test_strutturali/stage_2/complete_CBT.xml");
        REQUIRE_NOTHROW(cbtree.compute_length_sequences());
        REQUIRE(cbtree.get_max_length_sequence() == 2);
    }
    
}
