#include "simple_logger.hpp"


using namespace cbtc::utils;


simple_logger::level simple_logger::enabled_level_ = simple_logger::level::NONE;

simple_logger::simple_logger(simple_logger::level current_level) 
    : output_(current_level <= enabled_level_) 
{}
