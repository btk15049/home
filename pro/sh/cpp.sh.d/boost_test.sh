#!/bin/bash
#第一引数にyaml 第二引数にほしいパラメータ名
get_yaml_element() {
    cat ${1} | yq .${2} | sed 's/"//g'
}

SH_DIR=$(cd $(dirname $0); pwd)

#コンパイラ
GPP="g++"
if [ -e ${SH_DIR}/.builder.yaml ]; then
    GPP=`get_yaml_element ${SH_DIR}/.builder.yaml gpp`
fi
LIB="~/lib"
if [ -e ${SH_DIR}/.builder.yaml ]; then
    LIB=`get_yaml_element ${SH_DIR}/.builder.yaml header`
fi


#コンパイル
if [ -f a.out ]; then
    rm a.out
fi

ARGS="-I ${LIB} -Wall -Wextra -std=c++17"
if [ -e ${SH_DIR}/boost_test.sh.d/.build_args.yaml ]; then
    ARGS=`get_yaml_element ${SH_DIR}/boost_test.sh.d/.build_args.yaml args`
fi


echo ""
echo "build:"
echo "${GPP} ${1} ${ARGS}"
${GPP} ${1} ${ARGS}

#コンパイルの成功チェック
if [ ! -f a.out ]; then
    "a.out is not found."
    exit 1
fi

echo ""
echo "run:"

#run
./a.out
rm a.out