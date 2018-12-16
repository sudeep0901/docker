
# check swarm mode

docker info
# strt swarm mode

docker init


docker node -h

#list docker node
docker node ls

docker node inspect sudeep

docker node inspect self


docker service -h

# run a container in a node

 docker service create --name web --publish 8080:80  nginx

 docker service ls


#taks details
docker service ps web


#removing service
 docker service rm web

 # update service to run more than one tasl

  docker service update --replicas=2 web

# scale taks to 4 instances
  docker service scale web=4

# Read tasks & Scheduling
docker service create --name customer-api --publish 3000:3000 swarmgs/customer
--
#adding Node multiple nodes
# remove node 
docker swarm leave

docker swarm leave --force

#Create docker machine to create node
docker-machine create -d virtualbox m1

docker-machine env m1

eval $(docker-machine env m1)

vagrant up m1 m2 w1 w2

# to access docker machines from host use environment variable

DOCKER_HOST=192.168.99.201

docker image ls

# or 

$env:DOCKER_HOST="192.168.99.201"


#error while connecting - Cannot connect to the Docker daemon at tcp://192.168.99.201:2375. Is the docker daemon running?
and

>> Solution below

# add daemon json file
<!-- https://raw.githubusercontent.com/docker/docker/v17.03.0-ce/contrib/init/systemd/docker.service.rpm -->

# starting swarm mode in o multinode cluster

docker info| grep Name

docker info| grep Swarm


<!-- docker swarm init
Error response from daemon: could not choose an IP address to advertise since this system has multiple addresses on different interfaces (10.0.2.15 on enp0s3 and 192.168.99.201 on enp0s8) - specify one with --advertise-addr -->


<!-- mutliple network interfaces and swarm not able to determine where to start 
swarm cluster - hence use --advertise-addr -->

docker swarm init --advertise-addr 192.168.99.201

#check swarm is active

docker info | grep Swarm

docker swarm init --advertise-addr 192.168.99.201

<!-- Swarm initialized: current node (kl8684ep2lzvy7id2nbgtk01w) is now a manager.

To add a worker to this swarm, run the following command:

    docker swarm join --token SWMTKN-1-3kwicllwf0n5t5th9cjjerqpjelezqnw40j4lf0p5dg4hz8yh7-7kqmdom9v1n5pokwan53if083 192.168.99.201:2377

To add a manager to this swarm, run 'docker swarm join-token manager' and follow the instructions. -->

iptables -I INPUT -p tcp -m tcp --dport 2375 -j ACCEPT


#get the token to join as worker
docker swarm join-token worker

# use on master to check node status
docker node ls


# Cluster vishualizor
docker service create \
  --name=viz \
  --publish=8090:8080/tcp \
  --constraint=node.role==manager \
  --mount=type=bind,src=/var/run/docker.sock,dst=/var/run/docker.sock \
  dockersamples/visualizer


  # http://192.168.99.201:8090/

# create a service from node manager and it will distribute work to worker machines
  docker service create --name customer-api --publish 3000:3000 swarmgs/customer

# scale customer api
docker service scale customer-api=2

http://192.168.99.212:3000/customer/1

ab -n 1000 -c 4 http://192.168.99.201:3000/customer/1

docker network inspect ingress

#to check task
docker node ps m1 w1 w2

# dpromote to manager
docker node promote w1


# take of the nodes 
docker node update --availability=drain w2

#bring up
docker node update --availability=active w2

# to MOnitor container matrices - cadvisor
docker service create --mode=global --name=cadviser 



https://blog.codeship.com/monitoring-docker-containers/
https://blog.codeship.com/monitoring-docker-containers-with-elasticsearch-and-cadvisor/


docker service create --mode global --name cadvisor \
  --mount type=bind,source=/,target=/rootfs,readonly=true \
  --mount type=bind,source=/var/run,target=/var/run,readonly=false \
  --mount type=bind,source=/sys,target=/sys,readonly=true \
  --mount type=bind,source=/var/lib/docker/,target=/var/lib/docker,readonly=true \
  google/cadvisor:latest \
  -storage_driver=elasticsearch \
  -storage_driver_es_host="http://elasticsearch:9200"


# Docker swarmkit to work with Swarm easily


# Ingress Routing & Publishing port 

# update service definition remove published port

 docker service update --publish-rm 9090 cadvisor

docker service update --publish-add mode=host,published=8080,target=8080 cadvisor


#cadvisor end point
http://192.168.99.201:8080/docker/


# random
docker service create --name customer-api random -p target=3000 swarmgs/customer


# update docker applicatoin version 2

docker service update --image swarmgs/payroll:2
docker service update --image swarmgs/payroll:2 pay

# 3rd version
 docker service update --image swarmgs/payroll:3 --update-delay=20s  pay

# rollback to previous version

 docker service update --image swarmgs/payroll:3 --update-delay=20s --update-parallelism=2  pay


# taks clean up
docker service scale=0


# use watch command to observe progress of any command
watch docker service ls

<!-- check rollout mode -->

# check --rollback flag in docker github repo documentation

