rm -rf *.tar.bz2

wget https://www.gnupg.org/ftp/gcrypt/libgpg-error/libgpg-error-1.27.tar.bz2
tar -xjvf libgpg-error-1.27.tar.bz2
rm -rf libgpg-error-1.27.tar.bz2
cd libgpg-error-1.27
./configure
make
make install
cd ..


wget https://www.gnupg.org/ftp/gcrypt/libgpg-error/libgpg-error-1.27.tar.bz2
tar -xjvf libgpg-error-1.27.tar.bz2
cd libgpg-error-1.27
./configure
make
make install

wget https://www.gnupg.org/ftp/gcrypt/npth/npth-1.5.tar.bz2
tar -xjvf npth-1.5.tar.bz2
rm -rf npth-1.5.tar.bz2
cd npth-1.5
./configure
make
make install
cd ..

wget https://www.gnupg.org/ftp/gcrypt/libgcrypt/libgcrypt-1.7.8.tar.bz2
tar -xjvf libgcrypt-1.7.8.tar.bz2
rm -rf libgcrypt-1.7.8.tar.bz2
cd libgcrypt-1.7.8
./configure
make
make install
cd ..

wget wget ftp://ftp.gnupg.org/gcrypt/libksba/libksba-1.3.4.tar.bz2
tar -xjvf libksba-1.3.5.tar.bz2
rm -rf libksba-1.3.5.tar.bz2
cd libksba-1.3.5
./configure
make
make install
cd ..


wget https://www.gnupg.org/ftp/gcrypt/libassuan/libassuan-2.4.3.tar.bz2
tar -xjvf libassuan-2.4.3.tar.bz2
cd libassuan-2.4.3
./configure
make
make install
cd ..

