#include "AdvPython.hpp"
#include <iostream>

PyObject* getPyFunc(char *moduleName, char *funcName, std::vector<char*> funcArgs, PyObject* pValue) {
    PyObject *pName, *pModule, *pFunc;
    PyObject *pArgs;//, *pValue;

    //Initialize the python instance
    Py_Initialize();

    PyRun_SimpleString("import sys\nsys.path.append('.')\nsys.path.append('../include/AdvText/PySource')");

    // Getting module name and importing
    pName = PyUnicode_DecodeFSDefault(moduleName);
    pModule = PyImport_Import(pName);

    Py_DECREF(pName);

    // Checking module import
    if (pModule == NULL) {
        PyErr_Print();
        fprintf(stderr, "Failed to load 'adv_python' Module\n");
	exit(1);
    }

    // Getting function name
    pFunc = PyObject_GetAttrString(pModule, funcName);

    // Checking for errors
    if (!pFunc && !PyCallable_Check(pFunc)) {
        if (PyErr_Occurred()) {
            PyErr_Print();
            fprintf(stderr, "Cannot find function \"%s\"\n", funcName);
	}
        Py_XDECREF(pFunc);
        Py_DECREF(pModule);
    }

    pArgs = PyTuple_New(funcArgs.size());

    // Getting args for function
    for (size_t i = 0; i < funcArgs.size(); ++i) {
        pValue = PyUnicode_DecodeFSDefault(funcArgs[i]);
        if (!pValue) {
            Py_DECREF(pArgs);
            Py_DECREF(pModule);
            fprintf(stderr, "Cannot convert argument\n");
	    exit(1);
        }
        PyTuple_SetItem(pArgs, i, pValue);
    }

    // Getting function return value
    pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);

    // Checking for errors
    if (pValue == NULL) {
        Py_DECREF(pFunc);
        Py_DECREF(pModule);
        PyErr_Print();
        fprintf(stderr,"Call failed\n");
	exit(1);
    }

    // Final
    if (Py_FinalizeEx() < 0) {
        exit(1);
    }

    return pValue;
}

PyObject* getPyFunc_fromDict(char *moduleName, char *funcName, std::vector<char*> funcArgs, PyObject* argDict, PyObject* pValue) {
    PyObject *pName, *pModule, *pFunc;
    PyObject *pArgs;//, *pValue;

    //Initialize the python instance
    Py_Initialize();

    PyRun_SimpleString("import sys\nsys.path.append('.')\nsys.path.append('../include/AdvText/PySource')");

    // Getting module name and importing
    pName = PyUnicode_DecodeFSDefault(moduleName);
    pModule = PyImport_Import(pName);

    Py_DECREF(pName);

    // Checking module import
    if (pModule == NULL) {
        PyErr_Print();
        fprintf(stderr, "Failed to load 'adv_python' Module\n");
	exit(1);
    }

    // Getting function name
    pFunc = PyObject_GetAttrString(pModule, funcName);

    // Checking for errors
    if (!pFunc && !PyCallable_Check(pFunc)) {
        if (PyErr_Occurred()) {
            PyErr_Print();
            fprintf(stderr, "Cannot find function \"%s\"\n", funcName);
	}
        Py_XDECREF(pFunc);
        Py_DECREF(pModule);
    }

    pArgs = PyTuple_New(funcArgs.size() + 1);
    
    size_t i = 0;
    // Getting args for function
    for (; i < funcArgs.size(); ++i) {
        pValue = PyUnicode_DecodeFSDefault(funcArgs[i]);
        if (!pValue) {
            Py_DECREF(pArgs);
            Py_DECREF(pModule);
            fprintf(stderr, "Cannot convert argument\n");
	    exit(1);
        }
        PyTuple_SetItem(pArgs, i, pValue);
    }
    PyTuple_SetItem(pArgs, i, argDict);

    // Getting function return value
    pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);

    // Checking for errors
    if (pValue == NULL) {
        Py_DECREF(pFunc);
        Py_DECREF(pModule);
        PyErr_Print();
        fprintf(stderr,"Call failed\n");
	exit(1);
    }

    // Final
    if (Py_FinalizeEx() < 0) {
        exit(1);
    }

    return pValue;
}

