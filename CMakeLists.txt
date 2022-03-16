cmake_minimum_required (VERSION 3.9)
project (cbt_checker)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

include_directories(include)

add_executable(cbt_checker
	src/simple_logger.cpp 
	src/action.cpp 
	src/conditioned_behavior_tree.cpp 
	src/control_flow_node.cpp 
	src/execution_node.cpp 
	src/task.cpp
	src/main.cpp)