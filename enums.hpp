enum class Actions {GO, ATTACK, TAKE, LOOK, LAST};
std::vector<std::string> actionsText = 
{
    "GO",
    "ATTACK",
    "TAKE",
    "LOOK"
};

enum class CharacterType {Player, Npc, Mob, LAST};
std::vector<std::string> characterTypeText =
{
    "Player",
    "Npc",
    "Mob"
};

enum class Directions{NORTE, NORDESTE, LESTE, SUDESTE, SUL, SUDOESTE, OESTE, NOROESTE, LAST};
std::vector<std::string> directionsText =
{
    "NORTE",
    "NORDESTE",
    "LESTE",
    "SUDESTE",
    "SUL",
    "SUDOESTE",
    "OESTE",
    "NOROESTE"
};

enum class ItemType{WEAPON, ARMOR, CLOTHING, ACESSORY, LAST};
std::vector<std::string> itemTypeText =
    {
        "Weapon",
        "Armor",
        "Clothing",
        "Acessory"
    };
