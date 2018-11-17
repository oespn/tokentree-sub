<template>

    <v-card>

        <v-container
          id="scroll-target"
          style="max-height:700px"
          class="scroll-y"
          fluid
          grid-list-lg
        >
          <v-layout row wrap v-scroll>
            <v-flex xs12>

              <v-card color="blue-grey darken-2" class="white--text">
                <v-card-title primary-title>
                  <div class="headline">Checking code pays!</div>
                  <div>Now you can earn tokens rewards for checking code even when you don't find a bug!</div>
                </v-card-title>
                <v-card-actions>
                  <v-btn flat dark>Learn more</v-btn>
                  <v-img 
                    :src="require('~/assets/img/crowdos_logo.png')" 
                    name="welcomelogo"
                    height="25px" 
                    contain
                  ></v-img>
                </v-card-actions>
                
              </v-card>
            </v-flex>

            <v-flex xs12>
              <v-card color="cyan darken-2" class="white--text">
                <v-layout>
                  <v-flex xs4>
                    <v-img
                      src="https://lunardigitalassets.com/uploads/2018/05/eos.png"
                      height="125px"
                      name="item1"
                      contain
                    ></v-img>
                  </v-flex>
                  <v-flex xs8>
                    <v-card-title primary-title>
                      <div>
                        <div class="headline">Block.one EOS </div>
                        <div>ERC-20 ICO Smart Contract</div>
                        <div><small>225 checks, no issues reported.</small></div>
                      </div>
                    </v-card-title>
                  </v-flex>
                </v-layout>
                <v-divider light></v-divider>
                <v-card-actions class="pa-3">
                  $USD 5,250
                  <v-spacer></v-spacer>
                  <v-spacer></v-spacer>
                  <v-btn flat dark><v-icon>launch</v-icon> Check</v-btn>
                  <v-spacer></v-spacer>
                  <v-btn flat dark><v-icon>bug_report</v-icon> Report</v-btn>
                  <v-spacer></v-spacer>
                  <v-btn icon dark><v-icon>share</v-icon></v-btn>
                </v-card-actions>
              </v-card>
            </v-flex>
            <v-flex xs12 v-for="(t, i) in trees" :key="t.id">
              <v-card :class="{'purple': i % 2 === 0, 'indigo darken-2': i % 2 !== 0 }"  class="white--text">
                <v-layout>
                  <v-flex xs4>
                    <v-img
                      :src="t.picture"
                      :name="t.id"
                      height="125px"
                      contain
                    ></v-img>
                  </v-flex>
                  <v-flex xs8>
                    <v-card-title primary-title>
                      <div>
                        <div class="headline">{{ t.planter }} </div>
                        <div>ERC-20 ICO Smart Contract</div>
                        <div><small>{{ t.distance }} checks, no issues reported.</small></div>
                      </div>
                    </v-card-title>
                  </v-flex>
                </v-layout>
                <v-divider light></v-divider>
                <v-card-actions class="pa-3">
                  $USD 5,250
                  <v-spacer></v-spacer>
                  <v-spacer></v-spacer>
                  <v-btn flat dark><v-icon>launch</v-icon> Check</v-btn>
                  <v-spacer></v-spacer>
                  <v-btn flat dark><v-icon>bug_report</v-icon> Report</v-btn>
                  <v-spacer></v-spacer>
                  <v-btn icon dark><v-icon>share</v-icon></v-btn>
                </v-card-actions>
              </v-card>
            </v-flex>

          
          </v-layout>
      
        </v-container>

        <Verifications v-model="verify" :trees="trees"></Verifications>
        <v-bottom-nav :value="true">
            
            <v-btn @click="plant = true" flat>
              <span>Listing</span>
              <v-icon>add_circle</v-icon>
            </v-btn>
            <v-btn @click="verify = true" flat>
              <span>Messages</span>
              <v-icon>mail</v-icon>
            </v-btn>
            <v-btn @click="profile = true" flat>
              <span>Profile</span>
              <v-icon>account_circle</v-icon>
            </v-btn>
          </v-bottom-nav>
      
    </v-card>


  <!--<v-layout justify-center align-center fill-height v-if="!location">
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
      <Offers v-model="plant" :offers="offers"></Offers>
      <v-btn @click="plant = true" flat>
        <span>Listing</span>
        <v-icon>add_circle</v-icon>
      </v-btn>
      <v-badge color="red">
         <span slot="badge">!</span>
        <v-btn @click="verify = true" flat>
          <span>Messages</span>
          <v-icon>mail</v-icon>
        </v-btn>
      </v-badge>
            <v-btn @click="profile = true" flat>
        <span>Profile</span>
        <v-icon>account_circle</v-icon>
      </v-btn>
    </v-bottom-nav>
  </v-layout-->
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
      offers: 'offers',
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
