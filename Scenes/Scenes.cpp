#include "Scenes.hpp"

void Scene::set_name(std::string nameIn) {
    name = nameIn;
}

std::string Scene::get_name() {
    std::string result (name);
    return result;
}

void Scene::set_text(std::string textIn) {
    text = textIn;
}

std::string Scene::get_text() {
    return text;
}

void Scene::set_directions(std::vector<Directions> directionsInput) {
    for (int i = 0; i < directionsInput.size(); ++i) {
        directions.push_back(directionsInput[i]);
    }
}

int Scene::directions_size() {
    return directions.size();
}
Directions Scene::get_direction(int i) {
    return directions[i];
}
std::vector<Directions> Scene::get_directions() {
    return directions;
}
std::vector<std::string> Scene::get_directions_map() {
    return directionsMap;
}
std::string Scene::get_direction_map(int i) {
    return directionsMap[i];
}
void Scene::set_directions_map(std::vector<std::string> mapInput) {
    for (int i = 0; i < mapInput.size(); ++i) {
        directionsMap.push_back(mapInput[i]);
    }
}

void Scene::set_actions(std::vector<Actions> actionsInput) {
    for (int i = 0; i < actionsInput.size(); ++i) {
         actions.push_back(actionsInput[i]);
    }
}

std::vector<Actions> Scene::get_actions() {
    return actions;
}

//Actions Scene::get_action(int i) {
//    return actions[i];
//}

Item Scene::get_item(int i) {
    return items[i];
}
int Scene::items_size() {
    return items.size();
}
void Scene::remove_item(int i) {
    items.erase(std::next(items.begin(), i));
}
void Scene::set_items(std::vector<std::string> itemsInput) {
    for (int i = 0; i < itemsInput.size(); ++i) {
        Item newItem;
        newItem.set_name(itemsInput[i]);
        items.push_back(newItem);
    }
}

Character* Scene::get_character(int i) {return charactersInScene[i];}
int Scene::get_characters_size() {
    return charactersInScene.size();
}
void Scene::set_character(Character* newCharacter) {
    charactersInScene.push_back(newCharacter);
}
void Scene::remove_character(int i) {
    charactersInScene.erase(std::next(charactersInScene.begin(), i));
}

void Scene::show_scene () {		// Prints the scene text and contend
    //std::cout << name[0] << text[0] << "teste\n\n";
    printw("%s\n\n%s", &name[0], &text[0]);

    if (items.size() > 0) {
	printw("Tem uma ");
        for (int i = 0; i < items.size(); ++i) {
            if (i == items.size() - 1) {
                if (i > 0)
		    printw(" e uma ");
                printw("%s aqui\n", &items[i].get_name()[0]);
                break;
            }
            if (i > 0){
	        printw(", a ");
	    }
	    printw("%s", &items[i].get_name()[0]);
        }
    }
    addch('\n');
    refresh();
};

