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
  },
  async create({ rootState, commit }, { campaign }) {
    const result = await rootState.db.collection(COLLECTION).add(campaign);
    commit("SET_CAMPAIGN", { campaign: await result.get() });
  }
};

const getters = {
  all: state => Object.keys(state.all)
    .map(x => state.all[x])
};

export default {
  namespaced: true,
  state,
  mutations,
  actions,
  getters
};
