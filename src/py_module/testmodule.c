//
// Created by User on 11. 08. 2017.
//

#include <Python.h>
#include "../main.h"

static PyObject* call_k_means(PyObject* self, PyObject* args)
{
    int n;
    if (!PyArg_ParseTuple(args, "i", &n))
        return NULL;
    int ret;
    ret = k_means();
    Py_RETURN_NONE;
}

static PyMethodDef KmeansMethods[] = {
        {"call_k_means", call_k_means, METH_VARARGS, "Call k-means test function."},
        {NULL, NULL, 0, NULL}
};

PyMODINIT_FUNC inittestmodule(void)
{
    (void) Py_InitModule("testmodule", KmeansMethods);
}