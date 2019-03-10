ls -l /run
srw-rw----  1 root  docker    0 Dec 14 07:34 docker.sock

# adding user to run with non-root user - just add user to docker group
    check group exists

cat /etc/group
# check users
less /etc/passwd

echo $USER | getent passwd $USER

getent passwd 
getent passwd  0

#  adding aws user to cloud group
sudo gpasswd -a aws cloud
sudo gpasswd -a aws docker

# allowing access of docker container on network
netstat -tlp

docker -H IP:2375 -d &

export DOCKER_HOST="tcp://192.168.99.201:2375"

docker run -it centos /bin/bash

ping 8.8.8.8

ps -elf

cat /etc/hosts

[root@ae111c1831d8 /]# cat /etc/redhat-release 
CentOS Linux release 7.6.1810 (Core) 

docker can export images in -tar using save and  load from trt using 
docker load
docker save


Securing Docker Container Workloads
------------------------------------
Namespaces
control group - controlling access to resources
Cgroups
container workload privileges
Limiting access to the Kernel
linux security model


container shares kernel

container is abstraction of namespace, cgroups, isolated file structure

Linux Namespace
----------------
    Mount Namespace
    UTS namespace
    PID namspaces
    IPC namespace: POSIX MSGQ 
    Network namespace isolates network
    User namespace
    Cgroup namespace

/proc/self/ns

system call to create namespace

clone()  unshare() setns()

share host pid
--------------
docker container run -d --pid=host helloworld

docker container run -d --pid=container:#containerid# helloworld

share ipc
---------
docker container run -d --ipc=host helloworld
docker container run -d --ipc=container:#containerid# helloworld

share network
---------
docker container run -d --network=host helloworld
docker container run -d --network=container:#containerid# helloworld

share uts
---------
docker container run -d --uts=host helloworld

docker build -t receiver -f Dockerfile.receiver . 
 docker build -t sender -f Dockerfile.sender . 

 docker container run -it --name=receiver receiver

docker container run -it --ipc=container:receiver sender

Control Group
---------------

control groups are attached to subsystems on linux

control group heirarchy

sudo apt install htop

install the cgroup-tools package, and its dependencies
install the stress package

creating a cg group
-------------------
sudo cgcreate -a sudeep:sudeep -t sudeep:sudeep -g cpuset:all

sudeep@sudeep:/sys/fs/cgroup/cpuset/all$ dir

cgset -r cpuset.cpus=0 -r cpuset.mems=0 all
sudo cgcreate -a sudeep:sudeep -t sudeep:sudeep -g cpu:cg1
cat cpu.shares
1024


cgexec -g cpuset:all -g cpu:cg1 stess -q -c &

