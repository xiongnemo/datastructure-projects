#!/bin/bash
if (which g++); then
        for i in {1..10}; do
                cd $i && echo Compiling binaries for problem $i...
                g++ ./*.cc ./*.h -Wall -o $i.out
                if [ $? -eq 0 ]; then
                        echo The compilation process of problem $i completed with no errors.
                else
                        echo The compilation process of problem $i failed.
                fi
                cd ../
        done
else
        echo No g++.
fi
