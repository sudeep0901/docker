
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

