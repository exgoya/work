aa()
{
    echo "insert into test values($1,0, 'aaaaa');"
}

COUNT=0

while :
do
    COUNT=`expr $COUNT + 1`

    if [ $COUNT -gt 30000 ]; then
        break
    fi

    aa $COUNT
done
