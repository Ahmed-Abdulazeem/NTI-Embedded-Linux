#!/bin/bash

### Create a new directory in home/usr ###

mkdir $HOME/script_exercise

for index in {1..10}
do
    if [ "${index}" -le 5 ]
    then
        echo "file${index} created"
        touch ~/script_exercise/file${index} 
    else
        echo "Timestamp was added to the file$((index - 5))"
        date >> ~/script_exercise/file$((index - 5))
    fi    
done

for index in {1..5}
do
    cat ~/script_exercise/file${index}
    echo "===================================="
done  	
