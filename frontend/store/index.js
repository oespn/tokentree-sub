import Vuex from 'vuex'
import distance from '~/lib/distanceInKm'

const toMap = x => x.reduce((p, v) => ({ ...p, [v.id]: v }), {})

export default () => new Vuex.Store({
  state: {
    location: null,
    trees: require("~/assets/trees.json"),
    offers: require("~/assets/offers.json"),
    listings: require("~/assets/listings.json"),
  },
  getters: {
    location: state => state.location,
    trees: state => state.location
      ? state.trees
        .map(x => ({ ...x, distance: parseInt(distance(x.lat, x.lng, state.location.lat, state.location.lng) * 100) / 100 }))
        .sort((a, b) => a.distance - b.distance)
      : [...state.trees],
    offers: state => state.offers,
    listings: state => state.listings,
    treesMap: state => toMap(state.trees)
  },
  mutations: {
    setLocation: (state, location) => state.location = {
      lat: location.latitude,
      lng: location.longitude,
    }
  }
})
