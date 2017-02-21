#!/bin/bash
set -x

clear

sudo make uninstall

sudo make clean

./configure --enable-ffi

python O2Remover.py

python IncludeMakefiles.py

make all

sudo make install

bash compile_java.sh
