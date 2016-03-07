make re;
i=0;
for (( i = 0; i < $1; i++ )); do
    LD_PRELOAD=./libriceferee.so ./philo -p $2 -e $3 | grep "Inconsistences";
done
