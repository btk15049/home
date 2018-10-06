DIR1=`dirname $1`
DIR2=`basename $1 .cpp`
DIR="$DIR1/$DIR2"
URL=`head -n 1 $1 | cut -c3-`
echo $DIR
echo $URL
if [ ! -d $DIR ]
then 
    mkdir $DIR
    oj dl $URL -d $DIR
fi
g++ -std=c++14 -Wall -Wextra $1
if [ -f a.out ]
then
    oj test -d $DIR
    rm a.out
fi
