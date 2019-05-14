#!/bin/bash

#第一引数にyaml 第二引数にほしいパラメータ名
get_yaml_element() {
    cat ${1} | yq .${2} | sed 's/"//g'
}

SH_DIR=$(cd $(dirname $0); pwd)
LIB="~/lib"
if [ -e ${SH_DIR}/.build.sh.d/.build_config.yaml ]; then
    LIB=`get_yaml_element ${SH_DIR}/.build.sh.d/.build_config.yaml header`
fi
echo "<parse>"
python3 ${SH_DIR}/run_all.sh.d/resolve_includes.py ${1} ${LIB}
clang-format ${1} > tmp
mv tmp  ${1}
