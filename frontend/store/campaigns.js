const COLLECTION = "campaigns";

const state = {
  all: {}
};

const mutations = {
  SET_CAMPAIGN: (state, { campaign }) => {
    state.all = {
      ...state.all,
      [campaign.id]: {
        id: campaign.id,
        ...campaign.data()
      }
    };
  }
};

const actions = {
  async fetchAll({ rootState, commit }) {
    const campaigns = await rootState.db.collection(COLLECTION).get();
    campaigns.forEach(campaign => commit("SET_CAMPAIGN", { campaign }));
    return campaigns;
  },
  async fetch({ rootState, commit }, id) {
    const campaign = await rootState.db.collection(COLLECTION).doc(id).get();
    commit("SET_CAMPAIGN", { campaign });
    return campaign;
  },
  async create({ rootState, getters, commit }, { campaign }) {
    const result = await rootState.db.collection(COLLECTION).add(campaign);
    const c = await result.get();
    commit("SET_CAMPAIGN", { campaign: c });
    return getters.all.filter(x => x.id === c.id)[0];
  }
};

const getters = {
  all: state => Object.keys(state.all).map(x => state.all[x])
};

export default {
  namespaced: true,
  state,
  mutations,
  actions,
  getters
};
