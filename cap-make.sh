#!/bin/bash

project_dir=$(cd "$(dirname "$0")"; pwd)
src_dir=${project_dir}/libs/cap
build_dir=${project_dir}/build/cap
target_dir=${project_dir}/target

sh proto-make.sh &&
mkdir -p ${build_dir} && cd ${build_dir} &&
cmake ${src_dir} -DBIN_STATIC=0 &&
make -j && sudo make install