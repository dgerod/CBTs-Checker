//
//  execution_node.cpp
//  CBT_Requirements_Calculator
//
//  Created by E.Giunchiglia on 30/05/18.
//  Copyright © 2018 Eleonora Giunchiglia. All rights reserved.
//

#include "execution_node.hpp"

#include <iostream>
#include "simple_logger.hpp"


using namespace cbt;
using cbt::utils::simple_logger;


execution_node::execution_node(std::string label)
{
    action_label_ = label;
    sequence_length_ = 1;
    type_ = execution;
}

std::string execution_node::get_action_label()
{
    return this->action_label_;
}

int execution_node::get_identifier()
{
    simple_logger(simple_logger::level::DEBUG) << "execution_node::get_identifier" << std::endl;
    return this->identifier_;
}

int execution_node::get_ex_time()
{
    return this->ex_time_;
}

std::tuple<int, int> execution_node::compute_node_params(int id)
{
    this->identifier_ = id; 

    simple_logger(simple_logger::level::DEBUG) << "execution_node::compute_node_params" << std::endl;
    
    simple_logger(simple_logger::level::DEBUG) << "node identifier: " << this->identifier_ << std::endl;
    simple_logger(simple_logger::level::DEBUG) << "node type: " << this->type_ << std::endl;
    simple_logger(simple_logger::level::DEBUG) << "sequence length: " << this->sequence_length_ << std::endl;

    return  std::make_tuple(this->sequence_length_, this->identifier_);
}

int execution_node::set_ex_time(int current_time, task* parent)
{
    this->ex_time_ = current_time;
    return current_time+1;
}

int execution_node::get_plan(int current_time, task* parent, std::ofstream &file, std::set<action> * const actions)
{
    simple_logger(simple_logger::level::DEBUG) << "execution_node::get_plan" << std::endl;
    
    simple_logger(simple_logger::level::DEBUG) << "node identifier: " << this->identifier_ << std::endl;
    simple_logger(simple_logger::level::DEBUG) << "node type: " << this->type_ << std::endl;
    simple_logger(simple_logger::level::DEBUG) << "action label: " << this->action_label_ << std::endl;

    file << " & (eta_succ_" << this->get_identifier() << " -> " << "eta_try_" << this->get_identifier() << ")";
    file << " & (eta_succ_"<< this->get_identifier() << " <-> " << this->get_action_label() << "_" << this->get_ex_time() << ")";

    if (parent->get_type() != parallel)
    {
        file << " & (";
        unsigned int j = 0;
        for(auto& a : *actions)
        {
            if(a.get_label()!= this->get_action_label())
            {
                if (j < actions->size()-1)
                    file << "!" << a.get_label() << "_" << this->get_ex_time() << " & ";
                else
                    file << "!" << a.get_label() << "_" << this->get_ex_time();
            }
            j++;
        }
        
        file << ")";
    }  
    
    return current_time+1;
}