#!/bin/bash
set -e

EXTERN_DIR=$1
TOOLS_DIR=$2
NUM_JOBS=$(nproc)

CMAKE_PATH="${TOOLS_DIR}/cmake/bin/cmake"
if [[ -f ${CMAKE_PATH} ]]; then
    CMAKE_PATH=$(readlink -f "${TOOLS_DIR}/cmake/bin/cmake")
fi

if [[ "${BASH_SOURCE[0]}" == "${0}" ]]; then
    echo "This script cannot be called directly from the console."
    exit 1
fi

function install_cmake {
    if [[ ! -f ${CMAKE_PATH} ]]; then
        echo "The cmake file does not exist or the version is lower. "
        read -p "Do you want to install the specified version of the cmake tool? (y/n): " INPUT
        if [[ "$INPUT" == "y" ]] || [[ "$INPUT" == "Y" ]]; then
            mkdir -p ${EXTERN_DIR}
            cd ${EXTERN_DIR}
            if [ ! -d cmake ]; then
                git clone https://github.com/Kitware/CMake.git cmake
            fi
            cd cmake && git checkout v3.29.6
            ./bootstrap --prefix=${TOOLS_DIR}/cmake
            make -j ${NUM_JOBS} && make install
        fi
    else
        echo "---------------------------------------------------------------"
        echo '[WARNING]: The cmake tools find in '${CMAKE_PATH}
        echo 'Please run "export PATH='${CMAKE_PATH}':$PATH" to add it to PATH.'
        echo 'The operation will continue after 3 seconds...'
        echo "---------------------------------------------------------------"
        sleep 3
    fi
    export PATH="${TOOLS_DIR}/cmake/bin/:$PATH"
}

# Check if the cmake tool exists
if which cmake > /dev/null 2>&1; then
    CMAKE_PATH=$(which cmake)
    echo "cmake is available at ${CMAKE_PATH}"
else
    install_cmake
fi

# check the cmake tool version
CMAKE_VERISON=$(cmake --version | head -n 1 | awk '{print $NF}')
if [[ "$(echo "$CMAKE_VERISON" | grep -E '^[0-9]+\.[0-9]+')" < "3.22" ]]; then
    echo "cmake tools version less than 3.22"
    install_cmake
fi
