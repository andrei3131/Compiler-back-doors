cd vsftpd-3.0.3
# The -fno-strict-overflow flag was added in the Makefile
make 
cp vsftpd ../prefix/
cp vsftpd.conf.5 ../prefix/
cp vsftpd.8 ../prefix
cd ..
