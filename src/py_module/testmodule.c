//
// Created by User on 11. 08. 2017.
//

#include <stdio.h>
#include <Python.h>
#include "../main.h"

static PyObject* call_k_means(PyObject* self, PyObject* args)
{
    int n_latPoints;  // Number of latitude points received from caller
    int n_lonPoints;  // Number of longitude points received from caller

    PyObject *latListObj;  // Buffer for received latitude points as python list
    PyObject *lonListObj;  // Buffer for received longitude points as python list

    int N;  // Number of points (length of points)
    int K;  // K in k-means - number of clusters we assume there are

    // the O! parses for a Python object (listObj) checked to be of type PyList_Type
    if (! PyArg_ParseTuple( args, "O!O!i", &PyList_Type, &latListObj,
                                           &PyList_Type, &lonListObj,
                                           &K)) {
        return NULL;
    }

    // get the number of lines passed to us
    n_latPoints = PyList_Size(latListObj);
    n_lonPoints = PyList_Size(lonListObj);
    // should raise an error here
    if (n_latPoints != n_lonPoints) {
        PyErr_SetString(PyExc_ValueError, "'lat' and 'lon' lists must have equal length.");
        return NULL;
    }
    N = n_latPoints;

    double *latPoints = (double *) malloc(sizeof(double) * N);
    double *lonPoints = (double *) malloc(sizeof(double) * N);

    // should raise an error here
    if (n_latPoints < 0) {
        PyErr_SetString(PyExc_ValueError, "Less then zero points supplied.");
        return NULL; // Not a list
    }

    printf("K: %d, N: %d\n", K, N);
    for (int i = 0; i < n_latPoints; i++) {
        *(latPoints + i) = PyFloat_AsDouble(PyList_GetItem(latListObj, i));;
        *(lonPoints + i) = PyFloat_AsDouble(PyList_GetItem(lonListObj, i));
    }
    // printf("testmodule - calling 'call_k_means() ...\n'");
    struct cluster *clusters = (struct cluster *) malloc(sizeof(struct cluster) * K);
    k_means(latPoints, lonPoints, N, K, clusters);

    PyObject *pList = PyList_New(K); // new reference
    assert(PyList_Check(pList));

    for (int i = 0; i < K; i++) {
        // print_cluster(clusters[c]);
        printf("#%d:\n    N:%d\n    (%f, %f)\n", i, clusters[i].num_points, clusters[i].center.lat, clusters[i].center.lon);

        PyObject *pDict = PyDict_New(); // new reference
        assert(PyDict_Check(pDict));

        PyDict_SetItemString(pDict, "num_points", Py_BuildValue("i", clusters[i].num_points));
        PyDict_SetItemString(pDict, "center", Py_BuildValue("(f,f)", clusters[i].center.lat, clusters[i].center.lon));

        PyList_SetItem(pList, i, pDict);

        free(clusters[i].cluster_points);
    }
    // Clean
    free(clusters);
    free(latPoints);
    free(lonPoints);
    return pList;
}

static PyMethodDef KmeansMethods[] = {
        {"call_k_means", call_k_means, METH_VARARGS, "Calculate cluster based on K-means algorithm."},
        {NULL, NULL, 0, NULL}
};

//             init"filename "
PyMODINIT_FUNC inittestmodule(void)
{
    //                   " filename "
    (void) Py_InitModule("testmodule", KmeansMethods);
}