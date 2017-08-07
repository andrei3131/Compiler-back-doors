How to build and use lighttpd:
Prerequisites: glibc-2.14, can be installed by running script install_glibc.sh

1. cd lighttpd1.4exploit
2. CC=' /usr/local/bin/gcc ' CFLAGS+=' -O2 ' ./configure --prefix=/CompilerBackdoors/lighttpd/prefix/ --without-bzip2
3. make
4. make install
5. cd .. (You must be under lighttpd. Critical step, as daemon not configured
and path to www dir is from this directory.)
6. sudo ./prefix/sbin/lighttpd -D -f lighttpd.conf (Make sure the configuration
file has the correct server.username and server.groupname)
7. Provided you are on the college network or have VPN configured,
you can access from the browser http://146.169.46.199:9000. When you access the
/download/ resource while the server is running in the Docker container,
you can login with any password.
