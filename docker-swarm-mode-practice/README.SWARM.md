
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
