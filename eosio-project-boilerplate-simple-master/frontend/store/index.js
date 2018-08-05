import Vuex from 'vuex'
import distance from '~/lib/distanceInKm'

export default () => new Vuex.Store({
  state: {
    location: null,
    trees: require("~/assets/trees.json"),
  },
  getters: {
    location: state => state.location,
    trees: state => state.location
      ? state.trees
        .map(x => ({ ...x, distance: parseInt(distance(x.lat, x.lng, state.location.lat, state.location.lng) * 100) / 100 }))
        .sort((a, b) => a.distance - b.distance)
      : [...state.trees],
    treesMap: state => state.trees
      .reduce((prev, value) => ({
        ...prev,
        [value.id]: value
      }), {})
  },
  mutations: {
    setLocation: (state, location) => state.location = {
      lat: location.latitude,
      lng: location.longitude,
    }
  }
})