std::vector<std::string> get_json_att(char* fileName, char* attName, char* sceneName) {
    std::vector<char*> funcArgs;
    funcArgs.push_back(attName);
    funcArgs.push_back(sceneName);
    funcArgs.push_back(fileName);

    std::vector<std::string> finalOut;

    PyObject *tempPyOut;

    //tempPyOut = getPyFunc((char*)"json-parser", (char*)"get_scene_attribute", funcArgs);
    tempPyOut = getPyFunc((char*)"json-parser", (char*)"get_scene_attribute", funcArgs, tempPyOut);

    Py_ssize_t listSize = PyList_GET_SIZE(tempPyOut);
    for (Py_ssize_t i = 0; i < listSize; i++) {
        std::string tempString(PyUnicode_AsUTF8(PyList_GET_ITEM(tempPyOut, i)));
        finalOut.push_back(tempString);
    }

    //Py_DECREF(tempPyOut);
    return finalOut;
}

PyObject* scene_to_Dict(Scene sceneIn) {
    PyObject* newDict;
    Py_Initialize();
    newDict = PyDict_New();

    PyDict_SetItem(newDict, PyUnicode_FromString("Name"),  PyUnicode_FromString(sceneIn.get_name().c_str()) );
    PyDict_SetItem(newDict, PyUnicode_FromString("Text"),  PyUnicode_FromString(sceneIn.get_text().c_str()) );

    PyObject* newList;
    std::vector<std::string> tempVec = directions_to_string( sceneIn.get_directions());
    newList = PyList_New (tempVec.size());
    for (Py_ssize_t i = 0; i < PyList_Size(newList); i++) {
        PyList_SetItem(newList, i, PyUnicode_FromString(tempVec[i].c_str()));
    }

    PyDict_SetItem(newDict, PyUnicode_FromString("Allowed-Directions"), newList);

    tempVec = sceneIn.get_directions_map();
    newList = PyList_New (tempVec.size());
    for (Py_ssize_t i = 0; i < PyList_Size(newList); i++) {
        PyList_SetItem(newList, i, PyUnicode_FromString(tempVec[i].c_str()));
    }

    PyDict_SetItem(newDict, PyUnicode_FromString("Directions-Map"),   newList);

    tempVec = actions_to_string( sceneIn.get_actions() );
    newList = PyList_New (tempVec.size());
    for (Py_ssize_t i = 0; i < PyList_Size(newList); i++) {
        PyList_SetItem(newList, i, PyUnicode_FromString(tempVec[i].c_str()));
    }

    PyDict_SetItem(newDict, PyUnicode_FromString("Allowed-Actions"), newList);

    std::vector<std::string> tempItems;
    for (size_t i = 0; i < sceneIn.items_size(); i++) {
	tempItems.push_back(sceneIn.get_item(i).get_name());
    }

    newList = PyList_New (tempItems.size());
    for (Py_ssize_t i = 0; i < PyList_Size(newList); i++) {
        PyList_SetItem(newList, i, PyUnicode_FromString(tempItems[i].c_str()));
    }
    PyDict_SetItem(newDict, PyUnicode_FromString("Itens-in-scene"),  newList );
    Py_DECREF(newList);

    //sceneOut.set_(get_json_att(fileName, "Characters-in-scene", sceneName);

    return newDict;
}

Scene json_to_scene(char *sceneName, char *fileName) {
    Scene sceneOut;

    //std::cout << get_json_att<std::string>(fileName, (char*)"Name", sceneName) << "nop\n";
    sceneOut.set_name(get_json_att(fileName, (char*)"Name", sceneName)[0]);
    sceneOut.set_text(get_json_att(fileName, (char*)"Text", sceneName)[0]);

    sceneOut.set_directions(
	                   string_to_directions(
				                get_json_att(fileName, (char*)"Allowed-Directions", sceneName)
					       )
                          );

    sceneOut.set_directions_map(
	                        get_json_att(fileName, (char*)"Directions-Map", sceneName)
			       );

    sceneOut.set_actions(
	                 string_to_actions(
				           get_json_att(fileName, (char*)"Allowed-Actions", sceneName)
					  )
			);

    sceneOut.set_items(get_json_att(fileName, (char*)"Itens-in-scene", sceneName));
    //sceneOut.set_(get_json_att(fileName, "Characters-in-scene", sceneName);

    return sceneOut;
}

std::vector<std::string> directions_to_string(std::vector<Directions> vecIn) {
    std::vector<std::string> vecOut;

    for (size_t i = 0; i < vecIn.size(); i++) {
        vecOut.push_back(directionsText[static_cast<int>(vecIn[i])]);
    }
	
    return vecOut;
}

