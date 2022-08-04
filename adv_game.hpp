#pragma once

#include "./Game/Game.hpp"
#include "./Characters/Characters.hpp"
#include <iostream>
#include <fstream>

std::string load_json_save(std::string pathAdventures);
int load_save(std::string pathAdventures, std::string currentAdventure, GameLoad &currentLoad);
//int save_scene_game(std::string pathAdventures, std::string currentAdventure, GameLoad &currentLoad);
