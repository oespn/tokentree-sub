#!/usr/bin/env bash

echo "=== setup blockchain accounts and smart contract ==="

# change to executable directory
cd "/opt/eosio/bin"

set -m

# start nodeos ( local node of blockchain )
# run it in a background job such that docker run could continue
nodeos -e -p eosio -d /mnt/dev/data --config-dir /mnt/dev/config --http-validate-host=false \
  --plugin eosio::wallet_api_plugin \
  --plugin eosio::wallet_plugin \
  --plugin eosio::producer_plugin \
  --plugin eosio::history_plugin \
  --plugin eosio::chain_api_plugin \
  --plugin eosio::history_api_plugin \
  --plugin eosio::http_plugin \
  --http-server-address=0.0.0.0:8888 \
  --access-control-allow-origin=* \
  --contracts-console &

sleep 1s
  until curl localhost:8888/v1/chain/get_info
do
  sleep 1s
done

sleep 2s

echo "=== setup wallet for the block producer === "
./cleos wallet create -n eosiomain
./cleos wallet import -n eosiomain --private-key 5KQwrPbwdL6PhXujxW37FSSQZ1JiwsST4cqQzDeyXtP79zkvFD3
./cleos wallet import -n eosiomain --private-key 5KBPE51prPdCUVHAwhZwEgnvRdf119cwpgkWycTPCzWySPh8PNw #alice

echo "=== setup wallet: tokentree ==="
./cleos wallet create -n wtokentree | tail -1 | sed -e 's/^"//' -e 's/"$//' > wallet_password.txt
# ./cleos wallet open -n wtokentree
# ./cleos wallet unlock -n wtokentree --password $(cat wallet_password.txt)
./cleos wallet import -n wtokentree --private-key 5JzsbVY1uKy9VFnNbt6FHZkwJzDU2L1X6xNwNaFyxf5dXJNS9ye
./cleos wallet import -n wtokentree --private-key 5KLqT1UFxVnKRWkjvhFur4sECrPhciuUqsYRihc1p9rxhXQMZBg

./cleos create account eosio atokentree EOS5i3KbjWXR6e9B7GhgCf8vbBgDH4CE1sQ3baDQ8W6BV7kU3S6k1 EOS78RuuHNgtmDv9jwAzhxZ9LmC6F295snyQ9eUDQ5YtVHJ1udE6p
#./cleos create account eosio eosio.token EOS5i3KbjWXR6e9B7GhgCf8vbBgDH4CE1sQ3baDQ8W6BV7kU3S6k1 EOS78RuuHNgtmDv9jwAzhxZ9LmC6F295snyQ9eUDQ5YtVHJ1udE6p
./cleos create account eosio eosio.token EOS69yzjJbMjhd2KTs6tuwaUWkTGvtN33nWGKeTDsdQjswz1hAT7p EOS7R2cxnj7Yh5EsBsGXyUf2eCt5tbXck785RpiATFPR2hgFVCgQA

echo "==== create alice ====="
./cleos create account eosio alice EOS69yzjJbMjhd2KTs6tuwaUWkTGvtN33nWGKeTDsdQjswz1hAT7p EOS69yzjJbMjhd2KTs6tuwaUWkTGvtN33nWGKeTDsdQjswz1hAT7p

echo "=== deploy smart contract ==="
# $1 smart contract name
# $2 account holder name of the smart contract
# $3 wallet for unlock the account
# $4 password for unlocking the wallet
./scripts/deploy_contract.sh tokentree atokentree wtokentree $(cat wallet_password.txt)

#./cleos push action eosio updateauth "{\"account\": eosio.token,\"permission\": \"active\",\"parent\": \"owner\",\"auth\": {\"threshold\": 1, \"keys\": [], \"waits\": [],\"accounts\": [{\"weight\": 1,\"permission\": {\"actor\": atokentree, \"permission\": \"active\"}}]}}" -p atokentree@active
./cleos set account permission alice active '{"threshold": 1,"keys": [{"key": "EOS69yzjJbMjhd2KTs6tuwaUWkTGvtN33nWGKeTDsdQjswz1hAT7p","weight": 1}],"accounts": [{"permission":{"actor":"atokentree","permission":"eosio.code"},"weight":1}]}' owner -p alice
./cleos set account permission atokentree active '{"threshold": 1,"keys": [{"key": "EOS5i3KbjWXR6e9B7GhgCf8vbBgDH4CE1sQ3baDQ8W6BV7kU3S6k1","weight": 1}],"accounts": [{"permission":{"actor":"atokentree","permission":"eosio.code"},"weight":1}]}' owner -p atokentree

echo "=== create user accounts ==="
./scripts/create_accounts.sh

echo "=== end of setup blockchain accounts and smart contract ==="
touch "/mnt/dev/data/initialized"

# put the background nodeos job to foreground for docker run
fg %1

