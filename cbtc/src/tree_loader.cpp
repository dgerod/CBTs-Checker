#include "tree_loader.hpp"

#include <stdio.h>
#include <fstream>
#include "simple_logger.hpp"


using namespace cbtc;
using namespace cbtc::utils;



namespace {

// Function that ignores empty lines and whitespaces at the beginning of each
// line. Takes as input the ifstream and returns the next full line.
std::string get_next_line(std::ifstream* const file)
{
    std::string line = "";
    bool end_file = false;

    while(line.length() == 0 and !end_file)
    {
        if(!file->eof()) 
        {
            std::getline(*file >> std::ws,line);
        }
        else
        {
            end_file = true;
        }
    }
    return line;
}

// Function that, given a line, returns the cleaned action label.
std::string read_action_label(std::string const line)
{
    unsigned long first_quotation_marks = line.find("\"");
    unsigned long second_quotation_marks = line.find("\"", first_quotation_marks+1);
    std::string label = line.substr(first_quotation_marks+1, second_quotation_marks-first_quotation_marks-1);
    
    if (label.length()==0 || second_quotation_marks == std::string::npos) 
    {
        throw std::runtime_error("Input XML file bad format: YARPAction must have identifier surrounded by quotation marks");
    }

    std::transform(label.begin(), label.end(), label.begin(), ::tolower);
    if(label.find(" ") != std::string::npos)
    {
        throw std::runtime_error("Input XML file bad format: YARPAction cannot contain whitespaces");
    }
    
    return label;
}

// Function that, given a line, returns the cleaned condition label.
std::string read_condition_label(std::string const line)
{
    unsigned long first_quotation_marks = line.find("\"");
    unsigned long second_quotation_marks = line.find("\"", first_quotation_marks+1);
    std::string label = line.substr(first_quotation_marks+1, second_quotation_marks-first_quotation_marks-1);
    
    if (label.length()==0 || second_quotation_marks == std::string::npos)
    {
        throw std::runtime_error("Input XML file bad format: Pre and Post conditions must have identifier surrounded by quotation marks");
    }

    std::transform(label.begin(), label.end(), label.begin(), ::tolower);
    if(label.substr(0,3).find("!") != std::string::npos or 
       label.substr(0,3).find("not") != std::string::npos or
       label.substr(0,3).find("NOT") != std::string::npos)
    {
        if(label.substr(4).find(" ") != std::string::npos)
        {
            throw std::runtime_error("Input XML file bad format: after \"not \" Pre and Post conditions cannot contain whitespaces");
        }
        label = "!" + label.substr(4);
    } 
    else
    {
        if(label.find(" ") != std::string::npos) 
        {
            throw std::runtime_error("Input XML file bad format: positive Pre and Post conditions cannot contain whitespaces");
        }
    }
    return label;
}

// Function processing and storing a single action
void read_single_action(cbtc::conditioned_behavior_tree& cbt, std::ifstream* const file)
{
    action* new_action = new action();
    
    // Get the label of the action and check the input format
    std::string line;
    line = get_next_line(file);
    if (line.substr(0,11).find("YARPAction") == std::string::npos)
    {
        throw std::runtime_error("Input XML file bad format: object ActionTemplate must contain object YARPAction");
    }

    std::string action_label = read_action_label(line);
    new_action->set_label(action_label);
    
    // Get the Pre-conditions of the action and check the input format
    std::string pre_label;
    line = get_next_line(file);
    while(line.substr(0,13).find("Precondition") != std::string::npos)
    {
        pre_label = read_condition_label(line);

        if(pre_label[0] == '!' && std::find(new_action->get_pre().begin(), new_action->get_pre().end(), pre_label.substr(1)) != new_action->get_pre().end())
        {
            throw std::runtime_error("Input XML file bad format: action cannot have 'c' and 'not c' as pre-conditions");
        }
        
        else if(pre_label[0] != '!' && (std::find(new_action->get_pre().cbegin(), new_action->get_pre().cend(), "!" + pre_label) != new_action->get_pre().cend())) 
        {
            throw std::runtime_error("Input XML file bad format: action cannot have 'c' and 'not c' as pre-conditions");
        }
        new_action->insert_pre(pre_label);
        
        line = get_next_line(file);
    }
        
    // Get the Post-conditions of the action and check the input format
    std::string post_label;
    while(line.substr(0,14).find("Postcondition") != std::string::npos)
    {
        post_label = read_condition_label(line);
        if(post_label[0] == '!' && std::find(new_action->get_post().begin(), new_action->get_post().end(), post_label.substr(1)) != new_action->get_post().end())
        {
            throw std::runtime_error("Input XML file bad format: action cannot have 'c' and 'not c' as post-conditions");
        }
        else if(post_label[0] != '!' && std::find(new_action->get_post().begin(), new_action->get_post().end(), ("!" + post_label)) != new_action->get_post().end()) 
        {
            throw std::runtime_error("Input XML file bad format: action cannot have 'c' and 'not c' as post-conditions");
        }
        new_action->insert_post(post_label);
        line = get_next_line(file);
    }
    
    // Check end of the function
    if (line.compare("</ActionTemplate>") != 0)
    {
        throw std::runtime_error("Input XML file bad format: object ActionTemplate must end with </ActionTemplate>");
    }
    
    // Insert the new action in the list of actions
    cbt.insert_action(new_action);
}

void read_execution_node(cbtc::conditioned_behavior_tree& cbt, std::string line, control_flow_node* const parent)
{
    unsigned long first_quotation_marks = line.find("\"");
    unsigned long second_quotation_marks = line.find("\"", first_quotation_marks+1);
    std::string label = line.substr(first_quotation_marks+1, second_quotation_marks-first_quotation_marks-1);
    std::transform(label.begin(), label.end(), label.begin(), ::tolower);
    action* dummy_action = new action();
    dummy_action->set_label(label);
    
    if(line.find("YARPAction") != std::string::npos) 
    {
        std::set<action> actions = cbt.get_actions();
        if(actions.find(*dummy_action) == actions.end())
        {
            throw std::runtime_error("Action not defined in the vocabulary");
        }
    }
    if(line.find("YARPCondition") != std::string::npos) 
    {
        cbt.insert_action(dummy_action);
    }
    execution_node* node = new execution_node(label);
    parent->add(node);
}

std::string read_next_node(cbtc::conditioned_behavior_tree& cbt, std::ifstream* const file, control_flow_node* const parent)
{
    std::string line = get_next_line(file);
    if(line.find("YARP") != std::string::npos)
    {
        read_execution_node(cbt, line, parent);
        if (parent->get_type() == ROOT)
            line = get_next_line(file);
        return line;
    }
    else if(line.find("</") != std::string::npos)
    {
        return line;
    }
    else 
    {
        control_flow_node* node = new control_flow_node();
        if(line.find("<Sequence>")!= std::string::npos)
        {
            node->set_type(SEQUENCE);
        }
        else if(line.find("<Fallback>")!= std::string::npos)
        {
            node->set_type(FALLBACK);
        }
        else if(line.find("<Parallel>")!= std::string::npos)
        {
            node->set_type(PARALLEL);
        }
        else
        {
            throw std::runtime_error("Input XML file bad format: Behavior Tree bad format");
        }

        parent->add(node);
        
        do 
        {
            line = read_next_node(cbt, file, node);
        } while(line.find("YARP") != std::string::npos);
        
        // Check that the node is closed
        if (node->get_type() == SEQUENCE && line.find("</Sequence>")== std::string::npos)
                throw std::runtime_error("Input XML file bad format: Behavior Tree bad format");
        else if (node->get_type() == FALLBACK && line.find("</Fallback>") == std::string::npos)
                throw std::runtime_error("Input XML file bad format: Behavior Tree bad format");
        else if (node->get_type() == PARALLEL && line.find("</Parallel>") == std::string::npos)
                throw std::runtime_error("Input XML file bad format: Behavior Tree bad format");
        
        do 
        {
            line = read_next_node(cbt, file, parent);
        } while(line.find("YARP") != std::string::npos);
        
        return line;
    }
}

std::string read_actions(cbtc::conditioned_behavior_tree& cbt, std::ifstream* const file)
{
    simple_logger(simple_logger::level::DEBUG) << "read_actions" << std::endl;

    std::string line = get_next_line(file);
    while(line == "<ActionTemplate>")
    {
        read_single_action(cbt, file);
        line = get_next_line(file);
    }    

    return line;
}

void read_bt(cbtc::conditioned_behavior_tree& cbt, std::ifstream* const file, std::string line)
{
    simple_logger(simple_logger::level::DEBUG) << "read_bt" << std::endl;

    if (line.substr(0, 6).compare("<root>") != 0)
    {
        throw std::runtime_error("Input XML file bad format: Behavior Tree must have a root");
    }    
    std::string bt_line = get_next_line(file);
    if (bt_line.substr(0, 14).compare("<BehaviorTree>") != 0)
    {
        throw std::runtime_error("Input XML file bad format: root must be followed by <BehaviorTree>");
    }
    line = read_next_node(cbt, file, cbt.get_root_node());
    if (line.substr(0, 15).compare("</BehaviorTree>") != 0)
    {            
        throw std::runtime_error("Input XML file bad format: object <Behavior Tree> must be closed");
    }
    line = get_next_line(file);
    if (line.substr(0, 7).compare("</root>") != 0)
    {
        throw std::runtime_error("Input XML file bad format: object <root> must be closed");
    }
}

bool validate_parallel_with_execute_nodes(cbtc::task& node)
{
    bool valid = true;

    if(node.get_type() == PARALLEL)
    {
        for(auto& c : node.get_children())
        {
            valid = valid and c->get_type() == EXECUTION;
        }
    }

    return valid;
}

bool validate_node_rules(cbtc::task& node, int id)
{
    bool valid = false;
    
    simple_logger(simple_logger::level::DEBUG) << "node"  << std::endl;
    simple_logger(simple_logger::level::DEBUG) << "  - node id: " << id << std::endl;
    simple_logger(simple_logger::level::DEBUG) << "  - node type: " << node_type_to_string(node.get_type()) << std::endl;
    
    if(node.get_type() == ROOT)
    {
        valid = node.get_children().size() == 1;
        
        simple_logger(simple_logger::level::DEBUG) << "  - num children: " << node.get_children().size() << std::endl;
        simple_logger(simple_logger::level::DEBUG) << "  - valid: " << valid << std::endl;
    }
    
    if(node.get_type() == FALLBACK || node.get_type() == SEQUENCE)
    {
        valid = node.get_children().size() > 1;

        simple_logger(simple_logger::level::DEBUG) << "  - num children: " << node.get_children().size() << std::endl;
        simple_logger(simple_logger::level::DEBUG) << "  - valid: " << valid << std::endl;
    }
    
    if(node.get_type() == PARALLEL)
    {
        bool are_execution_nodes = validate_parallel_with_execute_nodes(node);
        valid = node.get_children().size() > 1 and are_execution_nodes;

        simple_logger(simple_logger::level::DEBUG) << "  - num children: " << node.get_children().size() << std::endl;
        simple_logger(simple_logger::level::DEBUG) << "  - execution nodes: " << are_execution_nodes << std::endl;
        simple_logger(simple_logger::level::DEBUG) << "  - valid: " << valid << std::endl;
    }
    
    if(node.get_type() == EXECUTION)
    {
        valid = node.has_children() == false;
        
        simple_logger(simple_logger::level::DEBUG) << "  - action label: " << static_cast<execution_node&>(node).get_action_label() << std::endl;
        simple_logger(simple_logger::level::DEBUG) << "  - valid: " << valid << std::endl;
    }

    return valid;
}

bool validate_node(cbtc::task& node, int& id)
{
    if (validate_node_rules(node, id))
    {
        for(auto& c : node.get_children())
        {
            id++;
            if (!validate_node(*c, id))
            {
                return false;            
            }
        }
        
        return true;
    }

    return false;
}

bool validate_bt(cbtc::conditioned_behavior_tree& cbt)
{
    // Rules:
    //  - Fallback, sequence and parallel must have more two children at least.
    //  - Children of parallel node must be execution nodes.
    cbtc::task* node = cbt.get_root_node();
    int id = 0;
    return validate_node(*node, id);
}

}

namespace cbtc { namespace tree_loader {

void bt_from_yarp_xml(cbtc::conditioned_behavior_tree& cbt, const std::string path)
{
    simple_logger(simple_logger::level::DEBUG) << "bt_from_yarp_xml" << std::endl;

    simple_logger(simple_logger::level::DEBUG) << "read input file" << std::endl;

    std::ifstream file;
    file.open(path);
    if (!file.good())
    {
        throw std::runtime_error("Exception occurred while opening the file: input xml file not found.");
    }

    std::string line = read_actions(cbt, &file); 
    read_bt(cbt, &file, line);     
    
    simple_logger(simple_logger::level::DEBUG) << "validate cbt" << std::endl;

    bool format_valid = validate_bt(cbt);
    simple_logger(simple_logger::level::DEBUG) << "cbt well formated? " << format_valid << std::endl;

    if (!format_valid)
    {       
        throw std::runtime_error("Tree in input xml file is not well formated."); 
    }
}

void bt_from_sbt_file(cbtc::conditioned_behavior_tree& cbt, const std::string path)
{
    throw std::runtime_error("Not implemented.");
}

}}
