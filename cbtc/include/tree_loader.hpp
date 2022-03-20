#pragma once


#include <string>
#include "conditioned_behavior_tree.hpp"


namespace cbtc { namespace tree_loader {

void bt_from_yarp_xml(cbtc::conditioned_behavior_tree& cbt, const std::string path);
void bt_from_sbt_file(cbtc::conditioned_behavior_tree& cbt, const std::string path);

}}
