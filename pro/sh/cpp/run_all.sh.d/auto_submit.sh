#!/bin/bash

SH_DIR=$(cd $(dirname $0); pwd)
URL=${1}
echo "If do you want to submit, please type key [y]."
KEY1=`python3 ${SH_DIR}/input_with_timeout.py 5`
if [ ${KEY1} = "y" ]; then
    echo "submition to ${URL}"
    echo "If do you want to reformat code and expand header, please type key [y]."
    KEY2=`python3 ${SH_DIR}/input_with_timeout.py 5`
    if [ ${KEY2} = "y" ]; then
        echo ${2}
        pwd
        ${SH_DIR}/../header_expand.sh ${2}
    fi
    oj submit -y ${URL} ${2}
    echo "...done"
else
    echo "no submission"
fi
