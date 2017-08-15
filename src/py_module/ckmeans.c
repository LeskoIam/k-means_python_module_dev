//
// Created by User on 11. 08. 2017.
//

#include <stdio.h>
#include <Python.h>
#include "../main.h"

static PyObject* call_k_means(PyObject* self, PyObject* args)
{
    // Number of latitude and longitude points received from caller
    int n_latPoints;
    int n_lonPoints;

    // Received latitude and longitude points as C array of doubles
    double *latPoints;
    double *lonPoints;

    // Buffer for received latitude and longitude points as Python list
    PyObject *latListObj;
    PyObject *lonListObj;

    // K-means
    int N;  // Number of points (length of points)
    int K;  // K in k-means - number of clusters we assume there are
    struct cluster *clusters;  // Array for K-means result


    // 'O!' parses for a Python object (listObj) checked to be of type PyList_Type
    // 'i' parses for Python integer
    if (! PyArg_ParseTuple( args, "O!O!i", &PyList_Type, &latListObj,
                                           &PyList_Type, &lonListObj,
                                           &K)) {
        return NULL;
    }

    // Get the length of the list passed to us
    n_latPoints = PyList_Size(latListObj);
    n_lonPoints = PyList_Size(lonListObj);

    // Check if latitude and longitude lists are the same length and raise an error if they are not
    if (n_latPoints != n_lonPoints) {
        PyErr_SetString(PyExc_ValueError, "'lat' and 'lon' lists must have equal length.");
        return NULL;
    }
    // Check that we got a valid list and raise an error if it is not
    if (n_latPoints < 0) {
        PyErr_SetString(PyExc_ValueError, "Less then zero points supplied.");
        return NULL; // Not a list
    }
    N = n_latPoints;

    // Allocate space for received points
    latPoints = (double *) malloc(sizeof(double) * N);
    lonPoints = (double *) malloc(sizeof(double) * N);

    // printf("K: %d, N: %d\n", K, N);
    // Fill arrays with received data
    for (int i = 0; i < n_latPoints; i++) {
        *(latPoints + i) = PyFloat_AsDouble(PyList_GetItem(latListObj, i));
        *(lonPoints + i) = PyFloat_AsDouble(PyList_GetItem(lonListObj, i));
    }

    // Allocate enough space for clusters
    clusters = (struct cluster *) malloc(sizeof(struct cluster) * K);
    // Run K-means algorithm
    if (k_means(latPoints, lonPoints, N, K, clusters) != 0) {
        PyErr_SetString(PyExc_SystemError, "K-means algorithm failed.");
        return NULL;
    }

    /* Get results from K-means ready for returning to Python as Python data types
     * In Python returned data structure will be a list of dictionaries, e.g.:
     *
     * [
     *   {"num_points": X
     *    "center": (lat, lon)},
     *   {...},
     * ]
     *
     */
    // New output list
    PyObject *pList = PyList_New(K); // New reference to Python list type
    assert(PyList_Check(pList));     // Check that operation was successful
    // Build the output data structure
    for (int i = 0; i < K; i++) {
        // printf("#%d:\n    N:%d\n    (%f, %f)\n", i, clusters[i].num_points, clusters[i].center.lat, clusters[i].center.lon);
        // New dictionary
        PyObject *pDict = PyDict_New(); // New reference to Python dictionary type
        assert(PyDict_Check(pDict));    // Check that operation was successful
        // Add new key: value pairs
        PyDict_SetItemString(pDict, "num_points", Py_BuildValue("i", clusters[i].num_points));
        PyDict_SetItemString(pDict, "center", Py_BuildValue("(f,f)", clusters[i].center.lat, clusters[i].center.lon));
        // Add just created dictionary to output list
        PyList_SetItem(pList, i, pDict);

        // Free space previously allocated for points belonging to clusters
        free(clusters[i].cluster_points);
    }
    // Free space previously allocated
    free(clusters);
    free(latPoints);
    free(lonPoints);
    return pList;
}

static PyMethodDef KmeansMethods[] = {
        // {"name of the function as seen from Python", C function to call, ARGUMENTS TO FUNCTION, "Python docstring"}
        {"k_means", call_k_means, METH_VARARGS, "Calculate cluster based on K-means algorithm."},
        {NULL, NULL, 0, NULL}
};

//             init"filename"
PyMODINIT_FUNC initckmeans(void)
{
    //                   "filename"
    (void) Py_InitModule("ckmeans", KmeansMethods);
}