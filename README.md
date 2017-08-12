#### Simple 2D k-means Python2.7 module implemented in pure C

##### Resources used:
* [Using PyArg_ParseTuple with a list](http://code.activestate.com/lists/python-list/31841/)
* [Using Py_BuildValue() to create a list of tuples in C](https://stackoverflow.com/questions/36050713/using-py-buildvalue-to-create-a-list-of-tuples-in-c)
* [Using malloc for allocation of multi-dimensional arrays with different row lengths](https://stackoverflow.com/questions/1970698/using-malloc-for-allocation-of-multi-dimensional-arrays-with-different-row-lengt)
* [C: Correctly freeing memory of a multi-dimensional array](https://stackoverflow.com/questions/1733881/c-correctly-freeing-memory-of-a-multi-dimensional-array)
* [Python Programming/Extending with C](https://en.wikibooks.org/wiki/Python_Programming/Extending_with_C)
* [Writing Python/C extensions by hand](http://www.dalkescientific.com/writings/NBN/c_extensions.html)
* [DevDocs](http://devdocs.io/c/language/object)

#### How to compile to .pyd file on Windows (Windows10):
* Clone repo
* Install [MinGW](http://www.mingw.org/)
* Add MiGW to PATH
* Execute [make.cmd](src/py_module/make.cmd)