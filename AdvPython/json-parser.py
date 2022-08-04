import json
import os
import shutil
from configparser import ConfigParser

def read_json_file(fileName):
    '''
    Reads a json files and returns a dict with its content
    '''
    with open(fileName, 'r') as tempFile:
        return json.load(tempFile)

def json_to_scene(fileName):
    return Scene()


def get_scene_from_file(sceneName, fileName):
    '''
    Returns the scene as a dict
    '''
    return read_json_file(fileName).get(sceneName)

def get_scene_attribute(attName, sceneName, fileName):
    '''
    '''
    with open(fileName, 'r') as tempFile:
        tempJson = ''
        try:
            tempJson = json.load(tempFile)
            tempJson = tempJson.get(sceneName)
            tempJson = tempJson.get(attName)
        except:
            print('Scene or Atrribute not found')
        if type(tempJson) is not list:
            return [tempJson]
        else:
            return tempJson

def change_file_attribute(attName, sceneName, newValue, fileName):
    '''
    Takes a new att name and replaces on the given file
    '''
    tempJson = ''
    with open(fileName, 'r') as tempFile:
        tempJson = json.load(tempFile)
    with open(fileName, 'w') as tempFile:
        for key in tempJson.keys():
            if tempJson[key]["Name"] == sceneName:
                tempJson[key][attName] = newValue
        json.dump(tempJson, tempFile, indent=4)

def get_save(pathName, adventureName):
    '''
    '''
    initialize_save(pathName, adventureName)
    save_path = pathName+'/'+adventureName+'/save/'

    sceneName = ""

     # create a parser
    parser = ConfigParser()
    # read config file
    parser.read(save_path+adventureName+'.save')
    if parser.has_section('Scene'):
        sceneName = parser['Scene']['scene']

    """ Old way
    with open(save_path+adventureName+'.save', 'r') as tempFile:
        for line in tempFile:
            if line.startswith('-scene: '):
                sceneName = line.replace('-scene: ', '').strip()
    """
    jsonName = save_path+'../'+adventureName+'.json'

    return [sceneName, jsonName]

def save_json(pathName, adventureName, newJsonScene):
    '''
    '''
    save_path = pathName+'/'+adventureName+'/save/'+adventureName+'.json'
    for key in newJsonScene.keys():
        change_file_attribute(key, newJsonScene['Name'], newJsonScene[key], save_path)

    return 1

def initialize_save(pathName, adventureName):
    '''
    Check if the save file exists and creats it
    case don't
    '''
    save_path = os.path.join(pathName,adventureName,'save')
    #save_path = pathName+'/'+adventureName+'/save/'
    if not os.path.exists(save_path):
        os.mkdir(save_path)
        with open(os.path.join(save_path,adventureName+'.save'), 'x') as tempFile:
            parser = ConfigParser()
            parser['Scene'] = {'scene': 'scene1'}
            parser.write(tempFile)
        with open(os.path.join(pathName,adventureName,adventureName+'.json'), 'r') as tempOficial:
            with open(os.path.join(save_path,adventureName+'.json'), 'w') as tempOut:
            # Opening oficial file for adventure
                for line in tempOficial:
                    tempOut.write(line)
