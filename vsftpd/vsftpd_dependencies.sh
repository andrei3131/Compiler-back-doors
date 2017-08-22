echo "root:admin" | chpasswd
yum -y install openssh-server
service sshd start
yum -y install libcap-devel
yum -y install ftp
yum -y install nmap
