for file in `\find in/ -maxdepth 1 -type f`; do
    file=`basename ${file}`
    input="in/${file}"
    tmp="tmp/${file}"
    output="out/${file}"
    echo ${file}
    ./a.out < ${input} > ${tmp}
    perl -p -e 's/\n/\r\n/' < ${tmp} >${output}
done