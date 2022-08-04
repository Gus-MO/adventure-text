#pragma once

#include <cursesw.h>
#include <cstring>
#include <string>

#define STR_LIMIT 200
#define PROMPT "> "

void get_terminal_size(int& width, int& height);
void initialize_window();
void close_window();
std::string read_user_input();
