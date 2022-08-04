#pragma once

#include <vector>
#include <string>
#include <cursesw.h>

#include "../AdvPython/AdvPython.hpp"

#include "../main_classes.hpp"

std::string action_events(std::vector<std::string> userIn, GameLoad& currentLoad);
void action_go(GameLoad& currentLoad, Directions newDirection);
std::string load_json_save(std::string pathAdventures, std::string currentAdventure);
