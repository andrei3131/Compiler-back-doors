This contains information about each directory of the repository:

BugEnvironments:

** Note: The explanations below help reproduce only the bugs in bugs/Csmith and bugs/GCCsummit **

The gcc_install_script.sh is used to build a certain revision of gcc inside a virtual machine. I created a Ubuntu 9.10 (32-bit) virtual machine to be able to
reproduce gcc bug 42721. I created an appliance which you can import in
VirtualBox and see how the compiler behaves for the program in question. Steps to set-up the appliance:
1. sudo wget www.doc.ic.ac.uk/~ab7515/Ubuntu910.ova (Must be run as root)
2. Import appliance into VirtualBox
3. Login using username: andrei  and password: administrator
4. Access the buggy revision of gcc in ** /usr/local/bin/gcc ** and check  
   that the last line is 'gcc version 4.5.0 20100112 (experimental) GCC'
5. You can check that the small.c file under /home/andrei contains the concise
   version of the program, as specified in the Google document.
6. Compile using -O1 and -O2 flags and check that for -O2 the execution is aborted.


For ** all other ** gcc bugs, I created separate CentOS containers which you can
create and try as follows:
1. cd Dockerfiles
2. Identify the container you want to build corresponding to the bug id, as
documented in the Google document: dockerfile_gcc_<bug_id>
3. docker build -t centos_gcc_<bug_id> <Path to the folder containing the Dockerfile i.e dockerfile_gcc_<bug_id>/>
4. Make sure the PWD is the repository root (you want to access the bugs folder)
docker run -ti -v "$PWD":/usr/src/ -w /usr/src/ centos_gcc_<bug_id>
5. Note that the buggy version of gcc is ** /usr/local/bin/gcc **
6. Consult the Google doc ** Reported behaviour ** section for the chosen bug_id to check how to reproduce the bug.


bugs:

Csmith and GCCsummit contain bugs generated using Csmith. The file that must be compiled using the buggy gcc version is ** small.c **

Remote Shell:

The purpose of this shell is purely experimental. The code follows the one in
the tutorial at https://0x00sec.org/t/remote-shells-part-i/269.
There are two types of shells: one is a secure shell which uses repeated
xor with the number 42 (see https://linux.die.net/man/3/memfrob) and the
other is an 'invisible' shell which transmits the commands as ICMP packets.

By default, the shell I exploited using compiler bugs is the secure shell. I implemented a minimal authentication system having username **admin** and password **password**. The way this shell should be used is as follows:

1. After you build one of the Docker containers associated with a bug, clone the repo inside the container.
2. cd CompilerBackdoors/RemoteShell
1. Build using ** make all **
2. ./remote_shell_exe s <port>   (i.e. the server)
   ./remote_shell_exe c <target ip>  <port> (i.e. the client. Note that you can try it locally. In this case the attacker ip is 127.0.0.1)
3. You will be prompted to enter the username (followed by enter) and a password (followed by enter).
4. All exploits have been designed to provide access to the server for any supplied password P=c1 c2 c3....c8, where
[ci <= p | p <- "password"].
5. When you run the secure shell on a machine with a good compiler version, you should only be able to authenticate when the introduced password is "password".
