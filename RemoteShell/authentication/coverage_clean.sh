rm -f coverage.info
lcov --zerocounters --directory GnuPG/gnupg-2.1.21/
cd GnuPG/gnupg-2.1.21/
#make distclean
./autogen.sh
cd ../..
