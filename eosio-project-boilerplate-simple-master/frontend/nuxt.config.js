module.exports = {
  mode: 'spa',
  head: {
    meta: [
      { charset: 'utf-8' },
      { name: 'viewport', content: 'width=device-width, initial-scale=1' },
      { name: 'fragment', content: '!' },
      { hid: 'description', name: 'description', content: '' }
    ],
    link: [
      { rel: 'stylesheet', href: 'https://fonts.googleapis.com/css?family=Roboto:300,400,500,700|Material+Icons' }
    ]
  },
  env: {
    GMAP_KEY: process.env.GMAP_KEY
  },
  plugins: [
    { src: '~/plugins/vuetify.js' },
    { src: '~/plugins/gmap.js' },
  ],
  css: [
    '~/assets/style/app.styl'
  ]
}
