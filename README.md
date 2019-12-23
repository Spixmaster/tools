# tools
A C++ library. This project contains all functions I use personally in general.

## Usage
You can only use this project in your own ones. Thus, no main is included.

### As a submodule
```sh
cd to/your/project
git submodule add *link to this repo*
```

### As a contributor
#### eclipse
* clone the project to anywhere
* create a new eclipse project
* right click on the project > Import > General > File System
* select all content from the cloned project

### Compiler
You need to use a C++17 compiler.

### Dependencies
The following packages need to be installed:

#### Poco
```sh
sudo apt install libpoco-dev
```

#### rapidjson
Moreover, [rapdijson](https://github.com/Tencent/rapidjson) needs to be installed.

For this, do the following steps:
```sh
git clone https://github.com/Tencent/rapidjson
cd rapidjson
cmake .
make -j4
sudo make install
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
