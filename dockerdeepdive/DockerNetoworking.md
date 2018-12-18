Docker Networking
---------------------
docker network ls
docker network create -d bridge --subnet 10.0.0.1/24 ps-bridge
docker network inspect ps-bridge 
sudo apt-get bridge-utils
brctl show
ip link show
docker run -dt --name c1 --network ps-bridge alpine sleep 1d
docker run -dt --name c2 --network ps-bridge alpine sleep 1d

brctl show

Multi-host Networking Docker
--------------------------------
overlay Network
containers on mutliple host can connect each using VXLAN Tunnerl without crossing router

docker network create -d overlay ps-over
create container to see effect 
 docker service create --name ps-svc --network ps-over --replicas 2 alpine sleep 1d

vxlan id
------------ docker network inspect 
 "Options": {
            "com.docker.network.driver.overlay.vxlanid_list": "4097"
        },


MACVLAN - PROMISCOUS MOde required MAC address + IP COntainers
IPVLAN -  no bridge ,share one MAC but each with own IP, DHCP won't work with this



Network Services
--------------------
Infra + Application

    Service Discovery by Name or alias  
    -----------------
    ery container has a DNS server runs at 127.0.0.11:53

    Routing Mesh - Transport Layer L4
    ------------
    port based routing
    
    HTTP Routing Mesh (HRM)
--------------------------
Build on top of routing port mesh
Operates on L7
Require Docker DataCenter - Paid service
