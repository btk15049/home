#!/bin/bash

#第一引数にyaml 第二引数にほしいパラメータ名
get_yaml_element() {
    cat ${1} | yq .${2} | sed 's/"//g'
}

SH_DIR=$(cd $(dirname $0); pwd)

#コンパイラ
GPP="g++"
LIB="~/lib"
ARGS=${@:3:($#-2)}
if [ -e ${SH_DIR}/build.sh.d/.build_config.yaml ]; then
    GPP=`get_yaml_element ${SH_DIR}/build.sh.d/.build_config.yaml gpp`
    LIB=`get_yaml_element ${SH_DIR}/build.sh.d/.build_config.yaml header`
fi

#コンパイル
if [ -f a.out ]; then
    rm a.out
fi

echo "${GPP} ${1} -I ${LIB} ${ARGS} -std=c++17"
${GPP} ${1} -I ${LIB} ${ARGS}

