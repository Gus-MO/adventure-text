import os
from configparser import ConfigParser

def check_character(save_path, adventureName, characterType):
    parser = ConfigParser()
    parser.read(save_path+'/'+adventureName+'/save/'+adventureName+'.save')
    if parser.has_section(characterType):
        return 1
    else:
        return 0

def read_character(save_path, adventureName, characterType):
    '''
    Reads a character from a file and return a list
    with his characteristics

    Args
    ----
    characterType: Player, MOB or NPC
    '''
    result = []

    # create a parser
    parser = ConfigParser()
    # read config file
    parser.read(save_path+'/'+adventureName+'/save/'+adventureName+'.save')
    if parser.has_section(characterType):
        params = parser.items(characterType)
        for param in params:
            result.append = param[1]

    return result

def save_character(save_path, adventureName, characterDict):
    parser = ConfigParser()


    with open(save_path+'/'+adventureName+'/save/'+adventureName+'.save', 'r') as tempFile:
        parser.read(tempFile)

    parser.remove_section('Player')
    parser["Player"] = characterDict

    with open(save_path+'/'+adventureName+'/save/'+adventureName+'.save', 'w') as tempFile:
        parser.write(tempFile)

    return 0
