#!/bin/bash
#template更新
init_yaml() {
    cp sh/cpp.sh.d/runner_config.yaml ${1}
}

#第一引数にyaml 第二引数にほしいパラメータ名
get_yaml_element() {
    cat ${1} | yq -y .${2} | head -1
}

#パス取得
SUP=`dirname ${1}`
#hoge.cpp -> hoge
SUB=`basename ${1} .cpp`

#サンプル格納用ディレクトリ
DIR=${SUP}/${SUB}
#設定yaml
YML=${SUP}/.${SUB}.yaml
#コードからURL取得
URL=`head -n 1 $1 | cut -c3-`

echo "${YML}"
#yamlの存在チェック なければ作る
if [ ! -f ${YML} ]; then
    echo "create ${YML}"
    init_yaml ${YML}
fi

#サンプルDL
if [ `get_yaml_element ${YML} SampleDownload.dl` = "true" ]; then
    echo "dl:"
    echo "downloading samples into ${DIR} ..."
    #${DIR}がない or SampleDownload.forceがtrueならoj使ってDL
    if [ ! -d ${DIR} ]  || [ `get_yaml_element ${YML} SampleDownload.force` = "true" ]; then
        #URLチェック
        if [ "${URL}" = "" ]; then
            echo "    ERROR : URL is not found."
            exit 1
        fi
        #${DIR}の確保
        if [ ! -d ${DIR} ]; then
            mkdir ${DIR}
        else
            echo "    redownload."
        fi
        oj dl ${URL} -d ${DIR}
    else
        echo "    ${DIR} is exist. downloading has skipped."
    fi
fi

#コンパイルオプションをyamlから取得
ARGS=""
if [ `get_yaml_element ${YML} WarningOptions` = "true" ]; then
    ARGS="${ARGS} -Wall -Wextra"
fi
if [ `get_yaml_element ${YML} WithDebugMacro` = "true" ]; then
    ARGS="${ARGS} -DBTK"
fi
cppver=`get_yaml_element ${YML} CppVersion`
if [ ${cppver} != "null" ]; then
    ARGS="${ARGS} -std=${cppver}"
fi

if [ `get_yaml_element ${YML} Optimize` = "true" ]; then
    ARGS="${ARGS} -O3"
fi


#コンパイル
if [ -f a.out ]; then
    rm a.out
fi
echo ""
echo "build:"
echo "g++ ${1} ${ARGS}"
g++ ${1} ${ARGS}

#実行
if [ `get_yaml_element ${YML} Run.run` = "true" ]; then
    #コンパイルの成功チェック
    if [ ! -f a.out ]; then
        "a.out is not found."
        exit 1
    fi

    echo ""
    echo "run:"

    #実行
    if [ `get_yaml_element ${YML} Run.samples` = "true" ]; then
        oj test -d ${DIR}
    else
        ./a.out
    fi
    rm a.out
fi

#クリップボードにコピー
if [ `get_yaml_element ${YML} CopyToClipBoard` = "true" ]; then
    echo ""
    echo "copy:"
    python3 sh/cpp.sh.d/replace_ja.py ${1} | pbcopy
    echo "...done"
fi


