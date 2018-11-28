module.exports = {
  mode: "spa",
  head: {
    meta: [
      { charset: "utf-8" },
      { name: "viewport", content: "width=device-width, initial-scale=1" },
      { name: "fragment", content: "!" },
      { hid: "description", name: "description", content: "" }
    ],
    link: [
      {
        rel: "stylesheet",
        href:
          "https://fonts.googleapis.com/css?family=Roboto:300,400,500,700|Material+Icons"
      }
    ]
  },
  env: {
    FIREBASE_API_KEY: process.env.FIREBASE_API_KEY || "AIzaSyDZveu5NOk66xUEp91Yo-nySZXks8b_GEo",
    FIREBASE_AUTH_DOMAIN: process.env.FIREBASE_AUTH_DOMAIN || "localhost",
    FIREBASE_PROJECT_ID: process.env.FIREBASE_PROJECT_ID || "crowdos-8dfa7"
  },
  plugins: [{ src: "~/plugins/vuetify.js" }],
  css: ["~/assets/style/app.styl"]
};
