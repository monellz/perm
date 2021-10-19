#!/bin/bash
PROJECT_FOLDER=$(dirname $(dirname $(readlink -f "$0")))

rm -rf $PROJECT_FOLDER/build
mkdir -p $PROJECT_FOLDER/build
cd $PROJECT_FOLDER/build

cmake ..
make -j4
