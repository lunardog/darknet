#include <Python.h>
#include "network.h"
#include "parser.h"

struct module_state {
    PyObject *error;
    network net;
};

#if PY_MAJOR_VERSION >= 3
#define GETSTATE(m) ((struct module_state*)PyModule_GetState(m))
#else
#define GETSTATE(m) (&_state)
static struct module_state _state;
#endif

static PyObject *
error_out(PyObject *m) {
    struct module_state *st = GETSTATE(m);
    PyErr_SetString(st->error, "something bad happened");
    return NULL;
}

static PyObject *_parse_network_cfg(PyObject* self, PyObject* args) {
    char* filename;
    if (!PyArg_ParseTuple(args, "s", &filename))
        return NULL;
    GETSTATE(self)->net = parse_network_cfg(filename);
    Py_RETURN_NONE;
}

static PyObject *_load_weights(PyObject* self, PyObject* args) {
    char* filename;
    if (!PyArg_ParseTuple(args, "s", &filename))
        return NULL;
    load_weights(&GETSTATE(self)->net, filename);
    Py_RETURN_NONE;
}

static PyObject *_network_predict(PyObject* self, PyObject* args) {
    
}

static PyMethodDef darknet_methods[] = {
    {"error_out", (PyCFunction)error_out, METH_NOARGS, NULL},
    {"parse_network_cfg", _parse_network_cfg, METH_VARARGS, "Parse network cfg"},
    {"load_weights", _load_weights, METH_VARARGS, "Load weights"},
    {"network_predict", _network_predict, METH_VARARGS, "Network predict"},
    {NULL, NULL}
};

#if PY_MAJOR_VERSION >= 3

// this is for garbage collection
static int darknet_traverse(PyObject *m, visitproc visit, void *arg) {
    Py_VISIT(GETSTATE(m)->error);
    return 0;
}

// this is for garbage collection
static int darknet_clear(PyObject *m) {
    Py_CLEAR(GETSTATE(m)->error);
    return 0;
}


static struct PyModuleDef moduledef = {
        PyModuleDef_HEAD_INIT,
        "darknet",
        NULL,
        sizeof(struct module_state),
        darknet_methods,
        NULL,
        darknet_traverse,
        darknet_clear,
        NULL
};

#define INITERROR return NULL

PyMODINIT_FUNC
PyInit_darknet(void)

#else
#define INITERROR return

void
initdarknet(void)
#endif
{
#if PY_MAJOR_VERSION >= 3
    PyObject *module = PyModule_Create(&moduledef);
#else
    PyObject *module = Py_InitModule("darknet", darknet_methods);
#endif

    if (module == NULL) {
        INITERROR;
    }
    struct module_state *st = GETSTATE(module);

    st->error = PyErr_NewException("darknet.Error", NULL, NULL);
    if (st->error == NULL) {
        Py_DECREF(module);
        INITERROR;
    }

#if PY_MAJOR_VERSION >= 3
    return module;
#endif
}