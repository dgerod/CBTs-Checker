#include "cbt_validator.hpp"

#include <iostream>
#include "simple_logger.hpp"


using namespace cbtc;
using cbtc::utils::simple_logger;

namespace {

const std::string bt_plans_file_name = "cbt_plans.txt";
const std::string general_requirements_file_name = "solver_result.txt";

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

bool find_text_in_file(const std::string file_path, const std::string text)
{
    bool found = false;

    std::ifstream file;     
    file.open(file_path);       
   
    std::string line;
    line = get_next_line(&file);
    simple_logger(simple_logger::level::DEBUG) << "Validation text: " << line << std::endl;
    
    if (line.find(text) != std::string::npos)
    {
        found = true;
    }

    file.close();
    return found;
}

bool execute_limboole(const std::string limboole_path, const std::string bt_plans_file, const std::string general_requirmements_file)
{
    std::string command = limboole_path + " -s " + bt_plans_file + " >> " + general_requirmements_file;
    simple_logger(simple_logger::level::DEBUG) << "Command: " << command << std::endl;

    std::array<char, 128> buffer;
    std::string result;    
    FILE* pipe = popen(command.c_str(), "r");
    
    while (fgets(buffer.data(), 128, pipe) != NULL) 
    {
        result += buffer.data();
    }
    pclose(pipe);    

    // The CBT is NOT valid if the problem is satifiable, SAT verify if exists one 
    //  possible execution path of the CBT that is not respecting the constraints. So, the CBT is not valid.
    bool valid = false;

    if (find_text_in_file(general_requirmements_file, "UNSATISFIABLE"))
    {
        valid = true;
    }
    else
    {
        if (find_text_in_file(general_requirmements_file, "SATISFIABLE"))
        {
            valid = false;
        }
        else
        {
            simple_logger(simple_logger::level::ERROR) << "ERROR: Wrong SAT result file" << std::endl;
            throw std::runtime_error("ERROR: Wrong SAT result file");	
        }
    }
    
    simple_logger(simple_logger::level::DEBUG) << "Is valid: " << valid << std::endl;
    return valid;
}

bool validate_cbt_plan(const std::string limboole_path, std::string const output_folder) 
{
    simple_logger(simple_logger::level::DEBUG) << "Validate CBT plan" << std::endl;
    std::string bt_plans_file_path = output_folder + "/" + bt_plans_file_name;
    std::string general_requirements_file_path = output_folder + "/" + general_requirements_file_name;
        
    remove(general_requirements_file_path.c_str());
    bool valid = execute_limboole(limboole_path, bt_plans_file_path, general_requirements_file_path);  

    return valid;
}

}

cbt_validator::cbt_validator(const std::string limbool_app_path, const std::string output_folder)
{
    this->limboole_app_path_ = limbool_app_path;
    this->output_folder_ = output_folder;
    this->bt_plans_file_ = output_folder + "/" + bt_plans_file_name;
    this->generated_requirements_file_ = output_folder + "/" + general_requirements_file_name;
}

cbt_validator::~cbt_validator()
{
}

bool cbt_validator::validate(cbtc::conditioned_behavior_tree& cbt, const std::string initial_requirements_path) 
{   
    simple_logger(simple_logger::level::DEBUG) << "cbt_validator::validate" << std::endl;
    simple_logger(simple_logger::level::DEBUG) << "limboole app path: " <<  this->limboole_app_path_ << std::endl;    
    simple_logger(simple_logger::level::DEBUG) << "initial state:  " <<  initial_requirements_path << std::endl;
    simple_logger(simple_logger::level::DEBUG) << "output directory: " <<  this->output_folder_ << std::endl;

    cbt.compute_length_sequences();    
    cbt.compute_ex_times();

    simple_logger(simple_logger::level::INFO) << "Max sequence lenght: " << cbt.get_max_length_sequence() << std::endl;

    this->create_state_graph(cbt, initial_requirements_path, this->bt_plans_file_);
    this->create_cbt_plan(cbt, this->bt_plans_file_);

    return validate_cbt_plan(this->limboole_app_path_, this->output_folder_);
}

