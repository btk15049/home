#!/usr/local/bin/fish

if test (count $argv) -ne 3
  echo "Usage" 1>&2
  echo "build.sh <g++> <target> <testcase>" 1>&2
  exit 1
end

set BUILD $argv[1]
set ARGS "-std=c++17 -O3 -Wall -Wextra"
set TARGET (basename $argv[2])
set BINARY (basename $argv[2] .cpp).out
set INPUT $argv[3]
set OUTPUT (echo $INPUT | sed -e s@in/@out/@)

echo "BUILD  = $BUILD"
echo "ARGS   = $ARGS"
echo "TARGET = $TARGET"
echo "BINARY = $BINARY"
echo "INPUT  = $INPUT"
echo "OUTPUT = $OUTPUT"

if test -f $BINARY
  rm $BINARY
end

echo "" #<br/>

set BUILD_CMD "$BUILD $TARGET -o $BINARY $ARGS"
echo $BUILD_CMD
eval $BUILD_CMD

if test ! -f $BINARY
  echo "build failed." 1>&2
  exit 1
end

echo "" #<br/>

set RUN_CMD "./$BINARY <$INPUT >$OUTPUT"
echo $RUN_CMD
eval $RUN_CMD

echo "" #<br/>

set SHOW_CMD "tail $OUTPUT"
echo $SHOW_CMD
eval $SHOW_CMD

rm $BINARY

