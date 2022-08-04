#include "Actions.hpp"

std::string action_events(std::vector<std::string> userIn, GameLoad& currentLoad) {
    /*
     *
     * Executes the action for a given user input
     * returning the text output.
     *
     * Takes the current scene as input for functions
     *
     */

    std::string result;

    // Reading action -> userIn[0]
    Actions userAction = Actions::LAST;
    for (int i = static_cast<int>(Actions::GO); i < static_cast<int>(Actions::LAST); ++i ) {
        if (userIn[0].compare(actionsText[i]) == 0)
            userAction = static_cast<Actions>(i);
    }

    if (userAction == Actions::LAST)
        return "Eu não entendi o que você quis dizer com " + userIn[0];		// Localize

    // Executing the action
    switch(userAction) {
	case Actions::GO: {
            Directions newDirection = Directions::LAST;
            for (int i = static_cast<int>(Directions::NORTE); i < static_cast<int>(Directions::LAST); ++i) {
                if (userIn[1].compare(directionsText[i]) == 0)
                    newDirection = static_cast<Directions>(i);
	    }
	    if (newDirection == Directions::LAST) {
		//cout << "Essa direção não existe\n";
		printw("Essa direção não existe\n");
                refresh();
		break;
	    }
            action_go(currentLoad, newDirection);
	    currentLoad.get_scene().show_scene();		// Revisar isto
	    break;
        }
	case Actions::ATTACK: {
	    break;
        }
	case Actions::TAKE: {
	    //cout << currentLoad.get_scene().items_size() << '\n';
	    for (int i = 0; i < currentLoad.get_scene().items_size(); ++i) {
	        if (userIn[1] == currentLoad.get_scene().get_item(i).get_name()) {	// insert upper
		    // Put on the character items
		    // Remove from the json scene
		    currentLoad.get_scene().remove_item(i);	// Remove from the scene
                    break;
		}
	    }
	    result = "Taken";
	    break;
        }
	case Actions::LOOK: {
	    currentLoad.get_scene().show_scene();
	    break;
        }
	case Actions::SAY: {
            break;
	}
	
        case Actions::EXIT: {
	    // Last save
	    // Exit
	    result = "exit";
	}
	case Actions::LAST: {
	
	    break;
        }
    }

    return result;
}

void action_go(GameLoad& currentLoad, Directions newDirection) {
    Scene oldScene = currentLoad.get_scene();
    for (int i = 0; i < oldScene.directions_size(); ++i) {
        if (oldScene.get_direction(i) == newDirection) {
	    // Getting newScene text
	    std::string newSceneText = oldScene.get_direction_map(i);
	    currentLoad.set_scene(json_to_scene((char *)newSceneText.c_str(), (char *)currentLoad.get_scenario_json().c_str()));
	    return;
	}
    }

    printw("Você não pode ir nessa direção\n");
    refresh();
}

