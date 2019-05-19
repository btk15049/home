#!/bin/bash

SH_DIR=$(cd $(dirname $0); pwd)

#template更新
init_yaml() {
    cp ${SH_DIR}/run_all.sh.d/run_all_config.yaml ${1}
}

#第一引数にyaml 第二引数にほしいパラメータ名
get_yaml_element() {
    cat ${1} | yq .${2} | sed 's/"//g'
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
HEAD=`head -n 1 < $1`
#先頭が//で始まらないならexit
PR=`echo ${HEAD} | cut -c-3`
URL=`echo ${HEAD} | cut -c4-`
if [ "${PR}" != "// " ]; then
    echo "ERROR: Header is invalid"
    exit 1
fi

#yamlの存在チェック なければ作る
if [ ! -f ${YML} ]; then
    echo "create ${YML}"
    init_yaml ${YML}
fi

#サンプルDL
if [ `get_yaml_element ${YML} SampleDownload.dl` = "true" ]; then
    echo "<dl>"
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
        oj dl "${URL}" -d ${DIR}
    else
        echo "    ${DIR} is exist. downloading has skipped."
    fi
fi

#コンパイルオプションをyamlから取得
ARGS="-I ${LIB}"
if [ `get_yaml_element ${YML} WarningOptions` = "true" ]; then
    ARGS="${ARGS} -Wall -Wextra"
fi
if [ `get_yaml_element ${YML} WithDebugMacro` = "true" ]; then
    ARGS="${ARGS} -DBTK"
fi
if [ `get_yaml_element ${YML} Optimize` = "true" ]; then
    ARGS="${ARGS} -O3"
fi

echo ""
echo "<build>"
#コンパイル
${SH_DIR}/build.sh ${1} ${ARGS}

#実行
if [ `get_yaml_element ${YML} Run` = "true" ]; then
    #コンパイルの成功チェック
    if [ ! -f a.out ]; then
        "a.out is not found."
        exit 1
    fi
    
    echo ""
    echo "<run>"
    
    #run
    oj test -d ${DIR}
    
    rm a.out
fi

#クリップボードにコピー
if [ `get_yaml_element ${YML} CopyToClipBoard` = "true" ]; then
    echo ""
    echo "<copy>"
    python3 ${SH_DIR}/run_all.sh.d/replace_ja.py ${1} | pbcopy
    echo "...done"
fi

#自動サブミット
if [ `get_yaml_element ${YML} AutoSubmit` = "true" ]; then
    echo ""
    echo "<submit>"
    ${SH_DIR}/run_all.sh.d/auto_submit.sh ${URL} ${1}
fi



