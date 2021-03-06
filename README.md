# Simple 2D K-means Python module implemented in pure C
##### Current version: [1.0.1](https://github.com/LeskoIam/k-means_python_module_dev/releases/latest)

## Intro
### What this is
It's an example on how to create and build extension module for Python 2.7 in pure C. It demonstrates how to parse
input and transform it to C data types then reversing the process for returning back to Python. Example is not the most
trivial one so I hope it explains a little bit more then just how to pass a single variable and print it out from C.

### What this is NOT
This is not meant to be a tutorial and is not written as such. It also does not talk about K-means algorithm but uses it
as an example.

## Backstory
For fun and games I'm gathering geolocation data for taxis in one of Europe's capital cities. In a year or so I am already
at 68 million rows of raw data which boils down to 1.8 million distinct events. Every one of this events has latitude and 
longitude information (and some other info) attached.

I wanted to do some clustering of the data to see where taxis pick up customers most of the time. Looking at different
algorithms I decided for [K-means](https://en.wikipedia.org/wiki/K-means_clustering). It's one of the simplest and easiest
to understand.

First I tried with Python. I found a pure Python implementation of K-means algorithm 
([original here](http://pandoricweb.tumblr.com/post/8646701677/python-implementation-of-the-k-means-clustering))
on the web. But it soon became obvious that it gets really slow really fast when amount of data supplied to it increases 
(70 seconds for 13000 points in 50 clusters). Enter C with promises of speedups.

I found C implementations of K-means but could not make heads or tails of it. Decision was made to implement it myself.
I do have some prior experience with C but haven't done anything with it for some time, so it was a great re-learning
experience especially in the end when I needed to wrap everything for calling from and returning to Python.

## C source code
Everything dealing with Python is in [ckmeans.c](src/py_module/ckmeans.c). All the code is commented and explained 
in the file.

Code related to K-means algorithm is in [lib](src/lib) folder. Split between [k_means.c](src/lib/k_means.c) and [utils.c](src/lib/utils.c).

### Top level look at workings of the module
C module receives two lists and an integer from Python ```.k_means([lat1, lat2, ...], [lon1, lon2, ...], K)``` and it returns 
list of dictionaries ```[{"center": (lat, lon), "num_points": N}]```.

## How to compile to .pyd file on Windows (Windows10):
1. Clone repo
2. Install [MinGW](http://www.mingw.org/)
3. Add MinGW to PATH
4. Execute [make.bat](src/py_module/make.bat) to compile. 
    * Run ```make.bat``` for 'production' compiling
    * Use ```-D``` flag to compile with debugging enabled (```make.bat -D```)
    
    If compiling is successful you will find ckmeans.pyd file in ```build\ ``` directory. pyd is like .dll file but you can
    import it as any other python file.
5. import into Python and use
```python
import ckmeans
import random
import time

N = 10000
K = 50

lat = [random.randint(1000, 2000)/100. for _ in xrange(N)]
lon = [random.randint(4000, 5000)/100. for _ in xrange(N)]

s_time = time.time()
ans = ckmeans.k_means(lat, lon, K)

print "Time to cluster {0} points in to {1} clusters was: {2} seconds".format(N, K, (time.time() - s_time))

```

## Resources used
* General C resources
    * [DevDocs](http://devdocs.io/c/language/object) - General C documentation
    * [Using malloc for allocation of multi-dimensional arrays with different row lengths](https://stackoverflow.com/questions/1970698/using-malloc-for-allocation-of-multi-dimensional-arrays-with-different-row-lengt) - 
      StackOverflow question with great answer
    * [C: Correctly freeing memory of a multi-dimensional array](https://stackoverflow.com/questions/1733881/c-correctly-freeing-memory-of-a-multi-dimensional-array) - 
      StackOverflow question with great answer
    * [#ifdef DEBUG print statements in C](http://ilostmynotes.blogspot.si/2011/04/ifdef-debug-print-statements-in-c.html)
    * Programming in C (fourth edition) by Stephen G. Kochan (ISBN: 978-0-321-77641-9)
* Python extensions resources
    * [Custom Python Part 1: Extensions](https://www.codeproject.com/Articles/3227/Custom-Python-Part-Extensions) - 
      great examples on how to dynamically build Python objects
    * [Python C Extensions](https://www.thecodingforums.com/threads/python-c-extensions.744128/) - forum question with good
      answer on how to dereference used Python objects
    * [The Py_BuildValue() Function](https://docs.python.org/2.0/ext/buildValue.html) - general documentation on ```Py_BuildValue()```
    * [Parsing arguments and building values](https://docs.python.org/2/c-api/arg.html) - general documentation on ```Py_BuildValue()```
    * [Dictionary Objects](https://docs.python.org/2/c-api/dict.html#c.PyList_Append) - dictionary object documentation
    * [Using PyArg_ParseTuple with a list](http://code.activestate.com/lists/python-list/31841/) - example on how to pass
      more then a string from Python to C
    * [Using Py_BuildValue() to create a list of tuples in C](https://stackoverflow.com/questions/36050713/using-py-buildvalue-to-create-a-list-of-tuples-in-c) - 
      StackOverflow question with great answer and links
    * [Python Programming/Extending with C](https://en.wikibooks.org/wiki/Python_Programming/Extending_with_C) - basic example
      of C extension
    * [Writing Python/C extensions by hand](http://www.dalkescientific.com/writings/NBN/c_extensions.html) - another a bit advanced 
      example of C extension 
    * Beginning Python by Peter Norton, Alex Samuel, David Aitel, ... (ISBN: 0-7645-9654-3) 

## TODO
* write ```setup.py```
* return points belonging to clusters
* clean up k_means and utils files
* some .h file refactoring, probably
* decide if cuttoff distance for K-means should be supplied by user?

## Technical details
* Windows10 64 Professional
* Python 2.7.13
* gcc (MinGW.org GCC-6.3.0-1) 6.3.0
* CLion 2017.2 as an editor
