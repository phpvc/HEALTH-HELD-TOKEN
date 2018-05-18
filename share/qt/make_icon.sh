#!/bin/bash
# create multiresolution windows icon
# to use "convert", you should install it by "apt-get install imagemagick" 

ICON_SRC=bitcoin.png
ICON_DST=../../src/qt/res/icons/bitcoin.ico

ICON_DIR=../../src/qt/res/icons/
IMG_DIR=../../src/qt/res/images/

ICON_TESTNET_SRC=bitcoin.png
ICON_TESTNET_DST=../../src/qt/res/icons/bitcoin_testnet.ico
#ICON_SRC=bitcoin.png

#MAINNET ICON
convert ${ICON_SRC} -resize 16x16 bitcoin-16.png
convert ${ICON_SRC} -resize 24x24 bitcoin-24.png
convert ${ICON_SRC} -resize 32x32 bitcoin-32.png
convert ${ICON_SRC} -resize 48x48 bitcoin-48.png
convert ${ICON_SRC} -resize 256x256 bitcoin-256.png
convert bitcoin-16.png bitcoin-24.png bitcoin-32.png bitcoin-48.png bitcoin-256.png bitcoin.ico

cp bitcoin-256.png ${ICON_DIR}bitcoin.png
cp bitcoin.ico ${ICON_DST}
cp bitcoin.ico ../pixmaps/

#TESTNET ICON
convert ${ICON_TESTNET_SRC} -resize 16x16 bitcoin-16.png
convert ${ICON_TESTNET_SRC} -resize 24x24 bitcoin-24.png
convert ${ICON_TESTNET_SRC} -resize 32x32 bitcoin-32.png
convert ${ICON_TESTNET_SRC} -resize 48x48 bitcoin-48.png
convert ${ICON_TESTNET_SRC} -resize 256x256 bitcoin-256.png
convert bitcoin-16.png bitcoin-24.png bitcoin-32.png bitcoin-48.png bitcoin-256.png bitcoin_testnet.ico

cp bitcoin-256.png ${ICON_DIR}bitcoin_testnet.png
cp bitcoin_testnet.ico ${ICON_TESTNET_DST}


cp splash.png ${IMG_DIR}splash.png
cp splash_testnet.png ${IMG_DIR}splash_testnet.png

#rm bitcoin-*

