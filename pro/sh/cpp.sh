#!/bin/bash
#hoge.cpp -> hoge
SUB=`basename ${1} .cpp`
SU=`basename ${SUB} .test`
SH_DIR=$(cd $(dirname $0); pwd)
if [ "${SU}.test" == ${SUB} ]; then
    ${SH_DIR}/cpp.sh.d/boost_test.sh ${1}
else
    ${SH_DIR}/cpp.sh.d/runner.sh ${1}
fi