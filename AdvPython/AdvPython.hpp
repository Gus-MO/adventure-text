#pragma once

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <vector>
#include <string>
#include <type_traits>

//#include <iostream>

#include "../main_classes.hpp"
#include "../main_enums.hpp"

PyObject* getPyFunc(char *moduleName, char *funcName, std::vector<char*> funcArgs, PyObject* pValue);
PyObject* getPyFunc_fromDict(char *moduleName, char *funcName, std::vector<char*> funcArgs, PyObject* argDict, PyObject* pValue);
Scene json_to_scene(char *sceneName, char *fileName);
std::vector<Directions> string_to_directions(std::vector<std::string> vecIn);
std::vector<std::string> directions_to_string(std::vector<Directions> vecIn);
std::vector<Actions> string_to_actions(std::vector<std::string> vecIn);
std::vector<std::string> actions_to_string(std::vector<Actions> vecIn);
std::string load_json_save(std::string pathAdventures, std::string currentAdventure);
int load_save_file(std::string pathAdventures, std::string currentAdventure, GameLoad& currentLoad);
std::vector<std::string> get_json_att(char* fileName, char* attName, char* sceneName);
Character load_saved_character(std::string pathAdventures, std::string currentAdventure);
int check_character (std::string pathAdventures, std::string currentAdventure);
int save_scene(std::string pathAdventures, std::string currentAdventure, GameLoad&currentLoad);
int save_character(std::string pathAdventures, std::string currentAdventure, Character currentPlayer);