std::vector<Directions> string_to_directions(std::vector<std::string> vecIn) {
    /*
     *
     * A conversor to read the json files directions
     *
     */

    std::vector<Directions> vecOut(vecIn.size());
    for (size_t i = 0; i < vecIn.size(); ++i) {
        // Branchless test
        vecOut[i] = static_cast<Directions>(
                        (vecIn[i] == "N")*0 +
                        (vecIn[i] == "NE")*1 +
                        (vecIn[i] == "E")*2 +
                        (vecIn[i] == "SE")*3 +
                        (vecIn[i] == "S")*4 +
                        (vecIn[i] == "SW")*5 +
                        (vecIn[i] == "W")*6 +
                        (vecIn[i] == "NW")*7
                    );
    }

    return vecOut;
}

std::vector<std::string> actions_to_string(std::vector<Actions> vecIn) {
    std::vector<std::string> vecOut;

    for (size_t i = 0; i < vecIn.size(); i++) {
        vecOut.push_back(actionsText[static_cast<int>(vecIn[i])]);
    }
	
    return vecOut;
}

std::vector<Actions> string_to_actions(std::vector<std::string> vecIn) {
    /*
     *
     * A conversor to read the json files actions   
     *
     */

    std::vector<Actions> vecOut(vecIn.size());     
    for (size_t i = 0; i < vecIn.size(); ++i) {
        // Branchless test
        vecOut[i] = static_cast<Actions>(   
                        (vecIn[i] == "go")*0 +
                        (vecIn[i] == "attack")*1 +              
                        (vecIn[i] == "tale")*2 +
                        (vecIn[i] == "look")*3
                    );
    }

    return vecOut;
}

int load_save_file(std::string pathAdventures, std::string currentAdventure, GameLoad& currentLoad) {
    // Check for temp json, a save json
    std::vector<char*> funcArgs;
    funcArgs.push_back((char*)pathAdventures.c_str());
    funcArgs.push_back((char*)currentAdventure.c_str());

    PyObject *tempObject;

    //tempObject = getPyFunc((char*) "json-parser", (char*) "get_save", funcArgs, tempObject);
    tempObject = getPyFunc((char*) "json-parser", (char*) "get_save", funcArgs, tempObject);

    std::string sceneName (PyUnicode_AsUTF8(PyList_GET_ITEM(tempObject, (Py_ssize_t) 0 )));
    std::string jsonPath (PyUnicode_AsUTF8(PyList_GET_ITEM(tempObject, (Py_ssize_t) 1 )));

    //Py_DECREF(tempObject);

    Scene tempScene;
    tempScene = json_to_scene((char*) sceneName.c_str(), (char*) jsonPath.c_str());

    currentLoad.set_scene(tempScene);
    currentLoad.set_scenario_json(jsonPath);

    // Returning sucess
    return 1;
}

std::string load_json_save(std::string pathAdventures, std::string currentAdventure) {
    // Check for temp json, a save json
    std::vector<char*> funcArgs;
    funcArgs.push_back((char*)pathAdventures.c_str());
    funcArgs.push_back((char*)currentAdventure.c_str());

    PyObject* temp;

    temp = getPyFunc((char*) "json-parser", (char*) "initialize_save", funcArgs, temp);
    
    Py_DECREF(temp);

    // If there is no temp, create one

    std::string result("");
    return result;
}

