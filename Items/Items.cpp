#include "Items.hpp"

std::string Item::get_name(){return name;}
void Item::set_name(std::string newName) {
    name = newName;
}

ItemType Item::get_type(){return type;}
void Item::set_type(ItemType newType) {
    type = newType;
}

Effects Item::get_effect(){return effects;}
void Item::set_effect(Effects newEffect) {
    effects = newEffect;
}
