This repo contains sample code showing how to pass image data from Python to C++. It includes a shared library that simply prints some information about the image.

* make test - process the a image with a shared library using C++
* make python_ctypes - run a Python script that passes jpeg data to C++ using ctypes
* make cli - build a command line tool that reads a jpeg file and passes it to the library
* make fifo_create - create a named pipe for passing data from Python to C++
* make fifo - build and run a C++ program that reads jpeg data from a fifo and passes it to the library
* make python_fifo - run a Python script that writes jpeg data to a named pipe
* make python_cli - run a Python script that invokes the command line tool
