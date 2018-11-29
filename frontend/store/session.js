import * as firebase from "firebase";

const state = {
  user: null
};

const mutations = {
  setUser: (state, payload) => {
    state.user = payload;
  }
};

const getters = {
  user: state => {
    return state.user;
  }
};

const actions = {
  async signUserInGithub({ rootState, dispatch }) {
    const user = await rootState.db.app
      .auth()
      .signInWithPopup(new firebase.auth.GithubAuthProvider());
    dispatch('autoSignIn', user.user.toJSON())
  },
  autoSignIn({ commit }, user) {
    commit("setUser", user);
  },
  logout({ rootState, commit }) {
    rootState.db.app.auth().signOut();
    commit("setUser", null);
  }
};

export default {
  namespaced: true,
  getters,
  state,
  mutations,
  actions
};
