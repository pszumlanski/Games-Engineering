cmake_minimum_required(VERSION 3.9)
# Require modern C++
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Games_Engineering)

#### Setup Directories ####
#Main output directory
SET(OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
# Output all DLLs from all libs into main build folder
SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})



#### Add External Dependencies ####
add_subdirectory("lib/sfml")
set(SFML_INCS "lib/sfml/include")
link_directories("${CMAKE_BINARY_DIR}/lib/sfml/lib")

#### Pong ####
file(GLOB_RECURSE SOURCES pong/*.cpp pong/*.h)
add_executable(PONG ${SOURCES})
target_include_directories(PONG PRIVATE ${SFML_INCS})
target_link_libraries(PONG sfml-graphics)

#### Space Invaders ####
file(GLOB_RECURSE SOURCES spaceinvaders/*.cpp spaceinvaders/*.h)
add_executable(SPACE_INVADERS ${SOURCES})
target_include_directories(SPACE_INVADERS SYSTEM PRIVATE ${SFML_INCS})
target_link_libraries(SPACE_INVADERS sfml-graphics)

#### Program source ####
set_target_properties(SPACE_INVADERS
	PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY
	${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration)
)

#### Post Build ####
add_custom_command(TARGET YOUR_EXECUTABLE POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different "resource_dir"
		$<TARGET_FILE_DIR:${YOUR_EXECUTABLE}>/res
)

add_custom_target(copy_resources ALL COMMAND ${CMAKE_COMMAND}
	-E copy_directory
		"${PROJECT_SOURCE_DIR}/res"
		${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIGURATION>/res
)

add_dependencies(SPACE_INVADERS copy_resources)