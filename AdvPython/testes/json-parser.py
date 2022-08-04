import json

def read_json_file(fileName):
    '''
    Reads a json files and returns a dict with its content
    '''
    with open(fileName, 'r') as tempFile:
        return json.load(tempFile)

def get_scene_from_file(sceneName, fileName):
    '''
    Returns the scene as a dict
    '''
    result = read_json_file(fileName).get(sceneName).get('Name')
    print(result)
    return result
