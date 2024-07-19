#!/bin/bash
set -e

NUM_JOBS=$(nproc)
ROOT_DIR=$(dirname "$(realpath $0)")
BUILD_DIR=${ROOT_DIR}/build/
EXTERN_DIR=${ROOT_DIR}/extern
TOOLS_DIR=${ROOT_DIR}/tools
ADPART_BIN=${BUILD_DIR}/AdpartSim

source ${ROOT_DIR}/.env

cd ${ROOT_DIR}

function compile {
    mkdir -p ${BUILD_DIR}
    cd ${BUILD_DIR}
    cmake ..
    make -j${NUM_JOBS}
}

function clean {
    cd ${ROOT_DIR}
    rm -rf ${BUILD_DIR}
    mkdir -p ${BUILD_DIR}
    cd ${BUILD_DIR}
}

function verify {
    cd ${ROOT_DIR}
    echo "Start verifying the compilation results"
    echo "------------------------------------------------------"
    export LOG_PATH=${LOG_PATH}
    export LOG_FILE=${LOG_FILE}
    export LOG_LEVEL=${LOG_LEVEL}
    ${ADPART_BIN} --input=${ROOT_DIR}/example/chakra/8npus_fullconnected.json
    python3 ${ROOT_DIR}/script/draw_result.py ${ROOT_DIR}/result
}

if [ $# -eq 0 ]; then
    set -- "-h"
fi

source ${ROOT_DIR}/script/cmake_check.sh ${EXTERN_DIR} ${TOOLS_DIR}
bash ${ROOT_DIR}/script/setup.sh -a

for ARG in "$@"; do
    case ${ARG} in
    -h|--help)
        echo "use -h|--help     to get help info"
        echo "use -c|--compile  to compile project"
        echo "use -l|--clean    to clean build product"
        echo "use -v|--verify   to run test case"
        echo "use -a|--all      to compile and run test case"
        exit;;
    -c|--compile)
        clean
        compile;;
    -l|--clean)
        clean;;
    -v|--verify)
        verify;;
    -a|--all)
        clean
        compile
        verify;;
    esac
done
echo "------------------------------------------------------"
