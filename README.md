# justask-qt-client
justask-qt-client is a Qt4 client for [justask](https://github.com/nilsding/justask) installations.

As of now, it only shows you some information about your installation. (that's what the API is for, right?)

## Building from source
To build justask-qt-client, you need...

 * CMake 2.6
 * Qt 4
 * [QJSON](http://qjson.sourceforge.net)

If you have these dependencies already installed on your computer, go ahead and compile.

```
$ mkdir build && cd build && cmake .. && make -j2
```
