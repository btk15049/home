DIR1=`dirname $1`
DIR2=`basename $1 .cpp`
DIR="$DIR1/$DIR2"
URL=`head -n 1 $1 | cut -c3-`
if [ $URL == "" ]
then
    echo "URL is not found."
    exit 1
fi
echo $DIR
echo $URL
if [ ! -d $DIR ]
then
    mkdir $DIR
    oj dl $URL -d $DIR
fi
g++ -std=c++14 -Wall -Wextra $1 -DBTK
if [ -f a.out ]
then
    oj test -d $DIR
    rm a.out
fi