# check - --force flag

--update -monitor

# to resume paused update

service update pay(servic name)

#Networkint

overlay Network
---------------------

do not expose api ports to external

# check ingress network
# creating overlay network


docker network create -d overlay --subnet=10.0.9.0/24 backend

 docker network ls
NETWORK ID          NAME                DRIVER              SCOPE
11pv3noy3vu6        backend             overlay             swarm
a87cdc5046a9        bridge              bridge              local
bf1294976592        docker_gwbridge     bridge              local
58944a26225b        host                host                local
v817ldxnkz5r        ingress             overlay             swarm
6316cecf3090        none                null                local


# using created overlay netowkr and exposing 5000 port and mapping it to 3002 internal port of service
 docker service create --name balance -p 5000:3000 \
> --network backend \
> swarmgs/balance


# create customer api whcih will be used by balance api


docker service create --name customer --network backend swarmgs/customer


# note not port is exposed from service, balance api will internally discover api
# http://192.168.99.201:5000/balance/1 - still does not work

<!-- IP in host varilable in node js app -->

# check service logs
docker service logs balance 


# service discovery using service name
<!-- , provide environment varialbe -->

# add environment variable
docker service  update --env-add MYWEB_CUSTOMER_API=customer:300 blanace



sudeep@sudeep:~/Projects/github/docker/docker-swarm-mode-getting-started-master$ docker exec -it 7d6c41226254 bash
root@7d6c41226254:/app# dig customer

; <<>> DiG 9.9.5-9+deb8u10-Debian <<>> customer
;; global options: +cmd
;; Got answer:
;; ->>HEADER<<- opcode: QUERY, status: NOERROR, id: 16220
;; flags: qr rd ra; QUERY: 1, ANSWER: 1, AUTHORITY: 0, ADDITIONAL: 0

;; QUESTION SECTION:
;customer.			IN	A

;; ANSWER SECTION:
customer.		600	IN	A	10.0.9.9 
# internal loadbalancer

;; Query time: 4 msec
;; SERVER: 127.0.0.11#53(127.0.0.11)
;; WHEN: Thu Dec 13 04:10:47 UTC 2018
;; MSG SIZE  rcvd: 50


# root@7d6c41226254:/app# dig tasks.customer

; <<>> DiG 9.9.5-9+deb8u10-Debian <<>> tasks. customer
;; global options: +cmd
;; Got answer:
;; ->>HEADER<<- opcode: QUERY, status: SERVFAIL, id: 46796
;; flags: qr rd ra; QUERY: 1, ANSWER: 0, AUTHORITY: 0, ADDITIONAL: 1

;; OPT PSEUDOSECTION:
; EDNS: version: 0, flags:; udp: 65494
;; QUESTION SECTION:
;tasks.				IN	A

;; Query time: 4 msec
;; SERVER: 127.0.0.11#53(127.0.0.11)
;; WHEN: Thu Dec 13 04:11:50 UTC 2018
;; MSG SIZE  rcvd: 34

;; Got answer:
;; ->>HEADER<<- opcode: QUERY, status: NOERROR, id: 8584
;; flags: qr rd ra; QUERY: 1, ANSWER: 1, AUTHORITY: 0, ADDITIONAL: 0

;; QUESTION SECTION:
;customer.			IN	A

;; ANSWER SECTION:
customer.		600	IN	A	10.0.9.9

;; Query time: 1 msec
;; SERVER: 127.0.0.11#53(127.0.0.11)
;; WHEN: Thu Dec 13 04:11:50 UTC 2018
;; MSG SIZE  rcvd: 50

root@7d6c41226254:/app# dig tasks.customer

; <<>> DiG 9.9.5-9+deb8u10-Debian <<>> tasks.customer
;; global options: +cmd
;; Got answer:
;; ->>HEADER<<- opcode: QUERY, status: NOERROR, id: 8977
;; flags: qr rd ra; QUERY: 1, ANSWER: 6, AUTHORITY: 0, ADDITIONAL: 0

;; QUESTION SECTION:
;tasks.customer.			IN	A

;; ANSWER SECTION:
tasks.customer.		600	IN	A	10.0.9.17
tasks.customer.		600	IN	A	10.0.9.10
tasks.customer.		600	IN	A	10.0.9.16
tasks.customer.		600	IN	A	10.0.9.13
tasks.customer.		600	IN	A	10.0.9.15
tasks.customer.		600	IN	A	10.0.9.14

;; Query time: 3 msec
;; SERVER: 127.0.0.11#53(127.0.0.11)
;; WHEN: Thu Dec 13 04:12:00 UTC 2018
;; MSG SIZE  rcvd: 212


# http://192.168.99.201:5000/inspect
# IVPS - IP Virtual Server

# DNT Round robin

docker service update --endpoint-mode=dnsrr customer ( for own loadbalancer to use and do not use internal LB or do not want to load balance)

# Docker stacks
----------------
 # To create / update
 docker stack deploy -c services/viz.yml viz


 #remote
 docker stack rm viz

 docker stack ps apis





