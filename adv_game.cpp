#include "adv_game.hpp"

int load_save(std::string pathAdventures, std::string currentAdventure, GameLoad &currentLoad) {
    // Load save file
    load_save_file(pathAdventures, currentAdventure, currentLoad);

    // Load json
    load_json_save(pathAdventures, currentAdventure);

    return 1;
}

/*
int save_scene_game(std::string pathAdventures, std::string currentAdventure, GameLoad &currentLoad) {
    save_scene(AdventuresPath, advName, currentLoad);
    save_character(pathAdventures, currentAdventure, *currentLoad.get_player());

    return 1;
}
*/

int main(int argc, char *argv[]) {
    GameLoad currentLoad;
    std::string advName;

    if (argc < 2) {
	std::cout << "Especify the adventure Name\n";
	exit(1);
    } else {
        advName = argv[1];
    }

    // Call for initilization
    load_save(AdventuresPath, advName, currentLoad);
    initialize_window();

    int rows, columns;
    get_terminal_size(columns, rows);
    move(rows-1, 0);
    
    //std::string tempName(AdventuresPath);
    //tempName += advName+"/save/"+advName+".save";
    //std::ifstream f(AdventuresPath+advName+"/save/"+advName+".save");
    if ( check_character(AdventuresPath, advName) == 0 ) {
        Character newCharacter;
        newCharacter = create_character();
	currentLoad.set_player(newCharacter);
    }

    currentLoad.get_scene().show_scene();
    
    // Call for main loop function
    while (main_loop(AdventuresPath, advName, currentLoad)) {
        //save_scene_game(AdventuresPath, advName, currentLoad);
    }
        
    // Call for game closing
    save_scene_game(AdventuresPath, advName, currentLoad);
    close_window();

    return 0;
}
