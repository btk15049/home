#!/bin/bash
#template更新
init_yaml() {
    cp sh/runner.sh.d/runner_config.yaml ${1}
}

#第一引数にyaml 第二引数にほしいパラメータ名
get_yaml_element() {
    cat ${1} | yq -y .${2} | head -1
}

#コンパイラ
GPP="g++"
if [ -e sh/.builder.yaml ]; then
    GPP=`get_yaml_element sh/.builder.yaml gpp`
fi

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
        oj dl "${URL}" -d ${DIR}
    else
        echo "    ${DIR} is exist. downloading has skipped."
    fi
fi


echo ""
echo "parse:"
if [ `get_yaml_element ${YML} HeaderExpand` = "true" ]; then
    python3 sh/resolve_includes.py ${1}
    clang-format ${1} > tmp
    cat tmp > ${1}
    cat ${YML} | yq -y '.HeaderExpand = false' > tmp
    mv tmp ${YML}
else
    echo "skipped."
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

#コンパイル
if [ -f a.out ]; then
    rm a.out
fi

echo ""
echo "build:"
echo "${GPP} ${1} ${ARGS}"
${GPP} ${1} ${ARGS}

#実行
if [ `get_yaml_element ${YML} Run.run` = "true" ]; then
    #コンパイルの成功チェック
    if [ ! -f a.out ]; then
        "a.out is not found."
        exit 1
    fi
    
    echo ""
    echo "run:"
    
    #run
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
    python3 sh/runner.sh.d/replace_ja.py ${1} | pbcopy
    echo "...done"
fi


