#!/bin/bash

project_dir=$(cd "$(dirname "$0")"; pwd)

cd ${project_dir}/libs/base/build &&
cmake .. && make -j &&

cd ${project_dir}/libs/pcap/build &&
cmake .. && make -j &&

cd ${project_dir}/build &&
cmake .. && make -j
