cmake_minimum_required (VERSION 3.9)
project (cbt_checker)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

find_package(Boost REQUIRED COMPONENTS filesystem)
include_directories({Boost_INCLUDE_DIRS})

include_directories(cbtc/include)

add_executable(cbt_checker 
	cbtc/src/main.cpp
	cbtc/src/simple_logger.cpp 
	cbtc/src/read_configuration.cpp 
	cbtc/src/task.cpp
	cbtc/src/action.cpp 	
	cbtc/src/control_flow_node.cpp 
	cbtc/src/execution_node.cpp 	
	cbtc/src/conditioned_behavior_tree.cpp 
	cbtc/src/cbt_validator.cpp
	cbtc/src/tree_loader.cpp)

add_executable(tests
	test/test.cpp
	test/load_bt_from_xml.cpp
	test/check_bt_valid.cpp
	#test/test_strutturali/compute_sequence_length.cpp
	#test/test_strutturali/stage_3.cpp
	#test/test_strutturali/stage_4.cpp
	#test/test_strutturali/stage_5.cpp
	#test/test_funzionali/test_funzionali.cpp
	cbtc/src/simple_logger.cpp 
	cbtc/src/read_configuration.cpp 
	cbtc/src/task.cpp
	cbtc/src/action.cpp 	
	cbtc/src/control_flow_node.cpp 
	cbtc/src/execution_node.cpp 	
	cbtc/src/conditioned_behavior_tree.cpp 
	cbtc/src/cbt_validator.cpp
	cbtc/src/tree_loader.cpp)

target_link_libraries(tests PUBLIC Boost::filesystem)