Character load_saved_character(std::string pathAdventures, std::string currentAdventure) {
    Character finalChar;
    PyObject* tempObject;
    std::vector<char*> funcArgs;
    funcArgs.push_back((char*)pathAdventures.c_str());
    funcArgs.push_back((char*)currentAdventure.c_str());
    funcArgs.push_back((char*)"Player");

    tempObject = getPyFunc((char*) "character-parser", (char*) "read_character", funcArgs, tempObject);

    finalChar.set_name(static_cast<std::string>(PyUnicode_AsUTF8(PyList_GET_ITEM(tempObject, (Py_ssize_t) 0 ))));

    std::string tempString(PyUnicode_AsUTF8(PyList_GET_ITEM(tempObject, (Py_ssize_t) 1 )));

    CharacterType userType = CharacterType::LAST;
    for (int i = static_cast<int>(CharacterType::Player); i < static_cast<int>(CharacterType::LAST); ++i ) {
        if (tempString.compare(characterTypeText[i]) == 0)
            userType = static_cast<CharacterType>(i);
    }

    finalChar.set_type(userType);
    finalChar.set_age(static_cast<std::string>(PyUnicode_AsUTF8(PyList_GET_ITEM(tempObject, (Py_ssize_t) 2 ))));
    finalChar.set_race(static_cast<std::string>(PyUnicode_AsUTF8(PyList_GET_ITEM(tempObject, (Py_ssize_t) 3 ))));
    finalChar.set_classes(static_cast<std::string>(PyUnicode_AsUTF8(PyList_GET_ITEM(tempObject, (Py_ssize_t) 4 ))));
    finalChar.set_STR(std::stoi(PyUnicode_AsUTF8(PyList_GET_ITEM(tempObject, (Py_ssize_t) 5 ))));
    finalChar.set_DEX(std::stoi(PyUnicode_AsUTF8(PyList_GET_ITEM(tempObject, (Py_ssize_t) 6 ))));
    finalChar.set_CON(std::stoi(PyUnicode_AsUTF8(PyList_GET_ITEM(tempObject, (Py_ssize_t) 7 ))));
    finalChar.set_INT(std::stoi(PyUnicode_AsUTF8(PyList_GET_ITEM(tempObject, (Py_ssize_t) 8 ))));
    finalChar.set_WIS(std::stoi(PyUnicode_AsUTF8(PyList_GET_ITEM(tempObject, (Py_ssize_t) 9 ))));
    finalChar.set_CHA(std::stoi(PyUnicode_AsUTF8(PyList_GET_ITEM(tempObject, (Py_ssize_t) 10 ))));
    //finalChar.set_Att(static_cast<std::string>(PyUnicode_AsUTF8(PyList_GET_ITEM(tempObject, (Py_ssize_t) 11 ))));
    //finalChar.set_Lp(static_cast<std::string>(PyUnicode_AsUTF8(PyList_GET_ITEM(tempObject, (Py_ssize_t) 12 ))));
    //finalChar.set_Def(static_cast<std::string>(PyUnicode_AsUTF8(PyList_GET_ITEM(tempObject, (Py_ssize_t) 13 ))));
    //finalChar.set_Hung(static_cast<std::string>(PyUnicode_AsUTF8(PyList_GET_ITEM(tempObject, (Py_ssize_t) 14 ))));
    //finalChar.set_langs(static_cast<std::string>(PyUnicode_AsUTF8(PyList_GET_ITEM(tempObject, (Py_ssize_t) 15 ))));
    //finalChar.set_hands(static_cast<std::string>(PyUnicode_AsUTF8(PyList_GET_ITEM(tempObject, (Py_ssize_t) 16 ))));
    //finalChar.set_fingers(static_cast<std::string>(PyUnicode_AsUTF8(PyList_GET_ITEM(tempObject, (Py_ssize_t) 17 ))));
    //finalChar.set_head(static_cast<std::string>(PyUnicode_AsUTF8(PyList_GET_ITEM(tempObject, (Py_ssize_t) 18 ))));
    //finalChar.set_cloths(static_cast<std::string>(PyUnicode_AsUTF8(PyList_GET_ITEM(tempObject, (Py_ssize_t) 19 ))));
    //finalChar.set_gold(static_cast<std::string>(PyUnicode_AsUTF8(PyList_GET_ITEM(tempObject, (Py_ssize_t) 20 ))));
    //finalChar.set_backpack(static_cast<std::string>(PyUnicode_AsUTF8(PyList_GET_ITEM(tempObject, (Py_ssize_t) 21 ))));
    //finalChar.set_belt(static_cast<std::string>(PyUnicode_AsUTF8(PyList_GET_ITEM(tempObject, (Py_ssize_t) 22 ))));

    Py_DECREF(tempObject);

    return finalChar;
}

int check_character (std::string pathAdventures, std::string currentAdventure) {
    std::vector<char*> funcArgs;
    funcArgs.push_back((char*)pathAdventures.c_str());
    funcArgs.push_back((char*)currentAdventure.c_str());
    funcArgs.push_back((char*)"Player");

    PyObject *tempObject;

    tempObject = getPyFunc((char*) "character-parser", (char*) "check_character", funcArgs, tempObject);

    int result = PyLong_AsLong(tempObject);
    //int result = std::stoi(tempObject);

    Py_DECREF(tempObject);

    return result;
}

