#!/bin/bash
#hoge.cpp -> hoge
SUB=`basename ${1} .cpp`
SU=`basename ${SUB} .test`
if [ "${SU}.test" == ${SUB} ]; then
    ./sh/boost_test.sh ${1}
else
    ./sh/runner.sh ${1}
fi