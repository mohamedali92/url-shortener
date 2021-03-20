#!/usr/bin/env bash

rm -rf $HOME/docker/volumes/postgres
mkdir -p $HOME/docker/volumes/postgres
SUPERUSERPASSWORD=${1?Error: no password given}
DEFAULTDB=${2:-urls}
docker run --rm --name pg-docker -e POSTGRES_PASSWORD="$SUPERUSERPASSWORD" -e POSTGRES_DB="$DEFAULTDB" -d -p 5432:5432 -v $HOME/docker/volumes/postgres:/var/lib/postgresql/data postgres