#!/bin/sh


# build lzma, mksquashfs and unsquashfs and copy them
cd tools
cd mksquash_lzma-3.2
make
cd ..
cd lzma-4.32.0beta5
./configure
make
cd ..
cd ..

cp ./tools/lzma-4.32.0beta5/src/lzma/lzma                             ./firmware/tools/lzma
cp ./tools/mksquash_lzma-3.2/squashfs3.2-r2/squashfs-tools/mksquashfs ./firmware/tools/mksquashfs
cp ./tools/mksquash_lzma-3.2/squashfs3.2-r2/squashfs-tools/unsquashfs ./firmware/tools/unsquashfs

# build Uboot
cd ./uboot/
cd ./Uboot
./buildUboot.sh

cd ..
cd ..
cp -Rf ./uboot/Uboot/uboot.bin          ./firmware/images/uboot.bin

#build toolchain
cd ./tools/buildroot/
make oldconfig
make
cd ../..

#build fw
cd ./firmware/
make

echo "*********************** COMPLETED ************************"
