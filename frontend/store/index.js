import Vuex from "vuex";

export default () =>
  new Vuex.Store({
    state: {
      company: false,
      user: {
        picture: "https://randomuser.me/api/portraits/men/85.jpg",
        name: "John Leider"
      }
    },
    getters: {},
    mutations: {}
  });
