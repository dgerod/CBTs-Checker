#pragma once


#include <string>
#include <boost/tuple/tuple.hpp>
#include "simple_logger.hpp"

namespace cbtc { namespace utils {

typedef boost::tuple<std::string, cbtc::utils::simple_logger::level> configuration_params;
const configuration_params read_configuration(const std::string file_path);

}};
