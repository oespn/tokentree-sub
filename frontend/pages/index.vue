<template>
  <v-layout
    wrap
    style="height: 200px;"
  >

    <v-card>
        <v-toolbar dark>
          
          <v-toolbar-side-icon @click.native.stop="drawer = !drawer"> 
            <v-badge color="green" right overlap>
            <v-icon slot="badge" dark small >notifications</v-icon>
            <v-icon
              large
              dark
            >
              menu
            </v-icon>
            </v-badge>
          </v-toolbar-side-icon>
          
          <v-toolbar-title>
          <v-img 
            :src="require('~/assets/img/crowdos_logo.png')" 
            name="welcomelogo"
            height="25px" 
            width="100"
            contain
          ></v-img>
          </v-toolbar-title>
          <v-spacer></v-spacer>
        <v-btn icon>
          <v-icon>search</v-icon>
        </v-btn>
        </v-toolbar>
        <div v-if="listingSelected" class="listing-card">
        <ReportCard v-model="report" :listing="listingSelected"></ReportCard>
        </div>
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
                      width="100"
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
            <v-flex xs12 v-for="(t, i) in listings" :key="t.id" nuxt-link :to="`/listing/${t.id}`">
         
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
                        <div class="headline">{{ t.companyname }} </div>
                        <div>{{t.title}}</div>
                        <div><small>{{ t.target }} checks, no issues reported.</small></div>
                      </div>
                    </v-card-title>
                  </v-flex>
                </v-layout>
                <v-divider light></v-divider>
                
                <v-card-actions class="pa-3">
                  $USD {{t.bounty}}
                  <v-spacer></v-spacer>
                  <v-spacer></v-spacer>
                  <v-btn flat dark><v-icon>launch</v-icon> Check</v-btn>
                  <v-spacer></v-spacer>
                  <v-btn @click="listingReport(t)" flat dark><v-icon>bug_report</v-icon> Report</v-btn>
                  <v-spacer></v-spacer>
                  <v-btn icon dark><v-icon>share</v-icon></v-btn>
                </v-card-actions>
              </v-card>
            </v-flex>

          
          </v-layout>
      
     <Verifications v-model="verify" :trees="trees"></Verifications>
        <v-bottom-nav :value="true">
            <!-- retire this? -->
            <v-btn nuxt-link to="/listingcreate" flat>
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
        </v-container>

       
      
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



    <v-navigation-drawer
      v-model="drawer"
      absolute
      temporary
      dark
    >
      <v-list class="pa-1">
        <v-list-tile avatar>
          <v-list-tile-avatar>
            <img src="https://randomuser.me/api/portraits/men/85.jpg">
          </v-list-tile-avatar>

          <v-list-tile-content>
            <v-list-tile-title>John Leider</v-list-tile-title>
          </v-list-tile-content>
        </v-list-tile>
      </v-list>

      <v-list class="pt-0" dense>
        <v-divider></v-divider>

        <v-list-tile @click="verify=true">
          <v-list-tile-action>
            <v-badge color="green" right overlap>
            <v-icon slot="badge" dark small >notifications</v-icon>
            <v-icon>question_answer</v-icon>
            </v-badge>
          </v-list-tile-action>
          <v-list-tile-content>
            <v-list-tile-title>Notifications </v-list-tile-title>
          </v-list-tile-content>
        </v-list-tile>
        <v-list-tile
          v-for="item in items"
          :key="item.title"
          @click="drawer=false"
    
          nuxt-link :to="item.link"
        >
          <v-list-tile-action>
            <v-icon>{{ item.icon }}</v-icon>
          </v-list-tile-action>

          <v-list-tile-content>
            <v-list-tile-title>{{ item.title }}</v-list-tile-title>
          </v-list-tile-content>
        </v-list-tile>
        <v-list-tile nuxt-link to="/listingcreate" @click="drawer=false">
            <v-list-tile-action>
              <v-icon>add_circle</v-icon>
            </v-list-tile-action>
            <v-list-tile-content>
            <v-list-tile-title>Test page </v-list-tile-title>
          </v-list-tile-content>


      </v-list-tile>
      </v-list>
      

       
      <v-divider></v-divider>
      <v-list>

      </v-list>
      <v-list>

      </v-list>
      <v-img 
                :src="require('~/assets/img/crowdos_logo.png')" 
                name="welcomelogo"
                height="40px"
                contain
              ></v-img>
      <v-list>
      </v-list>
      <v-list> by team TokenTree
      </v-list>
      <v-list>
      </v-list>
           <v-img 
                :src="require('~/assets/tokentree.png')" 
                name="tokentreelogo"
                height="40px"
                contain
              ></v-img>

    </v-navigation-drawer>

  </v-layout>
</template>

<script>
import { mapGetters, mapMutations } from 'vuex'
import Router from 'vue-router'
import Map from '~/components/Map'
import Verifications from '~/components/Verifications'
import TreeCard from '~/components/TreeCard'
import ListingCard from '~/components/ListingCard'
import ReportCard from '~/components/ReportCard'

export default {
  components: {
    Map,
    Verifications,
    TreeCard,
    ListingCard,
    ReportCard
  },
  data: () => ({
    verify: false,
    plant: false,
    report: false,
    treeSelected: null,
    listingSelected: null,

    drawer: null,
        items: [
          { title: 'Add Listing', icon: 'add_circle', link: '/listingcreate', click: 'drawer=true' },
          { title: 'Messages', icon: 'question_answer', link: '', click: 'verify = true' },
          { title: 'Home', icon: 'dashboard', link: '/',  click: 'drawer=true' },
          { title: 'About', icon: 'question_answer', link: '',  click: 'drawer=true' }
        ]

  }),
  computed: {
    ...mapGetters({
      trees: 'trees',
      listings: 'listings',
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
    },
    listingReport (listing) {
      this.listingSelected = listing;
      this.report = true;
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

.listing-card {
  position: absolute;
  z-index: 1;
  padding: .7em;
  width: 100%;
  top: 0;
  right: 0;
  top: 0;
}

.report-card {
  position: absolute;
  z-index: 1;
  padding: .7em;
  width: 100%;
  top: 0;
  right: 0;
  top: 0;
}


</style>
