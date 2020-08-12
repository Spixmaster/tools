# tools-cpp
A C++ library which contains all functions I use in general.

## Installation
### Compiler
You need to use a C++17 compiler for compilation.

### Dependencies
This software is built with the help of third party libraries. It is shown below how to install them.

#### Poco
```sh
sudo pacman -S poco
```

#### Rapidjson
```sh
sudo pacman -S rapidjson
```

#### Boost
```sh
sudo pacman -S boost
```

#### Libraries that need to be linked (option -l)
* PocoFoundation
* PocoNet
* PocoNetSSL
* PocoCrypto
* boost_iostreams
* boost_filesystem
* boost_locale

### Submodule
```sh
cd to/your/project/
git submodule add *link-to-this-repo*
```

### Makefile
```sh
cd to/this/project/
cmake .
make -j 4
```

## Usage
This project is thought to be used in other software as a library.

### Documentation
The documentation is generated with the help of Doxygen. It is an HTML document and can be found in *./doc/html/index.html*. Open that file with your favourite browser.

## Changelog
The changelog can be seen on the documentation's main page.
