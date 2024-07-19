#!/bin/bash
set -e

SCRIPT_DIR=$(dirname "$(realpath $0)")
EXTERN_DIR=${SCRIPT_DIR}/../extern
TOOLS_DIR=${SCRIPT_DIR}/../tools
NUM_JOBS=$(nproc)

source ${SCRIPT_DIR}/cmake_check.sh ${EXTERN_DIR} ${TOOLS_DIR}

if [ "$(id -u)" -eq 0 ]; then
    echo "Please do not run the script as root or with sudo privileges"
    exit 1
fi

function download {
    local URL=$1
    local NAME=$2
    local VERSION=$3

    mkdir -p ${EXTERN_DIR}
    cd ${EXTERN_DIR}
    if [ ! -d ${NAME} ]; then
        git clone ${URL} ${NAME:-}
    fi
    cd ${NAME} && git checkout ${VERSION}
    PREFIX_RET=${TOOLS_DIR}/${NAME}
}

function install_glog {
    FORCE=${1:-}
    download "https://github.com/AdpartSim/glog.git" "glog" "v0.7.1"
    if [ -n "$FORCE" ] || [ ! -d ${PREFIX_RET} ]; then
        cmake --install-prefix=${PREFIX_RET} .
        make -j ${NUM_JOBS} && make install
    fi
}

function install_json {
    FORCE=${1:-}
    download "https://github.com/AdpartSim/json.git" "json" "v3.11.3"
    if [ -n "$FORCE" ] || [ ! -d ${PREFIX_RET} ]; then
        cmake --install-prefix=${PREFIX_RET} .
        make -j ${NUM_JOBS} && make install
    fi
}

function install_chakra {
    FORCE=${1:-}
    download "https://github.com/AdpartSim/chakra.git" "chakra" "adpart_sim"
    if [ -n "$FORCE" ] || [ -z "$(pip list | awk '{print $1}' | grep -w chakra)" ]; then
        # pip install chakra
        pip install .
    fi
    if [ -n "$FORCE" ] || [ ! -d ${PREFIX_RET} ]; then
        # copy chakra protoc files to tools directory
        mkdir -p ${PREFIX_RET}
        cp -r schema ${PREFIX_RET}
        cp -r src/feeder ${PREFIX_RET}
        cp -r src/third_party ${PREFIX_RET}
        protoc et_def.proto \
            --proto_path=${PREFIX_RET}/schema/protobuf \
            --cpp_out=${PREFIX_RET}/schema/protobuf
    fi
}

function install_ns3 {
    FORCE=${1:-}
    download "https://github.com/AdpartSim/ns-3-dev-git.git" "ns3" "ns-3.42"
    if [ -n "$FORCE" ] || [ ! -d ${PREFIX_RET} ]; then
        # --build-profile=optimized / debug
        ./ns3 configure --prefix=${PREFIX_RET} \
            --build-profile=debug \
            --enable-mpi \
            --enable-tests \
            --enable-examples
        ./ns3 build -j ${NUM_JOBS}
        ./ns3 install
    fi
}

if [ $# -eq 0 ]; then
    set -- "-h"
fi

for ARG in "$@"; do
    case ${ARG} in
    -h|--help)
        echo "use -h|--help     to get help info"
        echo "use -a|--all      to install all missing tools"
        echo "use --<tool_name> to force installation of specified tools";;
    --glog)
        install_glog "FORCE";;
    --json)
        install_json "FORCE";;
    --chakra)
        install_chakra "FORCE";;
    --ns3)
        install_ns3 "FORCE";;
    -a|--all|*)
        install_glog
        install_json
        install_chakra
        install_ns3;;
    esac
done
