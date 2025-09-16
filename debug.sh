#!/bin/bash

make clean
make 
# Compile with debug symbols
gcc -g -c testing/main.c -o test.o
gcc -g -o test test.o -L. -leom DataStructures/DataStructures.a Networking/Networking.a Systems/System.a
# Run with lldb
lldb ./test
