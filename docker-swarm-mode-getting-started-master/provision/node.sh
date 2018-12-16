#!/bin/bash

# Install test version of docker engine, also shell completions
# curl -fsSL https://test.docker.com/ | sh

# Add the vagrant user to the docker group
usermod -aG docker vagrant

# Configure the docker engine
# Daemon options: https://docs.docker.com/engine/reference/commandline/dockerd/
# Set both unix socket and tcp to make it easy to connect both locally and remote
# You can add TLS for added security (docker-machine does this automagically)

mkdir /etc/docker
cat > /etc/docker/daemon.json <<END
{
    "hosts": [ 
        "unix://",
        "tcp://0.0.0.0:2375"
    ],
    "experimental": true,
    "debug": true,
    "metrics-addr": "0.0.0.0:9323" 
}
END
cat /etc/docker/daemon.json


echo "File daemon created"

# You can't pass both CLI args and use the daemon.json for parameters, 
# so I'm using the RPM systemd unit file because it doesn't pass any args 
# This version changes the following as of 17.03:
#  - Removes Requires=docker.socket
#  - Removes docker.socket from After
#  - Sets LimitNOFILE=infinity
#  - Removes -H fd:// from ExecStart 

wget -O /lib/systemd/system/docker.service https://raw.githubusercontent.com/docker/docker/v17.03.0-ce/contrib/init/systemd/docker.service.rpm

# check if docker daemon is running issue
# apt-get install \
#     apt-transport-https \
#     ca-certificates \
#     curl \
#     software-properties-common


# apt-get update

apt install apt-transport-https ca-certificates curl software-properties-common

add-apt-repository \
   "deb [arch=amd64] https://download.docker.com/linux/ubuntu bionic stable"
 
curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo apt-key add -
apt update

apt-get install -y docker.io

systemctl daemon-reload

echo "restring daemon"

# systemctl restart docker

# systemctl status docker

usermod -aG docker ${USER}
usermod -aG docker sudeep
su - ${USER}

iptables -A INPUT -p tcp --dport 2375 -j ACCEPT

groupadd docker
usermod -aG docker $(whoami)
usermod -aG docker sudeep
service docker restart
systemctl daemon-reload
service docker restart



# optional tools for learning 
apt-get install -y -q ipvsadm tree
# lsns is helpful from util-linux, this is installed already


# docker updates
# ----------------------------
swarmgs/payroll

# version 1
docker service create --name pay -p 3000:3000 swarmgs/payroll:1 #version 2



docker service scale pay=3
