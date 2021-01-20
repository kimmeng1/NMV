# docker-compose

The goal of this project is to visualize the performances and the resource consumptions of a microservice.

We will compose multiple microservices:

1. redis (the service we want to benchmark)
2. memtier (the service that will send requests to redis and measure the performances)
3. collector (the service that will collect resource comsumptions)
4. influxdb (the service that will store the metrics)
5. chronograf (the service that will visualize the metrics)

The first 4 services are already defined in `docker-compose.yml`.
You should be able to boot the project without vizualization, simply run `docker-compose up -d`, then `work.sh` to sends the requests. (check `docker stats` or `docker logs`)

* memtier and collector are linked to the influxdb service. They can connect to it and push the metrics.
* memtier is also linked to redis. It can send client requests.
* collector has `docker.sock` mounted. It can talk to the daemon to collect resource usages. (WARNING: why is this a poor security design?)

Configure the vizualisation service.

* https://hub.docker.com/_/chronograf/
* https://docs.influxdata.com/chronograf/v1.3/guides/create-a-dashboard/
* https://github.com/RedisLabs/memtier_benchmark
