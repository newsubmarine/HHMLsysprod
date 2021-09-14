# HHMLSysProd

HHMLSys framework for producing slimmed systematic ntuples

| Author | Contact| 
|:-------:  | :--------:|
|Babar Ali|babar.ali@cern.ch |

### Table of contents

* [Setup](#setup)
* [Running the code](#running)

# Setup <a name="setup"></a>

Cloning the repository
----------------------

Login to lxplus and start with a new directory.

```bash
mkdir YourFancyDir
cd YourFancyDir
mkdir build run
git clone ssh://git@gitlab.cern.ch:7999/atlas-physics/HDBS/DiHiggs/multilepton/hhmlsysprod.git
```

Building the code using CMake
----------------------
```bash
cd build
cmake ../hhmlsysprod
make
source x86_64-centos7-gcc8-opt/setup.sh
```

After the first time setup, each time you login to lxplus just navigate to HHMLSys directory and source the release script. 

```bash
cd hhmlsysprod/HHMLSys
source release_setup.sh
```

# Running the code <a name="running"></a>

Navigate to run directory inside your fancy working directory and run the command.

```bash
cd YourFancyDir/run
runHHMLSys --sp PATH/TO/INPUT/ROOT/FILE --conf $TestArea/x86_64-centos7-gcc8-opt/data/HHMLSys/data/config_MC.conf --out PATH/TO/SAVE/OUTPUT/FILE --mcRun mc16a (d or e)

PATH/TO/INPUT/ROOT/FILE: The complete path to input systematic ntuple. Usually the file downloaded from Grid.
PATH/TO/SAVE/OUTPUT/FILE: The complete path where you want to save the output root file.
mc16a (d or e): Select the mc campaign corresponds to the input root file. Either mc16a or mc16d or mc16e.
```
In case you want to run over few number of events. Use the option ```--me 1000 or any number```.

Here is the complete list of options
```bash
Usage: runHHMLSys <option(s)>
Options:
	--h  or --help   : help
	--sp             : path of the input root file 
	--me             : maximum number of events to be process
	--conf           : path of configuration file
	--out            : Output dir path
	--mcRun          : mc campaign e.g. mc16a etc
```
