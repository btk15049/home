#!/bin/bash
#第一引数にyaml 第二引数にほしいパラメータ名
get_yaml_element() {
    cat ${1} | yq .${2} | sed 's/"//g'
}

#コンパイラ
GPP="g++"
if [ -e sh/.builder.yaml ]; then
    GPP=`get_yaml_element sh/.builder.yaml gpp`
fi

#コンパイル
if [ -f a.out ]; then
    rm a.out
fi

ARGS="-Wall -Wextra -std=c++17 -DBTK -I /usr/local/Cellar/boost/1.69.0_2/include"

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