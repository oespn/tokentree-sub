const APIs = [
  'getInfo',
  'getBlock'
]

module.exports = eos => APIs.reduce((prev, api) => ({
  ...prev,
  [api]: async (inputs, { success, error }) => {
    console.log(eos[api])
    try {
      const res = await eos[api](inputs)
      return success({ res })
    } catch(e) {
      return error({ message: e.toString() })
    }
  }
}), {})