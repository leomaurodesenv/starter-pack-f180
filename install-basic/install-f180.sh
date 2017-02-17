#!/bin/bash


# ----------------------------------
# Necessidades
# ----------------------------------
# Diretórios
CUR_DIR=`pwd`
CUR_MAIN="$CUR_DIR/main"
echo "*- Install Starter Pack F180 (UFMS/CPPP) -*"
echo "Acessing: $CUR_DIR/"
echo "Main Folder: $CUR_MAIN/"
mkdir $CUR_MAIN

# Necessários (zip, findlib.xml, qtlib4)
cp -i -u $CUR_DIR/files/FindLibXML++.cmake /usr/share/cmake-2.8/Modules/
sudo apt-get install zip unzip
sudo apt-get install libxml++2.6-dev libxml++2.6-doc
sudo apt-get install build-essential cmake libqt4-dev libgl1-mesa-dev libglu1-mesa-dev libprotobuf-dev libode-dev libeigen3-dev
sudo apt-get install g++ libqt4-dev libeigen2-dev protobuf-compiler libprotobuf-dev libdc1394-22 libdc1394-22-dev libjpeg-dev libpng++-dev

# ----------------------------------
# Instalação grSim
# ----------------------------------
echo "Install: grSim"

# Temporário
wget http://vartypes.googlecode.com/files/vartypes-0.7.tar.gz
tar xfz vartypes-0.7.tar.gz
cd vartypes-0.7
mkdir build && cd build
cmake ..
make 
sudo make install
rm vartypes-0.7.tar.gz
rm -rf vartypes-0.7/

cd $CUR_DIR

# Install
unzip files/grSim-master.zip -d $CUR_MAIN
cd "$CUR_MAIN/grSim-master"
mkdir build
cd build
cmake ..
make cleanup_cache
make
cd $CUR_DIR

# ----------------------------------
# Instalação SSL Vision
# ----------------------------------
echo "Install: ssl-vision"

# Install
unzip files/ssl-vision-master.zip -d $CUR_MAIN
cd "$CUR_MAIN/ssl-vision-master"
make cleanup_cache
make
cd $CUR_DIR

