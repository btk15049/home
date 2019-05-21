#!/bin/bash
#第一引数にyaml 第二引数にほしいパラメータ名
get_yaml_element() {
    cat ${1} | yq .${2} | sed 's/"//g'
}

SH_DIR=$(cd $(dirname $0); pwd)

if [ -e ${SH_DIR}/boost_test.sh.d/.build_args.yaml ]; then
    ARGS=`get_yaml_element ${SH_DIR}/boost_test.sh.d/.build_args.yaml args`
fi
ARGS="${ARGS} -Wall -Wextra"


echo ""
echo "<build>"
${SH_DIR}/build.sh ${1} ${ARGS}

#コンパイルの成功チェック
if [ ! -f a.out ]; then
    echo "a.out is not found."
    exit 1
fi

echo ""
echo "<run>"

#run
./a.out
rm a.out