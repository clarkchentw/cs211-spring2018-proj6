
if [[ $# -ne 1 ]]
then
    echo "Usage: $0 [Program Call]"
    exit 100
fi

while :
do
	clear;
        g++ $1 && ./a.out $2
        sleep 3
done

