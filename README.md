# Language_Identifier : Getting Started

A C library that can determine the language of text

This library was my solution to a data clustering contest [Telegram Data Clustering Contest 2021 ](https://contest.com/docs/dc2021-r1) - check it out.

## Running Locally

The library was tested on servers running Debian GNU/Linux 10 (buster), x86-64 with 8 cores and 16 GB RAM and will work correctly on any clean system.
Use the following commands to build the library:

```sh
$ mkdir build
$ cd build
$ cmake -DCMAKE_BUILD_TYPE=Release ..
$ cmake --build .
```

You can test the resulting library file libtgcat.so on the [test](https://contest.com/docs/dc2021-r1#source-data) data using the test script [libtgcat-tester.tar.gz](https://data-static.usercontent.dev/libtgcat-tester.tar.gz). To do this, copy libtgcat.so into the directory containing the test script, then build with cmake in the standard way:

```sh
$ mkdir build
$ cd build
$ cmake -DCMAKE_BUILD_TYPE=Release ..
$ cmake --build .
```

To test the library output, launch the resulting binary file tgcat-tester with the following parameters:

```sh
$ tgcat-tester language <input_file> <output_file>
```
where: 
<input_file> – path to file containing input data,
<output_file> – path to file containing output data.

Output data is presented as a text file where each line represents processed channel data in JSON format:
```sh
 {
   "lang_code": "en"
 }
```

