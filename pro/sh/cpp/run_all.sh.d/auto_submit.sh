#!/bin/bash

SH_DIR=$(cd $(dirname $0); pwd)
URL=${1}
echo "Please type key [y/n]"
KEY=`python3 ${SH_DIR}/input_with_timeout.py`
if [ ${KEY} = "y" ]; then
    echo "submition to ${URL}"
    oj submit ${URL} ${1}
    echo "...done"
else
    echo "no submission"
fi
