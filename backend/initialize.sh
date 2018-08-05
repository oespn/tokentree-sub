#!/usr/bin/env bash

cd "$(dirname "$0")"

docker pull eosio/eos-dev:v1.1.0

rm -rf "./data"
mkdir -p "./data"
docker rm --force eosio_container
