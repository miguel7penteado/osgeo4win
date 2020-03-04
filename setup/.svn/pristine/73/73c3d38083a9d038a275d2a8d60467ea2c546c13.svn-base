#!/bin/sh

VER=1.0.7-1

strip -s setup.exe
upx --best setup.exe

rm -rf release
mkdir release
mkdir release/bin
mkdir release/etc
mkdir release/etc/postinstall
mkdir release/etc/preremove

cp setup.exe release/bin/osgeo4w-setup.exe
cp postinstall.bat release/etc/postinstall/setup.bat
cp preremove.bat release/etc/preremove/setup.bat
cp setup.bat release/bin
cp setup-test.bat release/bin

cd release
tar cjvf ../setup-$VER.tar.bz2 etc bin
