buildDeps='wget unzip bison flex libmpc-dev g++'
CURRENT_GCC=gcc-r$1
apt-get install $buildDeps

svn checkout -r "$1" svn://gcc.gnu.org/svn/gcc/trunk $CURRENT_GCC


wget ftp://gcc.gnu.org/pub/gcc/infrastructure/gmp-4.3.2.tar.bz2
tar -xjvf gmp-4.3.2.tar.bz2

wget ftp://gcc.gnu.org/pub/gcc/infrastructure/mpc-0.8.1.tar.gz
tar -xzvf mpc-0.8.1.tar.gz

wget ftp://gcc.gnu.org/pub/gcc/infrastructure/mpfr-2.4.2.tar.bz2
tar -xjvf mpfr-2.4.2.tar.bz2

cp gmp-4.3.2 $CURRENT_GCC
cp mpc-0.8.1 $CURRENT_GCC
cp mpfr-2.4.2 $CURRENT_GCC
cd $CURRENT_GCC

#GMP
cd gmp-4.3.2
./configure
make
make install
cd ..

#MPC
cd mpc-0.8.1
./configure
make
make install
cd ..

#MPFR
cd mpfr-2.4.2
./configure
make
make install
cd ..

mkdir objdir
../configure --enable-languages=c,c++ --disable-multilib --disable-bootstrap \
--with-gmp=/usr/local --with-mpc=/usr/local --with-mpfr=/usr/local
make -j$(nproc)
make install
make distclean
cd ../..
