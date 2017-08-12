//
// Created by User on 11. 08. 2017.
//

#include <stdio.h>
#include <Python.h>
#include "../main.h"

static PyObject* call_k_means(PyObject* self, PyObject* args)
{
    int n_latPoints;
    int n_lonPoints;
    double tempLat;
    double tempLon;

    PyObject *latListObj;
    PyObject *lonListObj;

    PyObject *latFloatObj;
    PyObject *lonFloatObj;

    int N;
    int K;

    /* the O! parses for a Python object (listObj) checked
       to be of type PyList_Type */
    if (! PyArg_ParseTuple( args, "O!O!i", &PyList_Type, &latListObj,
                                           &PyList_Type, &lonListObj,
                                           &K)) {
        printf("SHIT 01\n");
        return NULL;
    }

    // get the number of lines passed to us
    n_latPoints = PyList_Size(latListObj);
    n_lonPoints = PyList_Size(lonListObj);
    // should raise an error here
    if (n_latPoints != n_lonPoints) {
        printf("SHIT 02\n");
        return NULL;
    }
    N = n_latPoints;

    double latPoints[N];
    double lonPoints[N];

    // should raise an error here
    if (n_latPoints < 0) {
        printf("SHIT 03\n");
        return NULL; // Not a list
    }

    printf("K: %d, N: %d\n", K, N);
    for (int i = 0; i < n_latPoints; i++) {
        latFloatObj = PyList_GetItem(latListObj, i); // Can't fail WHY?
        lonFloatObj = PyList_GetItem(lonListObj, i);

        tempLat = PyFloat_AsDouble(latFloatObj);
        tempLon = PyFloat_AsDouble(lonFloatObj);

        latPoints[i] = tempLat;
        lonPoints[i] = tempLon;

        // printf("lat: %f lon: %f\n", tempLat, tempLon);
    }
    k_means(latPoints, lonPoints, N, K);

    Py_RETURN_NONE;
}

static PyMethodDef KmeansMethods[] = {
        {"call_k_means", call_k_means, METH_VARARGS, "Call k-means test function."},
        {NULL, NULL, 0, NULL}
};

//             init"filename "
PyMODINIT_FUNC inittestmodule(void)
{
    //                   " filename "
    (void) Py_InitModule("testmodule", KmeansMethods);
}