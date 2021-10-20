#!/bin/bash
set -e
PROJECT_FOLDER=$(dirname $(dirname $(readlink -f "$0")))

make -C $PROJECT_FOLDER/build

$PROJECT_FOLDER/build/test/benchmark