void cbt_validator::create_state_graph(cbtc::conditioned_behavior_tree& cbt, 
    const std::string requirements_file, const std::string bt_plans_file)
{
    simple_logger(simple_logger::level::DEBUG) << "[cbt_validator::create_state_graph] BEGIN" << std::endl;
    
    std::ofstream file;
    file.exceptions (std::ofstream::failbit | std::ofstream::badbit );

    file.open(bt_plans_file, std::ios::out);
    if (!file.good())
    {
        throw std::runtime_error("ERROR: Exception occurred while creating output file for BT plans.");	
    }

    // Define true and false symbols
    file << "true & !false &\n";

    // Open the input file with the requirements
    simple_logger(simple_logger::level::DEBUG) << "Initial requirements: " << requirements_file << std::endl;

    if (!requirements_file.empty())
    {
        std::ifstream req_file;
        req_file.open(requirements_file);
        if (!req_file.good())
        {
            throw std::runtime_error("ERROR: Exception occurred while opening the file: initial requirements file not found.");
        }

        std::string line = "";
        bool end_file = false;
        
        while (line.length() == 0 and !end_file)
        {
            if (!req_file.eof()) 
            {
                std::getline(req_file >> std::ws, line);
                file << line;
            }
            else
            {
                end_file = true;
            }
        }

        if (line.length() != 0)
        {
            file << " &\n";
        }
    }
    else
    {
        throw std::runtime_error("ERROR: An initial requirements is mandatory.");
    }

    // Write all the formulas of the state graph of the type:
    //  a_i & \big_wedge {\neg c_i | c \in Pre}
    file << "(";
    for(auto& a: cbt.get_actions())
    {
        for(int i=0; i < cbt.get_max_length_sequence(); i++)
        {
            
            if(a.get_pre().size() > 0)
            {
                unsigned int k = 0;
                file << "(" << a.get_label() << "_" << i << " & (";
                for(auto& pre: a.get_pre())
                {
                    if(k < a.get_pre().size()-1)
                    {
                         file << "!" <<  pre << "_" << i << " | ";
                    }
                    else
                    {
                        file << "!" <<  pre << "_" << i;
                    }
                    k++;
                }
                file << ")) | \n";
            }
        }
    }
    file << "false) & \n";

    // Write all the formulas of the state graph of the type:
    //  a_i --> \bigwedge {c_{i+1} | c \in Post}
    for(auto& a: cbt.get_actions())
    {
        for(int i=0; i < cbt.get_max_length_sequence(); i++)
        {                   
            if(a.get_post().size() > 0)
            {
                unsigned int k=0;
                file  << "(" << a.get_label() << "_" << i << " -> (";
                for(auto& post: a.get_post())
                {
                    if(k < a.get_post().size()-1)
                    {
                        file <<  post << "_" << (i+1) << " & ";
                    }
                    else
                    {
                        file <<  post << "_" << (i+1);
                    }
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
    for(auto& a: cbt.get_actions())
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
        for (int i=0; i < cbt.get_max_length_sequence(); i++)
        {
            file << "(";
            if (pair.first.substr(0,1).compare("!") == 0)
            {
                file << pair.first.substr(1) << "_" << i << " & " << pair.first << "_" << i+1 << " -> (";
            }
            else
            {
                file << "!" << pair.first << "_" << i << " & " << pair.first << "_" << i+1 << " -> (";
            }

            unsigned int j=0;
            for (auto& a : pair.second)
            {
                if(j < pair.second.size()-1)
                {
                    file << a << "_" << i << " | ";
                }
                else
                {
                    file << a << "_" << i;
                }
                j++;
            }
    
            if(pair.second.size() == 0)
            {
                file << "false";            
            }

            file << ")) &\n";
        }
    }
    
    file.flush();
    file.close();
    simple_logger(simple_logger::level::DEBUG) << "[cbt_validator::create_state_graph] END" << std::endl;
}

void cbt_validator::create_cbt_plan(cbtc::conditioned_behavior_tree& cbt, const std::string bt_plans_file)
{
    simple_logger(simple_logger::level::DEBUG) << "cbt_validator::create_cbt_plan" << std::endl;

    std::ofstream file;
    file.exceptions (std::ofstream::failbit | std::ofstream::badbit );
    file.open(bt_plans_file, std::ios::app);

    cbt.get_plan(file);
    file.close();    
}
