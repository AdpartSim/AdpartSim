# USER GUIDE

> [!NOTE]
>
> 1. GCC 10 or higher is recommended to use C++20 features
> 1. CMake 3.22  or higher are recommended

## DEPENDENCIES

- install apt dependencies

```bash
# May require root privileges
sudo apt update && sudo apt upgrade
sudo apt install -y nano git gcc g++ gdb make mpich cmake python3-pip libssl-dev
sudo apt install -y libboost-all-dev libboost-dev libboost-program-options-dev
sudo apt install -y libprotobuf-dev protobuf-compiler
```

- install pip dependencies

```bash
# Upgrade pip version
pip install --upgrade pip
# install pip pakckage
pip install -r requirements.txt
```

- Install third-party dependencies for the current project

```bash
# run setup script
bash ./script/setup.sh -a
# if cmake is not installed on the system or the cmake version is too low,
# you may be prompted to source the file and retry the script
source ~/.bashrc
bash ./script/setup.sh -a
```

## RUN ADPART-SIM

**You can build and test the project by running just one command**

**NOTE**

- Please make sure that the current system environment dependencies have been installed. For details, please refer to the next section

- The first execution may automatically download and install all dependencies, which may take a long time to execute, depending on your network and computer performance.

```bash
# Need Environment Config Ready
bash ./build.sh -a
# You can also use the following parameters to get other executable commands
bash ./build.sh -h
```

## MORE INFORMATION

also you can run these command on setup phase

```bash
# get setup script help info
bash script/setup.sh -h
# install all setup, if the tool already exists, skip it
bash script/setup.sh -a
# force install single tool
bash script/setup.sh --<tool_name>
```
