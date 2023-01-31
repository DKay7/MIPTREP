for i in `seq $1` 
do 
    r=$(od -An -N1 -i /dev/urandom);

    if [ $r -eq 0 ]
    then
        r=1;
    fi

    echo "$r" >> test.txt
done 

echo "0" >> test.txt
