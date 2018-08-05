# Following steps from:
https://gist.github.com/sergmetelin/077704472e7b22349735757f64d7a929

$ cleos wallet create
PW:
"PW5J1J5HQyZTGnggdzGzdu2jb1ALA2SizWiQZgMKA6xMu4K3VuXrD"

$ cleos wallet open
$ cleos wallet unlock --password YOURPASSWORD

$ cleos create key
Private key: 5JWjNHwdQRWgLKoXBdPvT272rrjb9boageFYX1WgZQKtLzPC6pZ
Public key: EOS5pPyKBnDqcmkYMrDcqzWuRj2bcKXmzuLCEX3rvSX2jzShPwK2E
$ cleos create key
Private key: 5JkG8tEELJVikQRfKPJ89FTiXsfy9Xy3NfNNLJGBAAac9D5Krj9
Public key: EOS8VheQwZukEQePP88A27vjWi1jWPnEadLmUYH36kGgUzi1aS62t

$ cleos wallet import --private-key PRIVATEKEYOWNER
$ cleos wallet import --private-key PRIVATEKEYACTIVE


To get access to the container
docker exec -it eosio_notechain_container /bin/bash

eosiocpp -o /opt/eosio/bin/contracts/tokentree/tokentree.wasm /opt/eosio/bin/contracts/tokentree/tokentree.cpp
eosiocpp -g /opt/eosio/bin/contracts/tokentree/tokentree.abi /opt/eosio/bin/contracts/tokentree/tokentree.cpp
cleos set contract testacc /opt/eosio/bin/contracts/tokentree --permission testacc@active

# Get the chain id
cleos get info

https://github.com/EOSIO/eosjs

cleos get table testacc testacc treepatch
cleos push action testacc addoffer '["testacc", "153.53", "50", "test", "150"]' -p testacc

# in JS use this approach:
eos.contract('myaccount').then(myaccount => myaccount.myaction(..))

# FRONTEND 
npm run dev