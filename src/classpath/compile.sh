#!/bin/bash
clear
sudo make uninstall
sudo make clean
autoreconf --force --install --symlink
./configure --disable-Werror --disable-plugin --disable-gtk-peer --disable-gconf-peer --disable-tools --disable-examples
make
sudo make install
