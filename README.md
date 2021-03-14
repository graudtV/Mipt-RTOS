# Mipt-RTOS
## Library Overview
Mipt-RTOS library consists of two main parts: directly library, which defines [Mipt-RTOS interface](#Mipt-RTOS-interface), and [rtosconfig](#rtosconfig) utility,
which helps to use this interface. Follow the links to get more information about them

## Requirments
1. Boost library
2. Compiler with C++14 support to install lib
3. Cross-compiler for your target platform (Linux/AVR/etc) with C++17 support

## Installation
1. Download repository
```
git clone https://github.com/graudtV/Mipt-RTOS/
```
2. Move to directory with it
```
cd Mipt-RTOS
```
3. Run installation
```
make install
```
4. If everithing is OK, library sources and headers will be installed into system directories, and you will be able to run [rtosconfig](#rtosconfig) utility.
You can try running the following:
```
rtosconfig --version
```

## Mipt-RTOS interface
TBD

## rtosconfig
_rtosconfig_ utility helps to configure Mipt-RTOS library for your particular project. It generates some C++ headers and sources, which allow to use
project-specific resources like tasks and timers in safe and convenient manner.

### Configuration files
Before running rtosconfig, you need to create configuration file, which describes your target platform properties, tasks you want to run, list of used resouces, message queues,
timers and all other features, that are available in Mipt-RTOS

Configuration files are written in json format. The easiest way to understand their structure is to take a look at some examples in [examples](examples) directory.
They are named as config.json

### Running rtosconfig
Since you are ready with configuration file, run
```
rtosconfig config_file_name.json
```
in directory with your project. It will generate rtos.h and rtos.cpp, which define all the stuff you specified in config file.
Now just ```#include "rtos.h"``` in your project, and you are ready to use Mipt-RTOS!
