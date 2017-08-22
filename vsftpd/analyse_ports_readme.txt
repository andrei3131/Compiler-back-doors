# Port scanning
nmap -p 1-65535 -T4 -A -v localhost
sudo netstat -tulpn | grep :<port> (to see what app is using that port)

