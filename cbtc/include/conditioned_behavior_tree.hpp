//
//  cbt.hpp
//  CBT_Requirements_Calculator
//
//  Created by E.Giunchiglia on 29/05/18.
//  Copyright © 2018 Eleonora Giunchiglia. All rights reserved.
//

#pragma once
 
#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <set>
#include <sstream>
#include <map>
#include "action.hpp"
#include "control_flow_node.hpp"


namespace cbtc {
    
const std::string name_path_gen_req = "general_requirements.txt";
const std::string name_path_bt_plans = "BTplans.txt";

class conditioned_behavior_tree
{
public:
    conditioned_behavior_tree();
    ~conditioned_behavior_tree();
    
    control_flow_node& get_root_node();
    std::set<action> get_actions();

    void insert_action(action const* const new_action);

    /**
     * Function handling the pipeline of function calls to generate the requirements.
     * \param requirements_path string containing the path to the input .txt file with the initial requirements
     * \param output_folder string containing the path to the output folder
     */
    void generate_initial_requirements(std::string const requirements_path, std::string const output_folder);

protected:    

    /**
     * Fuction returning the sequence length of the CBT.
     */
    int get_max_length_sequence();
    
    /**
     * Function to write the state graph to the output file.
     * \param path string containing the path to the output folder
     */
    void create_state_graph(std::string const path, std::string const req_path);
    
    /**
     * Function to write the plans of the CBT to the output file.
     * \param path string containing the path to the output folder
     */
    void create_cbt_plan(std::string const path);
    
    /**
     * Function computing for each node the associated length sequence.
     */
    void compute_length_sequences();

    /**
     * Function computing the execution time for each execution node.
     */
    void compute_ex_times();

    control_flow_node* root_;
    std::set<action> actions_;
    int max_length_sequence_;
};
    
}
