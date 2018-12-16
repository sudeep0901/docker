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