/*
int copy_game_to_save (std::string pathAdventures, std::string currentAdventure) {
    std::vector<char*> funcArgs;

    funcArgs.push_back((char*)pathAdventures.c_str());
    funcArgs.push_back((char*)currentAdventure.c_str());
    
    tempObject = getPyFunc((char*) "json-parser", (char*) "copy_game", funcArgs, tempObject);

    int result = PyLong_AsLong(tempObject);

    return result;
}
*/

int save_scene(std::string pathAdventures, std::string currentAdventure, GameLoad &currentLoad) {
    PyObject* newDict;
    Py_Initialize();
    newDict = PyDict_New();

    newDict = scene_to_Dict(currentLoad.get_scene());

    std::vector<char*> funcArgs;

    funcArgs.push_back((char*)pathAdventures.c_str());
    funcArgs.push_back((char*)currentAdventure.c_str());

    PyObject *tempObject;

    tempObject = getPyFunc_fromDict((char*) "json-parser", (char*) "save_json", funcArgs, newDict, tempObject);

    int result = PyLong_AsLong(tempObject);

    return result;
}

int save_character(std::string pathAdventures, std::string currentAdventure, Character currentPlayer) {
    PyObject* newDict;
    Py_Initialize();
    newDict = PyDict_New();

    PyDict_SetItem(newDict, PyUnicode_FromString("Class"), PyUnicode_FromString(currentPlayer.get_classes().c_str() ) );
    PyDict_SetItem(newDict, PyUnicode_FromString("Race"),  PyUnicode_FromString(currentPlayer.get_race().c_str() ) );

    PyDict_SetItem(newDict, PyUnicode_FromString("Type"),  PyUnicode_FromString(characterTypeText[static_cast<int>(CharacterType::Player)].c_str() ) );

    PyDict_SetItem(newDict, PyUnicode_FromString("Age"),   PyLong_FromLong(currentPlayer.get_age() ) );
    PyDict_SetItem(newDict, PyUnicode_FromString("STR"),   PyLong_FromLong(currentPlayer.get_STR() ) );
    PyDict_SetItem(newDict, PyUnicode_FromString("DEX"),   PyLong_FromLong(currentPlayer.get_DEX() ) );
    PyDict_SetItem(newDict, PyUnicode_FromString("CON"),   PyLong_FromLong(currentPlayer.get_CON() ) );
    PyDict_SetItem(newDict, PyUnicode_FromString("INT"),   PyLong_FromLong(currentPlayer.get_INT() ) );
    PyDict_SetItem(newDict, PyUnicode_FromString("WIS"),   PyLong_FromLong(currentPlayer.get_WIS() ) );
    PyDict_SetItem(newDict, PyUnicode_FromString("CHA"),   PyLong_FromLong(currentPlayer.get_CHA() ) );
    //PyDict_SetItem(newDict, "Age", currentPlayer.get_Age());
    //PyDict_SetItem(newDict, "Att", currentPlayer.get_Att());
    //PyDict_SetItem(newDict, "Lp", currentPlayer.get_Lp());
    //PyDict_SetItem(newDict, "Def", currentPlayer.get_Def());
    //PyDict_SetItem(newDict, "Hung", currentPlayer.get_Hung());
    //PyDict_SetItem(newDict, "Langs", currentPlayer.get_langs());
    //PyDict_SetItem(newDict, "Hands", currentPlayer.get_hands());
    //PyDict_SetItem(newDict, "Fingers", currentPlayer.get_fingers());
    //PyDict_SetItem(newDict, "Head", currentPlayer.get_head());
    //PyDict_SetItem(newDict, "Cloths", currentPlayer.get_cloths());
    //PyDict_SetItem(newDict, "Gold", currentPlayer.get_gold());
    //PyDict_SetItem(newDict, "Backpack", currentPlayer.get_backpack());
    //PyDict_SetItem(newDict, "Belt", currentPlayer.get_belt());
    
    std::vector<char*> funcArgs;

    funcArgs.push_back((char*)pathAdventures.c_str());
    funcArgs.push_back((char*)currentAdventure.c_str());

    PyObject *tempObject;

    tempObject = getPyFunc_fromDict((char*) "character-parser", (char*) "save_character", funcArgs, newDict, tempObject);

    int result = PyLong_AsLong(tempObject);
    //int result = std::stoi(tempObject);

    //Py_DECREF(tempObject);

    return result;
}

//int main() {load_json_save("./testes", "nop");}
