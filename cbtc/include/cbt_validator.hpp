#pragma once
 
#include <string>
#include "conditioned_behavior_tree.hpp"


namespace cbtc {

class cbt_validator
{
public:
    cbt_validator(const std::string limbool_app_path, const std::string output_folder);
    ~cbt_validator();
  
    bool validate(cbtc::conditioned_behavior_tree& cbt, const std::string initial_requirements_path);

protected:
    void create_state_graph(cbtc::conditioned_behavior_tree& cbt, 
        std::string const requirements_file, std::string const bt_plans_file);
    void create_cbt_plan(cbtc::conditioned_behavior_tree& cbt, 
        std::string const bt_plans_file);   

    std::string limboole_app_path_;
    std::string output_folder_;
    std::string bt_plans_file_;
    std::string generated_requirements_file_;
};

}
