#!/bin/bash
red=31
green=32
yellow=33
blue=36
on_console=0
use_file=1
use_directory=2
use_clipboard=3
on=0
off=1

#色付きecho
function cecho {
    local color="${1}"
    local msg="${@:2}"
    printf "\033[${color}m${msg}\033[m\n"
}

#引数が指すファイルが存在しないなら警告してtrueを返すだけ
function file_none {
    local file_name="${1}"
    if [ ! -f $file_name ];then
        cecho $red "${file_name} is not found."
        return 0
    fi
    return 1
}

#引数のファイルが空なら警告してtrueを返すだけ
function file_empty {
    local file_name="${1}"
    if [ ! -s $file_name ];then
        cecho $red "${file_name} is empty."
        return 0
    fi
    return 1
}

function file_set {
    if [ $# -eq 0 ]; then
        usage
        return 1
    fi
    touch .cww
    rm .cww
    local files=("$@")
    local files_num=`expr $#`
    for ((i=0;i<$files_num;i++))
    do
        files[i]=`echo ${files[i]} | cut -d"." -f1`
        echo ${files[i]} >>.cww
        file_none ${files[i]}.cpp && cp ~/home/template.cpp ${files[i]}.cpp && cecho $blue "create ${files[i]}.cpp"
    done
    return 0
}

function build {
    file_none .cww && cecho $red "use set subcommand." && return 1
    file_empty .cww && cecho $red "use set subcommand." && return 1
    IFS=$'\n'
    local files=(`cat .cww`)
    IFS=$' '
    local files_num=${#files[@]}
    name=${files[0]}
    for ((i=0;i<$files_num;i++))
    do
        files[i]="${files[i]}.cpp"
    done
    touch log
    cecho $blue "g++ -O3 -std=c++11 ${files[@]} -o $name 2>log"
    g++ -O3 -std=c++11 ${files[@]} -o $name.out -DBTK 2>log
    local ret=$?
    head -7 log
    if [ -e $name.out ]; then
        mv $name.out $name
    fi
    return $ret
}

function file_open {
    file_none .cww && cecho $red "use set subcommand." && return 1
    file_empty .cww && cecho $red "use set subcommand." && return 1
    
    IFS=$'\n'
    local files=(`cat .cww`)
    IFS=$' '
    local files_num=${#files[@]}
    for ((i=0;i<$files_num;i++))
    do
        file_none ${files[i]}.cpp || emacs ${files[i]}.cpp
    done
    return 0
}


function run_test {
    #例外処理
    file_none .cww && cecho $red "use set subcommand." && return 1
    file_empty .cww && cecho $red "use set subcommand." && return 1

    #実行ファイルの取得 $nameが実行ファイル
    IFS=$'\n'
    local files=(`cat .cww`)
    IFS=$' '
    local name=${files[0]}
    file_none $name && cecho $red "use set or build subcommand." && return 1

    #operandの取得
    local op=("$@")
    local op_num=`expr $#`

    #各フラグ及びファイルポインタ
    local vis=$off
    local input=$on_console
    local input_pointer=.input
    local output=$on_console
    local output_pointer=.output

    #operandを全探索してフラグ更新
    for ((i=0,j=1;i<$op_num;i++,j++))
    do
        case "${op[i]}" in
            "-v")
                vis=$on
	        ;;
            "-c")
                input=$use_clipboard
	        ;;
            "-fi")
                if [ $j -lt $op_num ];then
                    input=$use_file
                    input_pointer=${op[j]}
                else
                    return 1
                fi
	        ;;
            "-fo")
                if [ $j -lt $op_num ];then
                    output=$use_file
                    output_pointer=${op[j]}
                else
                    return 1
                fi
	        ;;
            "-di")
                if [ $j -lt $op_num ];then
                    input=$use_directory
                    input_pointer=${op[j]}
                else
                    return 1
                fi
	        ;;
            "-do")
                if [ $j -lt $op_num ];then
                    output=$use_directory
                    output_pointer=${op[j]}
                else
                    return 1
                fi
	        ;;            
            *)
                ;;
        esac
    done

    #/を外す処理 %hogeで後方のhogeを取り除けるらしい(テスト済み)
    input_pointer=${input_pointer%/}
    output_pointer=${output_pointer%/}

    #ディレクトリ入出力
    if [ $input -eq $use_directory ] || [ $output -eq $use_directory ] ;then
        #ここから例外処理
        if [ $input -ne $output ];then
            cecho $red "-d option is incorrect."
            return 1
        fi
        if [ ! -d $input_pointer ];then
            cecho $red "$input_pointer is not a directory."
            return 1
        fi
        if [ ! -d $output_pointer ];then
            cecho $red "$output_pointer is not a directory."
            return 1
        fi
        #ここまで例外処理

        #入力ディレクトリ下をfindで列挙，探索 IFSは区切りで死なないための対処
        IFS=$'\n'
        for tourist in `find ${input_pointer} -maxdepth 1 -type f`;
        do
            IFS=$' '
            #chokudaiは純粋なfilename
            chokudai=`basename ${tourist}`
            latte="${input_pointer}/${chokudai}"
            malta="${output_pointer}/${chokudai}"

            #実行
            cecho $blue "run ${name} <${latte} >${malta}"
            #入力を表示するときはコメントアウトを外す
            #[ $vis -eq $on ] && cecho $green `cat ${latte} | sed -e ':loop;N;$!b loop;s/\\n/\\\\n/g' `
            $name <${latte} >${malta}
            [ $vis -eq $on ] && cat ${malta} 
            IFS=$'\n'
        done
    fi
    
    #地獄のような場合分けをします まあでも出力はコンソールかファイルかの2択

    #入力=手打ち
    if [ $input -eq $on_console ] && [ $output -eq $on_console ];then
            cecho $blue "run ${name}"
            $name
    fi
    if [ $input -eq $on_console ] && [ $output -eq $use_file ];then
        cecho $blue "run ${name} >${output_pointer}"
        $name >${output_pointer}
        [ $vis -eq $on ] && cat ${output_pointer} 
    fi

    #入力=pbpaste
    if [ $input -eq $use_clipboard ] && [ $output -eq $on_console ];then
        cecho $blue "run pbpaste | ${name}"
        [ $vis -eq $on ] && cecho $green `pbpaste | sed -e ':loop;N;$!b loop;s/\\n/\\\\n/g'`
        pbpaste | ${name}
    fi
    if [ $input -eq $use_clipboard ] && [ $output -eq $use_file ];then
        cecho $blue "run pbpaste | ${name} >${output_pointer}"
        [ $vis -eq $on ] && cecho $green `pbpaste | sed -e ':loop;N;$!b loop;s/\\n/\\\\n/g'`
            pbpaste | ${name}  >${output_pointer}
        [ $vis -eq $on ] && cat ${output_pointer} 
    fi

    #入力=ファイル
    if [ $input -eq $use_file ] && [ $output -eq $on_console ];then
        cecho $blue "run ${name} <${input_pointer}"
        [ $vis -eq $on ] && cecho $green `cat ${input_pointer} | sed -e ':loop;N;$!b loop;s/\\n/\\\\n/g' `
        $name <${input_pointer}
    fi
    if [ $input -eq $use_file ] && [ $output -eq $use_file ];then
        cecho $blue "run ${name} <${input_pointer} >${output_pointer}"
        [ $vis -eq $on ] && cecho $green `cat ${input_pointer} | sed -e ':loop;N;$!b loop;s/\\n/\\\\n/g' `
        $name <${input_pointer} >${output_pointer}
        [ $vis -eq $on ] && cat ${output_pointer} 
    fi
    
    return 0
}
function usage {
    cat << EOF
Usage:
gg [commands]
commands:
    run [option]
      option:
        -c       :use clipboard for input.
        -v       :visualize input and output
        -fi file :assign dir for input file
        -fo file :assign dir for output file
        -di dir  :assign dir for input directory
        -do dir  :assign dir for output directory
    set <src.cpp>
        ... set files to .cww
    open
        ... emacs {.cww} 
    build
        ... g++ {.cww}
    copy src
        ... pbcopy
EOF
}



case "${1}" in
    "set")
        file_set ${@:2} && cecho $green "succeeded"
    ;;
    "open")
        file_open && cecho $green "succeeded"        
    ;;
    "build")
        build && cecho $green "build succeeded"
        ;;
    "run")
        run_test ${@:2} && cecho $green "\\nrun succeeded"
        ;;
    "copy")
	cecho $blue "pbcopy <$2"
	pbcopy <$2 && cecho $green "copy succeeded"
        ;;
    *)
        usage
        ;;
esac
