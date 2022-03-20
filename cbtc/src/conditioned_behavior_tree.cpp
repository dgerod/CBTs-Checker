//
//  cbt.cpp
//  CBT_Requirements_Calculator
//
//  Created by E.Giunchiglia on 29/05/18.
//  Copyright © 2018 Eleonora Giunchiglia. All rights reserved.
//

#include "conditioned_behavior_tree.hpp"

#include <iostream>
#include "simple_logger.hpp"


using namespace cbtc;
using cbtc::utils::simple_logger;


conditioned_behavior_tree::conditioned_behavior_tree()
{
    this->root_ = new control_flow_node(ROOT);
    this->max_length_sequence_ = 0;
}

conditioned_behavior_tree::~conditioned_behavior_tree()
{
    delete root_;
}

control_flow_node* conditioned_behavior_tree::get_root_node()
{
    return this->root_;
}

std::set<action> conditioned_behavior_tree::get_actions()
{
    return this->actions_;
}

void conditioned_behavior_tree::insert_action(action const* const new_action)
{
    
    if(!this->actions_.insert(*new_action).second){
        std::cerr << "Warning: action " << new_action->get_label() << " specified more than one time in the XML file." <<std::endl;
        std::cerr << "New pre and post conditions not memorized" << std::endl;
    }
}

int conditioned_behavior_tree::get_max_length_sequence()
{
    return this->max_length_sequence_;
}

void conditioned_behavior_tree::compute_length_sequences()
{
    simple_logger(simple_logger::level::DEBUG) << "conditioned_behavior_tree::compute_length_sequences" << std::endl;

    this->root_->compute_node_params(0);
    this->max_length_sequence_ = this->root_->get_sequence_length();
}

void conditioned_behavior_tree::compute_ex_times()
{
    simple_logger(simple_logger::level::DEBUG) << "conditioned_behavior_tree::compute_ex_times" << std::endl;

    this->root_->set_ex_time(0, this->root_);
}

int conditioned_behavior_tree::get_plan(std::ofstream& file)
{
    return this->root_->get_plan(0, this->root_, file, &this->actions_);    
}