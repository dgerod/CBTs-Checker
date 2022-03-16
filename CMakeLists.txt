cmake_minimum_required (VERSION 3.9)
project (cbt_checker)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

include_directories(cbtc/include)

add_executable(cbt_checker
	cbtc/src/simple_logger.cpp 
	cbtc/src/action.cpp 
	cbtc/src/conditioned_behavior_tree.cpp 
	cbtc/src/control_flow_node.cpp 
	cbtc/src/execution_node.cpp 
	cbtc/src/task.cpp
	cbtc/src/main.cpp)