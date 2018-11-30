import * as firebase from "firebase";

const state = {
  user: null
};

const mutations = {
  SET_USER: (state, payload) => {
    state.user = payload;
  }
};

const getters = {
  user: state => state.user
};

const actions = {
  async signUserInGithub({ rootState, dispatch }) {
    const user = await rootState.db.app
      .auth()
      .signInWithPopup(new firebase.auth.GithubAuthProvider());
    dispatch("autoSignIn", user.user.toJSON());
  },
  autoSignIn({ commit }, user) {
    commit("SET_USER", user);
  },
  logout({ rootState, commit }) {
    rootState.db.app.auth().signOut();
    commit("SET_USER", null);
  }
};

export default {
  namespaced: true,
  getters,
  state,
  mutations,
  actions
};
