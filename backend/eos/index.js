const MESG = require('mesg-js').service()
const api = require('./tasks/api')
// MESG.listenTask({
//   taskX: require('./tasks/taskX')
// })

// MESG.emitEvent("started", { x: true })

const EOS = require("eosjs")

chain = {
  main: 'aca376f206b8fc25a6ed44dbdc66547c36c6c33e3a119ffbeaef943642f0e906', // main network
  jungle: '038f4b0fc8ff18a4f0842a8f0564611f6e96e8535901dd45e43ac8691a1c4dca', // jungle testnet
  sys: '1ada1e31ac1a090303d60ed9e9e40db669fbd851ae68b97d092c9b46159bb7f5' // local developer
}

const eos = EOS({
  keyProvider: '5JtUScZK2XEp3g9gh7F8bwtPTRAkASmNrrftmx4AxDKD5K4zDnr',
  httpEndpoint: 'http://nodeos:8888',
  chainId: chain.sys,
})

MESG.listenTask({
  ...api(eos)
})

// const fetch = require("node-fetch")
// const { TextDecoder, TextEncoder } = require("text-encoding")

// const defaultPrivateKey = "5JtUScZK2XEp3g9gh7F8bwtPTRAkASmNrrftmx4AxDKD5K4zDnr"; // useraaaaaaaa
// console.log(JsSignatureProvider)
// const signatureProvider = new JsSignatureProvider([defaultPrivateKey]);

// const rpc = new JsonRpc('http://127.0.0.1:8000', { fetch: fetch })
// const api = new Api({ rpc, signatureProvider, textDecoder: new TextDecoder(), textEncoder: new TextEncoder() });
