#!/bin/bash

BASE=$HOME/work/tensorflow/tflite-micro
OUT=$PWD/tfl

pushd $BASE
python3 ./tensorflow/lite/micro/tools/project_generation/create_tflm_tree.py $OUT
cp ./tensorflow/lite/micro/tools/project_generation/Makefile $OUT
bash $BASE/tensorflow/lite/micro/tools/make/ext_libs/cmsis_download.sh $OUT/third_party
bash $BASE/tensorflow/lite/micro/tools/make/ext_libs/cmsis_nn_download.sh $OUT/third_party
popd
