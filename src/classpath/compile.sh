#!bin/bash

clear

sudo make uninstall

sudo make clean

sudo ./configure --disable-Werror --disable-plugin --disable-gtk-peer --disable-gconf-peer --disable-tools --disable-examples

sudo make

sudo make install
