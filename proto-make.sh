#!/bin/bash

project_dir=$(cd "$(dirname "$0")"; pwd)
src_dir=${project_dir}/libs/proto
build_dir=${project_dir}/build/proto
target_dir=${project_dir}/target

sh base-make.sh &&
mkdir -p ${build_dir} && cd ${build_dir} &&
cmake ${src_dir} &&
make -j && sudo make install