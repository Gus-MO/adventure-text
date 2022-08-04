#pragma once

#include <vector>
#include <string>
#include <math.h>
#include <cursesw.h>
#include <cstring>

#include "../main_classes.hpp"
#include "../main_enums.hpp"
#include "../main_functions.hpp"

#define STR_LIMIT 200

constexpr int CLASS_LIMIT = 3;
constexpr int HANDS_LIMIT = 2;
constexpr int FINGERS_LIMIT = 10;
constexpr int HEAD_LIMIT = 1;
constexpr int CLOTHS_LIMIT = 3;
constexpr int BACKPACK_LIMIT = 6;
constexpr int BELT_LIMIT = 2;

int base_table(int x);
Character create_character();
void change_char_attribute(std::string attribute, std::string newValue);
