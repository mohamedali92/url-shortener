#!/usr/bin/env bash

rm -rf $HOME/docker/volumes/cassandra
mkdir -p $HOME/docker/volumes/cassandra
DEFAULTPASSWORD=${1:-cassandra}
docker run --rm -d --name cassandra-docker -e CASSANDRA_PASSWORD_SEEDER=yes -e CASSANDRA_PASSWORD="$DEFAULTPASSWORD" -p 9042:9042 -v $HOME/docker/volumes/cassandra:/bitnami bitnami/cassandra:3.11.9

