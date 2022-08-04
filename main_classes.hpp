#pragma once

#include <string>
#include <vector>

#include "main_enums.hpp"

struct Effects {
    int Armor;
    std::string Active;
    std::string Passive;
    int Attribute;              // How to define whuch attribute?
};

class Character {
    public:
	Character (
	/*
            std::string strName,
	    std::string strClass,
	    std::string strRace,
	    int intStr,
	    int intDex,
	    int intCon,
	    int intInt,
	    int intWis,
	    int intCha,
	    CharacterType charType
	*/
	    ):
	    typeCharacter{},
	    name{},
	    age{},
	    race{},
	    classes{},
	    STR{},
	    DEX{},
	    CON{},
	    INT{},
	    WIS{},
	    CHA{},
	    Att{},
	    Lp{},
	    Def{},
	    Hung{},
	    langs{},
	    hands{},
	    fingers{},
	    head{},
	    cloths{},
	    gold{},
	    backpack{},
	    belt{}
	    {}

        std::string get_name();
	void set_name(std::string newName);
        CharacterType get_type();
	void set_type(CharacterType newType);
        int get_age();
	void set_age(std::string newAge);
	std::string get_race();
	void set_race(std::string newRace);
        std::string get_classes();
	void set_classes(std::string newClass);
        int get_STR();
	void set_STR(int newValue);
        int get_DEX();
	void set_DEX(int newValue);
        int get_CON();
	void set_CON(int newValue);
        int get_INT();
	void set_INT(int newValue);
        int get_WIS();
	void set_WIS(int newValue);
        int get_CHA();
	void set_CHA(int newValue);
        int get_Att(int i);
	void set_Att();
        int get_Lp();
	void set_Lp();
        int get_Def();
	void set_Def();
        int get_Hung();
	void set_Hung();
        std::string get_langs(int i);
	void set_langs();
        std::string get_hands(int i);
	void set_hands();
        std::string get_fingers(int i);
	void set_fingers();
        std::string get_head(int i);
	void set_head();
        std::string get_cloths(int i);
	void set_cloths();
        int get_gold();
	void set_gold();
        std::string get_backpack(int i);
	void set_backpack();
        std::string get_belt(int i);
	void set_belt();

    private:
	// character definitions
        CharacterType typeCharacter;
	std::string name;
	int age;
	std::string race;
	std::string classes;

	// primary attributes -- the classic ones
	int STR;
	int DEX;
	int CON;
	int INT;
	int WIS;
	int CHA;

	// secundary attributes
	std::vector<int>Att;
	int Lp;
	int Def;
	int Hung;

	// terciary attributes
	std::vector<std::string> langs;

	// equipment
	std::vector<std::string> hands;
	std::vector<std::string> fingers;
	std::vector<std::string> head;
	std::vector<std::string> cloths;
	
	// inventory
	int gold;
	std::vector<std::string> backpack;
	std::vector<std::string> belt;
};

class GameHistory {
    public:
        GameHistory(std::string savePath) :
	    historySz{},
	    history{},
	    saveName{savePath}
	    {}

	void add_action(std::string action);
	void save_file();		// Saving to the .save file
	std::string get_path_name();

    private:
	int historySz;
	std::vector<std::string> history;
	std::string saveName;		// The save name on user saves
};


class Item {
    public:
        Item() :
	    name{},
	    type{},
	    effects{}
	{}

	std::string get_name();
	void set_name(std::string newName);

	ItemType get_type();
	void set_type(ItemType newType);

	Effects get_effect();
	void set_effect(Effects newEffect);

    private:
	std::string name;
	ItemType type;
	Effects effects;
};

class Scene {
    public:
        Scene() :
            name{},
            text{},
 	    actions{},
	    directions{},
            directionsMap{},
	    items{},
	    charactersInScene{}
            {}

        void set_name(std::string nameIn);
	std::string get_name();
        void set_text(std::string textIn);
	std::string get_text();
	void set_directions(std::vector<Directions> directionsInput);
	int directions_size();
	Directions get_direction(int i);
	std::vector<Directions> get_directions();
	std::vector<std::string> get_directions_map();
	std::string get_direction_map(int i);
	void set_directions_map(std::vector<std::string> mapInput);
	void set_actions(std::vector<Actions> actionsInput);
        std::vector<Actions> get_actions();
	Item get_item(int i);
	int items_size();
	void remove_item(int i);
	void set_items(std::vector<std::string> itemsInput);
	Character* get_character(int i);
	int get_characters_size();
	void set_character(Character* newCharacter);
	void remove_character(int i);
	void show_scene ();

    private:
	std::string name;
	std::string text;
        std::vector<Actions> actions;
	std::vector<Directions> directions;
	std::vector<std::string> directionsMap;
        std::vector<Item> items;
	std::vector<Character*> charactersInScene;		// Not players

};

class GameLoad {		// Necessary loaded infos
    public:
        GameLoad () :
            currentScene{},
            scenarioJson{},	// string of the current game json file
	    player{}
            {}

	std::string get_scenario_json();
	void set_scenario_json(std::string scenarioIn);

	Scene get_scene();
	void set_scene(Scene sceneIn);

        Character* get_player();
	void set_player(Character newPlayer);

    private:
        Scene currentScene;
	std::string scenarioJson;	// Name of the file json for the save
	Character player;
};
