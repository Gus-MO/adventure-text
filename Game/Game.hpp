#pragma once

#include <vector>
#include <string>
#include <cursesw.h>
#include <regex>

#include "../Actions/Actions.hpp"
#include "../Screen/Screen.hpp"

#include "../main_classes.hpp"
#include "../main_enums.hpp"

std::vector<std::string> input_reader(std::string textIn);
std::string input_handler(std::string userIn, GameLoad& currentLoad);
int main_loop(std::string pathAdventures, std::string currentAdventure, GameLoad& currentLoad);
int save_scene_game(std::string pathAdventures, std::string currentAdventure, GameLoad &currentLoad);
void initialize_window();
void close_window();
