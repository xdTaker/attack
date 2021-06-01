#!/bin/bash

project_dir=$(cd "$(dirname "$0")"; pwd)
src_dir=${project_dir}/libs/base
build_dir=${project_dir}/build/base
target_dir=${project_dir}/target

mkdir -p ${target_dir} &&
mkdir -p ${build_dir} && cd ${build_dir} &&
cmake ${src_dir} &&
make -j && sudo make install