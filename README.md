# tools
This project contains all functions I use in general.

## Usage
### Dependencies
#### Compiler
You need to use a C++17 compiler.

#### Poco
The following packages need to be installed:
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

#### Libraries that need to be linked (option -l)
* PocoFoundation
* PocoNetSSL
* PocoNet
