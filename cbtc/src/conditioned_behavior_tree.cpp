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

control_flow_node& conditioned_behavior_tree::get_root_node()
{
    return *this->root_;
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

void conditioned_behavior_tree::generate_initial_requirements(std::string const requirements_path, 
std::string const output_path_bt_plans) 
{
    simple_logger(simple_logger::level::DEBUG) << "conditioned_behavior_tree::compute_initial_requirements" << std::endl;

    this->compute_length_sequences();
    this->compute_ex_times();
    this->create_state_graph(output_path_bt_plans, requirements_path);
    this->create_cbt_plan(output_path_bt_plans);
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

void conditioned_behavior_tree::create_state_graph(std::string const output_path_bt_plans, std::string const req_path)
{
    simple_logger(simple_logger::level::DEBUG) << "conditioned_behavior_tree::create_state_graph" << std::endl;
    
    std::ofstream file;
    file.exceptions (std::ofstream::failbit | std::ofstream::badbit );

    file.open(output_path_bt_plans, std::ios::out);
    if (!file.good())
    {
        throw std::runtime_error("Exception occurred while creating output file for BT plans.");	
    }

    // Define true and false symbols
    file << "true & !false &\n";

    // Open the input file with the requirements
    std::ifstream req_file;
    req_file.open(req_path);
    if (!req_file.good())
    {
        throw std::runtime_error("Exception occurred while opening the file: input txt file with initial requirements not found.");
    }

    std::string line = "";
    bool end_file = false;
    while(line.length() == 0 and !end_file)
    {
        if(!req_file.eof()) 
        {
            std::getline(req_file >> std::ws,line);
        }
        else
        {
            end_file = true;
        }

        file << line;
    }

    file << " &\n";
                
    // Write all the formulas of the state graph of the type:
    //  a_i & \big_wedge {\neg c_i | c \in Pre}
    file << "(";
    for(auto& a: this->actions_)
    {
        for(int i=0; i < this->max_length_sequence_; i++)
        {
            
            if(a.get_pre().size()>0)
            {
                unsigned int k = 0;
                file << "(" << a.get_label() << "_" << i << " & (";
                for(auto& pre: a.get_pre())
                {
                    if(k < a.get_pre().size()-1)
                         file << "!" <<  pre << "_" << i << " | ";
                    else
                        file << "!" <<  pre << "_" << i;
                    k++;
                }
                file << ")) | \n";
            }
        }
    }
    file << "false) & \n";

    // Write all the formulas of the state graph of the type:
    //  a_i --> \bigwedge {c_{i+1} | c \in Post}
    for(auto& a: this->actions_)
    {
        for(int i=0; i < this->max_length_sequence_; i++)
        {                   
            if(a.get_post().size()>0)
            {
                unsigned int k=0;
                file  << "(" << a.get_label() << "_" << i << " -> (";
                for(auto& post: a.get_post())
                {
                    if(k < a.get_post().size()-1)
                        file <<  post << "_" << (i+1) << " & ";
                    else
                        file <<  post << "_" << (i+1);
                    k++;
                }
                file << ")) & \n";
            }
        }
    }
    // Write all formulas of the state graph of the type
    //  (c_i \wedge \neg c_{i+1}) --> \big_vee {a_i | \neg c \in Post}
    //  (\neg c_i \wedge c_{i+1}) --> \big_vee {a_i | c \in Post}
    
    // First we create a map from each condition to all the actions that generete that postcondition
    std::map<std::string, std::vector<std::string>> formulas;
    for(auto& a: this->actions_)
    {
        std::string action = a.get_label();
        for(auto& post : a.get_post())
        {
            std::vector<std::string> actions;
            actions.insert(actions.begin(), action);
            std::pair<std::map<std::string,std::vector<std::string>>::iterator,bool> ret;
            ret = formulas.insert(std::pair<std::string, std::vector<std::string>> (post, actions));
            if (!ret.second)
            { 
                // it means that the pair with that condition already existed in the map, in that case nothing is inserted
                ret.first->second.insert(ret.first->second.begin(), action);
            }
            if(post.substr(0,1).compare("!") == 0)
            {
                std::vector<std::string> actions;
                ret = formulas.insert(std::pair<std::string, std::vector<std::string>> (post.substr(1), actions));
            }
            else
            {
                std::vector<std::string> actions;
                ret = formulas.insert(std::pair<std::string, std::vector<std::string>> ("!" + post, actions));
            }
        }
    }
    
    // Given the map we can write all the formulas
    for (auto& pair: formulas)
    {
        for (int i=0; i < max_length_sequence_; i++)
        {
            file << "(";
            if (pair.first.substr(0,1).compare("!") == 0)
                file << pair.first.substr(1) << "_" << i << " & " << pair.first << "_" << i+1 << " -> (";
            else
                file << "!" << pair.first << "_" << i << " & " << pair.first << "_" << i+1 << " -> (";
        
            unsigned int j=0;
            for (auto& a : pair.second)
            {
                if(j < pair.second.size()-1)
                    file << a << "_" << i << " | ";
                else
                    file << a << "_" << i;
                j++;
            }
    
            if(pair.second.size() == 0)
                file << "false";            
        
            file << ")) &\n";
        }
    }
    
    file.flush();
    file.close();
}

void conditioned_behavior_tree::create_cbt_plan(std::string const output_path_bt_plans)
{
    simple_logger(simple_logger::level::DEBUG) << "conditioned_behavior_tree::create_CBT_plan" << std::endl;

    std::ofstream file;
    file.exceptions (std::ofstream::failbit | std::ofstream::badbit );
    file.open(output_path_bt_plans, std::ios::app);

    this->root_->get_plan(0, this->root_, file, &this->actions_);
    
    file.close();    
}
