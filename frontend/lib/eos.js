
const Eos = require('eosjs')

const instance = Eos({
    httpEndpoint: 'http://localhost:8888',
    chainId: 'cf057bbfb72640471fd910bcb67639c22df9f92470936cddc1ade0e2f2e7dc4f',
    // this is Alices' private key
    keyProvider: "5KBPE51prPdCUVHAwhZwEgnvRdf119cwpgkWycTPCzWySPh8PNw", //"5JzsbVY1uKy9VFnNbt6FHZkwJzDU2L1X6xNwNaFyxf5dXJNS9ye",
    verbose: true
})
console.log(instance)

export default instance