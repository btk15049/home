set KEEP 1
set URL $argv[1]
set FILE $argv[2]
touch submit.lock
while test -f submit.lock
    sleep 60
    echo "try submit $FILE to $URL ..."
    oj submit $URL $FILE -y
    set KEEP $status
end
echo "submit done!"

if test -f submit.lock
    rm submit.lock
end