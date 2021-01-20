#!/bin/bash
set -x -e

SIZE=$((2**12)) # 512MB max
REQUESTS=$((2*189841)) #$((2**30/${SIZE}/2))

EXTRA_INIT="-d ${SIZE} --key-pattern=S:S --key-maximum=${REQUESTS} --ratio=1:0 --requests=${REQUESTS} -c 1 -t 1"
EXTRA_HIGH="-d ${SIZE} --key-pattern=R:R --key-maximum=${REQUESTS} --ratio=0:1 -c 1 -t 1"

docker-compose exec memtiera run -- memtier_benchmark -s redisa ${EXTRA_INIT}
docker-compose exec redisa redis-cli save
docker-compose exec memtiera job run -- memtier_benchmark -s redisa ${EXTRA_HIGH} --test-time 300
