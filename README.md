# CBT Requirements Calculator

Given a Conditional Behavior Tree (CBT) this program is able to check its executability.

References:

* __Conditional Behavior Trees: Definition, Executability, and Applications__.
Eleonora Giunchiglia, Michele Colledanchise, Lorenzo Natale and Armando Tacchella [PDF](https://lornat75.github.io/papers/2019/giunchiglia-smc.pdf)
* __Computing the Initial Requirements in Conditioned Behavior Trees__.
Eleonora Giunchiglia [PDF](http://emas2018.dibris.unige.it/images/papers/EMAS18-08.pdf)

## TO DO

- Fix tests because now they are failing

## Installation

### Requirements 

##### Compile

You will need the gcc compiler (with c++11 support) installed on your computer. 
In order to check if you have gcc installed on your machine you can issue the command:

`gcc --version`

If the message  *command not found* appears that it means that gcc is not installed on your machine.  

##### External Program 

In order to check the satisfiability of the propositional logic encoding, the external program *limboole* is needed. Follow next steps to download and compile it:

1. *limboole* requires *PicoSAT* as backend. If you do not have it on yuor machine, follow the steps below:

     * dowload the file `"picosat-965.tar.gz"` that you can find at the link http://fmv.jku.at/picosat
     * decompress the downloaded file
     * rename the folder `"picosat-965"` to `"picosat"`
     * in the picosat folder execute `./configure.sh && make`.

2. Once you have *PicoSAT*, it is time to compile *limboole*:

     * go to the link http://fmv.jku.at/limboole
     * dowload the file `"limboole1.1.tar.gz"`
     * decompress the dowloaded file in the **same folder** in which the picosat folder is placed 
     * in the decompressed folder (limboole1.1) execute the command `./configure.sh && make`.

## Compile

CMake use is to build the application.

## Testing

For the testing phase the framework catch2 (https://github.com/catchorg/Catch2) was deployed.

## How to use it

Call cbt_checker build in "/bin" with the following parameters:

- configuration file: a file where "limboole path" is stored
- tree: a xml file representing the tree
- initial state: a txt file with input requirements
- output directory: directory where output files are stores

First three parameters are inputs while last one is where the program generates the follwoing files:
- `bt_plans.txt`: in this file the propositional logic representation of the CBT is written.
- `general_requirements.txt`: the first line of this file declares if the representation contained in `bt_plans.txt` is satisfiable.If that is the case it also shows a model of such representation.
- `cbt_valid.txt`: writes as YES/NO the result of validating the CBT.
