#include "Game.hpp"

void GameHistory::add_action(std::string action) {
    history.push_back(action);
    ++historySz;
}

void GameHistory::save_file() {		// Saving to the .save file
    // implement in python
}

std::string GameHistory::get_path_name() {return saveName;}

std::string GameLoad::get_scenario_json() {return scenarioJson;}
void GameLoad::set_scenario_json(std::string scenarioIn) {
    scenarioJson = scenarioIn;
}

Scene GameLoad::get_scene() {return currentScene;}
void GameLoad::set_scene(Scene sceneIn) {
    currentScene = sceneIn;
}

Character* GameLoad::get_player() {return &player;}
void GameLoad::set_player(Character newPlayer) {
    player = newPlayer;
}

std::vector<std::string> input_reader(std::string textIn) {
    /*
     *
     * Takes the text input and return a vector with each 
     * word separated by spaces
     *
     */
    std::vector<std::string> textOut;

    // Adapted from the A Tour of C++ - Bjarne Stroustrup
    std::regex pat {R"(([\w+\d]+))"};
    for (std::sregex_iterator p(textIn.begin(), textIn.end(),pat); p!=std::sregex_iterator{}; ++p) {
        textOut.push_back( static_cast<std::string>( (*p)[1] ) );
    }

    return textOut;
}

std::string input_handler(std::string userIn, GameLoad& currentLoad) {
    printw("%s\n\n", userIn.c_str());	// First we print the user input
    refresh();

    std::vector<std::string> parsedIn;
    parsedIn = input_reader(userIn);

    // Make necessaries changes
    std::string screenOut;              // This will be taken from action_events
    screenOut = action_events(parsedIn, currentLoad);

    return screenOut;
}

int main_loop(std::string pathAdventures, std::string currentAdventure, GameLoad& currentLoad) {
    std::string userIn;
    std::string userOut;

    save_scene_game(pathAdventures, currentAdventure, currentLoad);
    // Get user input
    userIn = read_user_input();
    
    // Interpret input
    userOut = input_handler(userIn, currentLoad);

    // Give output
    printw("%s\n\n", userOut.c_str());	// First we print the user input
    
    if (userOut == "exit")
	return 0;

    return 1;
}

int save_scene_game(std::string pathAdventures, std::string currentAdventure, GameLoad &currentLoad) {
    save_scene(pathAdventures, currentAdventure, currentLoad);
    save_character(pathAdventures, currentAdventure, *currentLoad.get_player());

    return 1;
}
