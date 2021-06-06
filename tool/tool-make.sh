#!/bin/bash

tool_dir=$(cd "$(dirname "$0")"; pwd)
build_dir=${tool_dir}/build
# target_dir=${tool_dir}/target

mkdir -p ${build_dir} &&
# mkdir -p ${target_dir} &&

if [ -e /usr/local/bin/cppcheck ]; then
    echo "cppcheck already exist"
else
    echo "install cppcheck..."
    cd ${build_dir} &&
    tar -xf ../cppcheck-2.4.1.tar.gz && cd cppcheck-2.4.1 && (
        make -j4  && sudo mv cppcheck /usr/local/bin -f 
        cd .. && rm -rf cppcheck-2.4.1
    )
fi
