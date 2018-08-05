<template>
  <v-layout justify-center align-center fill-height v-if="!location">
    <v-btn @click="getPosition">Please enable geolocation</v-btn>
  </v-layout>
  <v-layout fill-height column v-else>
    <link v-for="t in trees" :key="t.id" rel="preload" :href="t.picture" as="image">
    <Map
      v-if="location"
      :trees="trees"
      :center="location"
      @selected="select">
    </Map>
    <div v-if="treeSelected" class="tree-card" v-touch="{ left, right }">
      <TreeCard :tree="treeSelected"/>
    </div>
    <v-bottom-nav :value="true">
      <Verifications v-model="verify" :trees="trees"></Verifications>
      <v-btn @click="plant = true" flat>
        <span>Plant</span>
        <v-icon>nature</v-icon>
      </v-btn>
      <v-btn @click="verify = true" flat>
        <span>Verify</span>
        <v-icon>nature_people</v-icon>
      </v-btn>
    </v-bottom-nav>
  </v-layout>
</template>

<script>
import { mapGetters, mapMutations } from 'vuex'
import Map from '~/components/Map'
import Verifications from '~/components/Verifications'
import TreeCard from '~/components/TreeCard'
export default {
  components: {
    Map,
    Verifications,
    TreeCard
  },
  data: () => ({
    verify: false,
    plant: false,
    treeSelected: null,
  }),
  computed: {
    ...mapGetters({
      trees: 'trees',
      location: 'location',
    }),
    selectedIndex () {
      return this.treeSelected ? this.trees.findIndex(x => x.id === this.treeSelected.id) : -1
    }
  },
  methods: {
    ...mapMutations({
      setLocation: 'setLocation'
    }),
    getPosition () {
      navigator.geolocation
        .getCurrentPosition(x => this.setLocation(x.coords))
    },
    select (tree) {
      this.treeSelected = tree
    },
    left () {
      this.treeSelected = this.trees[(this.selectedIndex + 1) % this.trees.length]
    },
    right () {
      this.treeSelected = this.trees[(this.selectedIndex + this.trees.length - 1) % this.trees.length]
    }
  },
  mounted () {
    this.getPosition()
  }
}
</script>

<style scoped>
.tree-card {
  position: absolute;
  z-index: 1;
  padding: .7em;
  width: 100%;
  top: 0;
  right: 0;
  top: 0;
}
</style>
