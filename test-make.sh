#!/bin/bash

project_dir=$(cd "$(dirname "$0")"; pwd)
src_dir=${project_dir}/example
build_dir=${project_dir}/build/example
target_dir=${project_dir}/target

sh cap-make.sh &&
mkdir -p ${build_dir} && cd ${build_dir} &&
cmake ${src_dir} -DBIN_STATIC=1 && make -j