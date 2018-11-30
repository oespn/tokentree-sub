import axios from "axios";

const state = {
  ratios: {}
};

const mutations = {
  SET_RATIO: (state, { couple, ratio }) => {
    state.ratios = {
      ...state.ratios,
      [couple]: ratio
    };
  }
};

const actions = {
  async fetchAll({ commit }) {
    const couple = "eos-usd";
    const { ticker } = (await axios.get(
      `https://api.cryptonator.com/api/ticker/${couple}`
    )).data;
    commit("SET_RATIO", {
      couple,
      ratio: parseFloat(ticker.price)
    });
  }
};

const getters = {
  ratios: state => state.ratios
};

export default {
  namespaced: true,
  state,
  mutations,
  actions,
  getters
};
