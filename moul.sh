#!/bin/bash

make re

i=0

while [ $i -le 200 ]; do
    nb_phil="`echo $RANDOM%100+2 | bc`"
    nb_eat="`echo $RANDOM%100+1 | bc`"
    ret="`LD_PRELOAD=./libriceferee.so ./philo -p $nb_phil -e $nb_eat | grep "Inconsistences found: 0"`"
    if [ -z "$ret" ];then
	echo -e "test n° $i:\t[\e[0;31mER\e[0m] avec -p $nb_phil -e $nb_eat"
    else
	echo -e "test n° $i:\t[\e[0;32mOK\e[0m] avec -p $nb_phil -e $nb_eat"
    fi
    i=$((i+1))
done
