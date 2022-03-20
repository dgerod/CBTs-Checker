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

class conditioned_behavior_tree
{
public:
    conditioned_behavior_tree();
    ~conditioned_behavior_tree();
    
    control_flow_node& get_root_node();
    std::set<action> get_actions();

    void insert_action(action const* const new_action);

    /**
     * Fuction returning the sequence length of the CBT.
     */
    int get_max_length_sequence();
    
    /**
     * Function computing for each node the associated length sequence.
     */
    void compute_length_sequences();

    /**
     * Function computing the execution time for each execution node.
     */
    void compute_ex_times();

    /**
     * Function handling the pipeline of function calls to generate the requirements.
     * \param initial_requirements_path string containing the path to the input .txt file with the initial requirements
     * \param bt_plans_path string containing the path to the bt plans file path
     */
    void generate_initial_requirements(std::string const initial_requirements_path, std::string const bt_plans_path);

    /**
     * Function to write the state graph to the output file.
     * \param path string containing the path to the output folder
     */
    void create_state_graph(std::string const bt_plans_file, std::string const requirements_file);
    
    /**
     * Function to write the plans of the CBT to the output file.
     * \param path string containing the path to the output folder
     */
    void create_cbt_plan(std::string const bt_plans_file);

protected:    
    control_flow_node* root_;
    std::set<action> actions_;
    int max_length_sequence_;
};
    
}
