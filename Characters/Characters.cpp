#include "Characters.hpp"

std::string Character::get_name() {return name;}
void Character::set_name(std::string newName) {
    name = newName;
}
CharacterType Character::get_type() {return typeCharacter;}
void Character::set_type(CharacterType newType) {
    typeCharacter = newType;
}
int Character::get_age() {return age;}
void Character::set_age(std::string newAge) {
    age = std::stoi(newAge);
}
std::string Character::get_race() {return race;}
void Character::set_race(std::string newRace) {
    race = newRace;
}
std::string Character::get_classes() {return classes;}
void Character::set_classes(std::string newClass) {
    classes = newClass;
}
int Character::get_STR() {return STR;}
void Character::set_STR(int newValue) {STR = newValue;}
int Character::get_DEX() {return DEX;}
void Character::set_DEX(int newValue) {DEX = newValue;}
int Character::get_CON() {return CON;}
void Character::set_CON(int newValue) {CON = newValue;}
int Character::get_INT() {return INT;}
void Character::set_INT(int newValue) {INT = newValue;}
int Character::get_WIS() {return WIS;}
void Character::set_WIS(int newValue) {WIS = newValue;}
int Character::get_CHA() {return CHA;}
void Character::set_CHA(int newValue) {CHA = newValue;}
int Character::get_Att(int i) {return Att[i];}
void Character::set_Att() {}
int Character::get_Lp() {return Lp;}
void Character::set_Lp() {}
int Character::get_Def() {return Def;}
void Character::set_Def() {}
int Character::get_Hung() {return Hung;}
void Character::set_Hung() {}
std::string Character::get_langs(int i) {return langs[i];}
void Character::set_langs() {}
std::string Character::get_hands(int i) {return hands[i];}
void Character::set_hands() {}
std::string Character::get_fingers(int i) {return fingers[i];}
void Character::set_fingers() {}
std::string Character::get_head(int i) {return head[i];}
void Character::set_head() {}
std::string Character::get_cloths(int i) {return cloths[i];}
void Character::set_cloths() {}
int Character::get_gold() {return gold;}
void Character::set_gold() {}
std::string Character::get_backpack(int i) {return backpack[i];}
void Character::set_backpack() {}
std::string Character::get_belt(int i) {return belt[i];}
void Character::set_belt() {}


int base_table(int x) {
    /*
     * A conversions for the game Base_table
     * See the README file
     */
    return static_cast<int>(floor((x*10 - 100) / 20));
}

Character create_character() {
    char userIn[STR_LIMIT];
    Character returnCharacter;

    returnCharacter.set_type(CharacterType::Player);
    // Char Name
    printw("Type your Name: \n");
    getnstr( userIn, STR_LIMIT);
    returnCharacter.set_name(static_cast<std::string>(userIn));

    // Char Age
    printw("Type your Age: \n");
    getnstr( userIn, STR_LIMIT);
    returnCharacter.set_age(static_cast<std::string>(userIn));

    // Char Race
    printw("Choose a race: (Human, Elf, Dwarf or Halfling): \n");
    getnstr( userIn, STR_LIMIT);
    returnCharacter.set_race(static_cast<std::string>(userIn));

    // Char Class
    printw("Choose a class: (Mage, Knight, Thief or Cleric): \n");
    getnstr( userIn, STR_LIMIT);
    returnCharacter.set_classes(static_cast<std::string>(userIn));

    // Primary Attributes
    printw("Now is time to roll your primary attributes...\n");
    printw("Press any key to continue: ");
    noecho();
    char _temp = getch();

    int tempInt = 0;

    do {
        printw("\n\nRolling: ");

        tempInt = generate_rand_int() + generate_rand_int() + generate_rand_int();
        printw("STR: %d  ", tempInt);
        returnCharacter.set_STR(tempInt);

        tempInt = generate_rand_int() + generate_rand_int() + generate_rand_int();
        printw("DEX: %d  ", tempInt);
        returnCharacter.set_DEX(tempInt);

        tempInt = generate_rand_int() + generate_rand_int() + generate_rand_int();
        printw("CON: %d  ", tempInt);
        returnCharacter.set_CON(tempInt);

        tempInt = generate_rand_int() + generate_rand_int() + generate_rand_int();
        printw("INT: %d  ", tempInt);
        returnCharacter.set_WIS(tempInt);

        tempInt = generate_rand_int() + generate_rand_int() + generate_rand_int();
        printw("WIS: %d  ", tempInt);
        returnCharacter.set_WIS(tempInt);

        tempInt = generate_rand_int() + generate_rand_int() + generate_rand_int();
        printw("CHA: %d  ", tempInt);
        returnCharacter.set_CHA(tempInt);


        refresh();
        echo();

        printw("\n\nReroll attributes?(y or n): ");
        getnstr(userIn, STR_LIMIT);

    } while (strcmp(userIn, "y") == 0);

    printw("\n\n");


    return returnCharacter;
}

void change_char_attribute(std::string attribute, std::string newValue) {
}
