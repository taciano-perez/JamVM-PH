#!/bin/bash

clear

sudo make uninstall

sudo make clean

./configure --enable-ffi

python O2Remover.py

python IncludeMakefiles.py

make all

sudo make install
