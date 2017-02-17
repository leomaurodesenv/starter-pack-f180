#!/bin/bash

# ----------------------------------
# Instalação Qt Creator
# Baseado: https://wiki.qt.io/Install_Qt_5_on_Ubuntu
# ----------------------------------

# Diretórios
CUR_DIR=`pwd`
echo "Acessing: $CUR_DIR/"

# Instalação
echo "Install: Qt 5"
sudo apt-get install qtcreator
sudo apt-get install build-essential
sudo apt-get install mesa-common-dev
sudo apt-get install libglu1-mesa-dev -y

# Joystick
sudo apt-get install jstest-gtk

cd $CUR_DIR

