# tools
A C++ library which contains all functions I use in general.

## Installation
### As a submodule
```sh
cd to/your/project
git submodule add *link to this repo*
```

### As a contributor
The project needs to be set up properly in your IDE to be able to compile it.

#### Example eclipse
These instructions show how to set up the project right in eclipse.
1. Clone the project to anywhere.
2. Create a new eclipse project.
3. Right click on the project > "Import" > "General" > "File System".
4. Select all content from the cloned project.

### Compiler
You need to use a C++20 compiler for compilation.

### Dependencies
This software is built with the help of third party libraries. It is shown below how to install them.

#### Poco
```sh
sudo apt install libpoco-dev
```

#### rapidjson
```sh
sudo apt install rapidjson-dev
```

#### boost
```sh
sudo apt install libboost-all-dev
```

#### Libraries that need to be linked (option -l)
* PocoFoundation
* PocoNetSSL
* PocoNet
* PocoCrypto
* boost_iostreams
* boost_filesystem

## Usage
The source code cannot be compiled by itself as there is no main function included. It is thought to be used in other software as a library.

### Documentation
The documentation was generated with the help of Doxygen. It is an HTML document and can be found in *./doc/html/index.html*. Open that file with your favourite browser.

## Changelog
It can be seen on the documentation's mainpage.
