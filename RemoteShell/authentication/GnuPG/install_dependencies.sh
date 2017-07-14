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

wget https://www.gnupg.org/ftp/gcrypt/pinentry/pinentry-1.0.0.tar.bz2
tar -xjv pinentry-1.0.0.tar.bz2
cd pinentry-1.0.0
apt-get install qt5-default
./configure
make
make install
cd ..

touch /etc/ld.so.conf.d/gpg2.conf
echo "usr/local/lib" >  /etc/ld.so.conf.d/gpg2.conf
ldconfig -v

apt-get install pinentry-curses
echo "pinentry-program usr/bin/pinentry-curses" > ~/.gnupg/gpg-agent.conf
gpg-connect-agent reloadagent /bye

apt-get install rng-tools
#Run this command to generate entropy: sudo rngd -r /dev/urandom

#Indicate that you trust a key:
#alice% gpg --edit-key blake

#pub  1024D/8B927C8A  created: 1999-07-02 expires: never      trust: q/f
#sub  1024g/C19EA233  created: 1999-07-02 expires: never
#(1)  Blake (Executioner) <blake@cyb.org>

#Command> trust
#pub  1024D/8B927C8A  created: 1999-07-02 expires: never      trust: q/f
#sub  1024g/C19EA233  created: 1999-07-02 expires: never
#(1)  Blake (Executioner) <blake@cyb.org>

#Please decide how far you trust this user to correctly
#verify other users' keys (by looking at passports,
#checking fingerprints from different sources...)?

# 1 = Don't know
# 2 = I do NOT trust
# 3 = I trust marginally
# 4 = I trust fully
# s = please show me more information
# m = back to the main menu

#Your decision? 3

#pub  1024D/8B927C8A  created: 1999-07-02 expires: never      trust: m/f
#sub  1024g/C19EA233  created: 1999-07-02 expires: never
#(1)  Blake (Executioner) <blake@cyb.org>
#
#Command> quit
#[...]
