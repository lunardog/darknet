#include <Python.h>
#include "network.h"
#include "parser.h"

struct module_state {
    PyObject *error;
    int test;
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

static PyObject *
say_hello(PyObject* self, PyObject* args)
{
    const char* name;

    if (!PyArg_ParseTuple(args, "s", &name))
        return NULL;

    GETSTATE(self)->net = parse_network_cfg(name);

    printf("Hello %s! %d\n", name, GETSTATE(self)->test);

    Py_RETURN_NONE;
}

static PyMethodDef darknet_methods[] = {
    {"error_out", (PyCFunction)error_out, METH_NOARGS, NULL},
    {"say_hello", say_hello, METH_VARARGS, "Greet somebody."},
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