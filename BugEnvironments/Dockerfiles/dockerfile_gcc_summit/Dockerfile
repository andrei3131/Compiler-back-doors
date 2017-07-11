FROM centos:6.6

RUN yum -y update; yum clean all
RUN yum -y install epel-release; yum clean all
RUN yum -y install vim curl make cmake wget
RUN yum -y groupinstall 'Development Tools'
RUN yum -y install  gmp  gmp-devel  mpfr  mpfr-devel  libmpc  libmpc-devel
RUN yum -y install tar


#  echo "deb http://cz.archive.ubuntu.com/ubuntu trusty main universe" >> /etc/apt/sources.list \


 RUN yum -y update \
  && buildDeps='wget subversion unzip bison flex libc6 libc6-dev libmpc-dev g++ gcc-multilib g++-multilib' \
  && CURRENT_GCC=gcc-r164319 \
  && yum -y install -y $buildDeps \

  && svn checkout -r 164319 svn://gcc.gnu.org/svn/gcc/trunk $CURRENT_GCC \

  && cd $CURRENT_GCC \

  && wget ftp://gcc.gnu.org/pub/gcc/infrastructure/gmp-4.3.2.tar.bz2 \
  && tar -xjvf gmp-4.3.2.tar.bz2 \

  && wget ftp://gcc.gnu.org/pub/gcc/infrastructure/mpfr-2.4.2.tar.bz2 \
  && tar -xjvf mpfr-2.4.2.tar.bz2 \

  && wget ftp://gcc.gnu.org/pub/gcc/infrastructure/mpc-0.8.1.tar.gz \
  && tar -xzvf mpc-0.8.1.tar.gz \

  #GMP
  && cd gmp-4.3.2 \
  && ./configure \
  && make \
  && make check \
  && make install \
  && cd .. \

  #MPC
  && cd mpc-0.8.1 \
  && ./configure \
  && make \
  && make check \
  && make install \
  && cd .. \

  #MPFR
  && cd mpfr-2.4.2 \
  && ./configure \
  && make \
  && make check \
  && make install \
  && cd .. \

  && mkdir objdir \
  && cd objdir \
  && ../configure --enable-languages=c,c++ --disable-bootstrap --disable-multilib --with-gmp=/usr/local --with-mpc=/usr/local --with-mpfr=/usr/local \
  && make -j$(nproc) \
  && make install \
  && make distclean \
  && cd ../..
