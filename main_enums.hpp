#pragma once

#include <vector>
#include <string>

enum class Actions {GO, ATTACK, TAKE, LOOK, EXIT, SAY, LAST};
extern std::vector<std::string> actionsText;

enum class CharacterType {Player, Npc, Mob, LAST};
extern std::vector<std::string> characterTypeText;

enum class Directions{NORTE, NORDESTE, LESTE, SUDESTE, SUL, SUDOESTE, OESTE, NOROESTE, LAST};
extern std::vector<std::string> directionsText;

enum class ItemType{WEAPON, ARMOR, CLOTHING, ACESSORY, LAST};
extern std::vector<std::string> itemTypeText;
