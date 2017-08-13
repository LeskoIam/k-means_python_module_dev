### Simple 2D k-means Python 2.7 module implemented in pure C

This is an example on how to create and build an extension module for Python in pure C. Example is not the most trivial one so
I hope it explains a little bit more then then just how to pass a single variable and print it out from C.

#### Backstory
For fun and games I'm gathering geolocation data for taxis in one of Europe capital cities. In a year or so I am already
at 68 million rows of raw data which boil down to  1.8 million distinct events. Every one of this events has latitude and 
longitude information (and some other info) attached.

I wanted to do some clustering of the data. Looking at different algorithms I decided for 
[K-means](https://en.wikipedia.org/wiki/K-means_clustering). It's one of the simplest to implement and easy to understand.

First I tried with Python. Found a pure Python implementation of K-means algorithm ([Insert link to orikinal author here]())
on the web. I soon found out it gets really slow really fast when amount of data supplied to it increase 
(70 seconds for 13000 points in 50 clusters). Enter C with promise of speedups.

I found C implementations of K-means but could not make heads and tails from it. Decision was made implement it myself.
I have prior experience with C, but very limited, so it was a great learning experience specially in the end when I 
needed t wrap everything for calling from and returning to Python.

#### Resources used:
* [Custom Python Part 1: Extensions](https://www.codeproject.com/Articles/3227/Custom-Python-Part-Extensions)
* [Python C Extensions](https://www.thecodingforums.com/threads/python-c-extensions.744128/)
* [The Py_BuildValue() Function](https://docs.python.org/2.0/ext/buildValue.html)
* [Parsing arguments and building values](https://docs.python.org/2/c-api/arg.html)
* [Dictionary Objects](https://docs.python.org/2/c-api/dict.html#c.PyList_Append)
* [Using PyArg_ParseTuple with a list](http://code.activestate.com/lists/python-list/31841/)
* [Using Py_BuildValue() to create a list of tuples in C](https://stackoverflow.com/questions/36050713/using-py-buildvalue-to-create-a-list-of-tuples-in-c)
* [Using malloc for allocation of multi-dimensional arrays with different row lengths](https://stackoverflow.com/questions/1970698/using-malloc-for-allocation-of-multi-dimensional-arrays-with-different-row-lengt)
* [C: Correctly freeing memory of a multi-dimensional array](https://stackoverflow.com/questions/1733881/c-correctly-freeing-memory-of-a-multi-dimensional-array)
* [Python Programming/Extending with C](https://en.wikibooks.org/wiki/Python_Programming/Extending_with_C)
* [Writing Python/C extensions by hand](http://www.dalkescientific.com/writings/NBN/c_extensions.html)
* [DevDocs](http://devdocs.io/c/language/object)

### How to compile to .pyd file on Windows (Windows10):
* Clone repo
* Install [MinGW](http://www.mingw.org/)
* Add MinGW to PATH
* Execute [make.cmd](src/py_module/make.cmd)