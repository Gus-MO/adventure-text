#define PY_SSIZE_T_CLEAN
#include <Python.h>

static int numargs=0;

static PyObject*
emb_numargs(PyObject *self, PyObject *args)
{
    if(!PyArg_ParseTuple(args, ":numargs"))
        return NULL;
    return PyLong_FromLong(numargs);
}

static PyMethodDef EmbMethods[] = {
    {"numargs", emb_numargs, METH_VARARGS,
     "Return the number of arguments received by the process."},
    {NULL, NULL, 0, NULL}
};

static PyModuleDef EmbModule = {
    PyModuleDef_HEAD_INIT, "emb", NULL, -1, EmbMethods,
    NULL, NULL, NULL, NULL
};

static PyObject*
PyInit_emb(void)
{
    return PyModule_Create(&EmbModule);
}

int main(int argc, char *argv[]) {
    numargs = argc;
    PyImport_AppendInittab("emb", &PyInit_emb);

    PyObject *pName, *pModule, *pFunc;
    PyObject *pArgs, *pValue;

    //Initialize the python instance
    Py_Initialize();

    PyRun_SimpleString("import sys\nsys.path.append('.')");

    // Getting module name and importing
    pName = PyUnicode_DecodeFSDefault(argv[1]);
    pModule = PyImport_Import(pName);

    Py_DECREF(pName);

    // Checking module import
    if (pModule == NULL) {
        PyErr_Print();
        fprintf(stderr, "Failed to load \"%s\"\n", argv[1]);
        return 1;
    }

    // Getting function name
    pFunc = PyObject_GetAttrString(pModule, argv[2]);

    // Checking for errors
    if (!pFunc && !PyCallable_Check(pFunc)) {
        if (PyErr_Occurred())
                PyErr_Print();
            fprintf(stderr, "Cannot find function \"%s\"\n", argv[2]);
        Py_XDECREF(pFunc);
        Py_DECREF(pModule);
    }

    pArgs = PyTuple_New(argc - 3);

    // Getting args for function
    for (int i = 0; i < argc - 3; ++i) {
        //pValue = PyLong_FromLong(atoi(argv[i + 3]));
        pValue = PyUnicode_DecodeFSDefault(argv[i + 3]);
        if (!pValue) {
            Py_DECREF(pArgs);
            Py_DECREF(pModule);
            fprintf(stderr, "Cannot convert argument\n");
            return 1;
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
        return 1;
    }

    // Printing functions return value
    //printf("Result of call: %ld\n", PyLong_AsLong(pValue));
    //printf("Result of call: %s\n", PyByteArray_AsString(pValue));
    Py_DECREF(pValue);

    // Final
    if (Py_FinalizeEx() < 0) {
        return 120;
    }

    return 0;
}
