<template>
  <v-layout
    wrap
    style="height: 200px;"
  >

    <v-card>

        <div style="height: 56px; position: absolute; bottom:70px;right:30px;">
    
                <v-fab-transition>
                  
                  <v-btn
                    v-show="canAddListing()"
                    color="pink"
                    dark
                    absolute
                    bottom
                    right
                    fab
                    nuxt-link to="/listing/create" @click="drawer=false"
                    transition="slide-right"
                  >
                    <v-icon>add</v-icon>
                  </v-btn>
                  
                </v-fab-transition>
              </div>

        <v-toolbar dark 
          :extension-height="accountCompany ? 30:1"
          >
          
          <v-toolbar-side-icon @click.native.stop="drawer = !drawer"> 

            <v-badge color="green" right overlap v-show="isNotification()">
              <v-icon slot="badge" dark small v-show="isNotification()" >notifications</v-icon>
              <v-icon
                dark
              >
                menu
              </v-icon>
            </v-badge>
            <v-icon 
                v-show="!isNotification()"
                dark
              >
                menu
            </v-icon>


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

        <v-tabs
          v-show="accountCompany==true"
          slot="extension"
          v-model="tab"
          grow
          dark
          align-with-title
          :height="accountCompany ? 30:1"
        >
          <v-tabs-slider color="green"></v-tabs-slider>

          <v-tab>
            All
          </v-tab>
          <v-tab>
            Mine
          </v-tab>
        </v-tabs>



        </v-toolbar>
        <div v-if="listingSelected" class="listing-card">
        <ShareListingCard v-model="share" :listing="listingSelected"></ShareListingCard>
        </div>
        <v-container
          id="scroll-target"
          style="max-height:700px"
          class="scroll-y"
          fluid
          grid-list-lg
        >

          <v-layout row wrap v-scroll>
              
          <v-tabs-items v-model="tab">
          <v-tab-item>
            
            <v-flex xs12 >
              <v-card v-show="!accountCompany" color="blue-grey darken-2" class="white--text">
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

              <v-card v-show="accountCompany" color="blue-grey darken-2" class="white--text">
                <v-card-title primary-title>
                  <div class="headline">Improve security and exposure</div>

                  <div>Grow your brand while increasing security!</div>
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
                    <v-chip small label color="success" text-color="white">
                            TRENDING  
                          </v-chip>
                    <v-img
                      src="https://lunardigitalassets.com/uploads/2018/05/eos.png"
                      height="80px"
                      name="item1"
                      contain
                    ></v-img>
                  </v-flex>
                  <v-flex xs8>
                    <v-card-title primary-title>
                      <div>
                        <div class="headline">Block.one EOS </div>
                        <div>ERC-20 ICO Smart Contract  
                           
                        </div>
                        <div><small>89 checks, no issues reported.</small></div>
                        <v-item-group multiple>
                        <v-item
                          v-for="n in 3"
                          :key="n"
                        >
                          <v-chip
                            slot-scope="{ active, toggle }"
                            :selected="active"
                            @click="toggle"
                            style="height:24px;width:24px;margin-left:-8px;"
                          >
                          <v-avatar><img style="width:24px;height:24px;" src='https://randomuser.me/api/portraits/men/35.jpg'>
                          </v-avatar>
                          </v-chip>
                        </v-item>
                      </v-item-group>
                      </div>
                    </v-card-title>
                  </v-flex>
                </v-layout>
                <v-divider light></v-divider>
                <v-card-actions class="pa-3">
                  $USD 5,250
                  <v-spacer></v-spacer>
                  <v-spacer></v-spacer>
                  <v-btn flat dark  ><v-icon>launch</v-icon> Check</v-btn>
                  <v-spacer></v-spacer>
                   <v-btn nuxt-link to="/myreports/create" flat dark><v-icon>bug_report</v-icon><v-icon>check</v-icon>Report</v-btn>
                 
                  <v-spacer></v-spacer>
                  <v-btn icon dark><v-icon>share</v-icon></v-btn>
                </v-card-actions>
              </v-card>
            </v-flex>
            <v-flex xs12 v-for="(t, i) in listings" :key="t.id" nuxt-link :to="`/listing/${t.id}`">
         
              <v-card :class="{'purple': i % 2 === 0, 'indigo darken-2': i % 2 !== 0 }"  class="white--text">
                <v-layout>
                  <v-flex xs4>
                      <v-chip small label color="warning" text-color="white">
                            LAST DAYS  
                          </v-chip>
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
                  <v-btn flat dark @click="openLink(t)" ><v-icon>launch</v-icon> Check</v-btn>
                  <v-spacer></v-spacer>
                  <v-btn @click="listingReport(t)" nuxt-link to="/myreports/create" flat dark><v-icon>bug_report</v-icon><v-icon>check</v-icon>Report</v-btn>
                  <v-spacer></v-spacer>
                  <v-btn icon dark @click="listingShare(t)" ><v-icon>share</v-icon></v-btn>
                </v-card-actions>
              </v-card>

            </v-flex>
          </v-tab-item>
          <v-tab-item>
            <v-flex xs12>
              <v-card color="blue-grey darken-2" class="white--text">
                <v-card-title primary-title>
                  <div class="headline">Get the security of the crowd</div>

                  <div>Incentise code checking by listing a bounty!</div>
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
                  <v-btn flat dark  ><v-icon>widgets</v-icon> View </v-btn>
                  <v-spacer></v-spacer>
                  <v-btn flat dark><v-icon>code</v-icon> Widget</v-btn>
                  <v-spacer></v-spacer>
                  <v-btn icon dark><v-icon>share</v-icon></v-btn>
                </v-card-actions>
              </v-card>
            

              <v-card style="height:250px" v-show="mylistingsCount()<3">
                <v-img 
                      :src="require('~/assets/img/arrow_action.png')" 
                      name="arrowInstruction"
                      width="150"
                      style="position:absolute;right:70px;bottom:70px"

                      contain
                ></v-img>
              </v-card>
              
            </v-flex>
            

          </v-tab-item>
          </v-tabs-items>
 
          
          </v-layout>
      
          <Verifications v-model="verify" :trees="trees"></Verifications>
     <!--
        <v-bottom-nav :value="true">
             retire this? 
            <v-btn nuxt-link to="/listing/create" flat>
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
          -->

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
        <v-list-tile @click="accountCompany=!accountCompany; drawer=false;" small>
            <v-list-tile-action>
              <v-icon>how_to_reg</v-icon>
            </v-list-tile-action>
            <v-list-tile-content>
            <v-list-tile-title>{{getMode()}}
               </v-list-tile-title>
               <span class="caption"> Switch to {{getModeSwitchTo()}}</span>
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

        <v-list-tile nuxt-link to="/" @click="drawer=false">
            <v-list-tile-action>
              <v-icon>list</v-icon>
            </v-list-tile-action>
            <v-list-tile-content>
            <v-list-tile-title>All listings </v-list-tile-title>
          </v-list-tile-content>
        </v-list-tile>


        <v-list-tile v-show="accountCompany"  nuxt-link to="/reports" @click="drawer=false">
            <v-list-tile-action>
              <v-icon>bug_report</v-icon>
            </v-list-tile-action>
            <v-list-tile-content>
            <v-list-tile-title>Bug Reports</v-list-tile-title>
          </v-list-tile-content>
        </v-list-tile>

        <v-list-tile v-show="!accountCompany" nuxt-link to="/myreports" @click="drawer=false">
            <v-list-tile-action>
              <v-icon>bug_report</v-icon>
            </v-list-tile-action>
            <v-list-tile-content>
            <v-list-tile-title>My Reports</v-list-tile-title>
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

        
      </v-list>
      

       
      <v-divider></v-divider>
      <v-list>

      </v-list>
      <v-list>

      </v-list>
      
      <v-list>
      </v-list>
      <v-list> 
        
      </v-list>
      <v-list>
      </v-list>

        <v-list>
      </v-list>
        <v-list>
      </v-list>
        <v-list>
      </v-list>

        <v-list>
      </v-list>
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

      <v-card>
        <v-card-text>
        <p class="text-xs-center">by team TokenTree</p>
        </v-card-text>
      </v-card>

           <v-img 
                :src="require('~/assets/tokentree.png')" 
                name="tokentreelogo"
                width="100%"
                style="position: absolute;bottom: 0px;"
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
import ShareListingCard from '~/components/ShareListingCard'
export default {
  components: {
    Map,
    Verifications,
    TreeCard,
    ListingCard,
    ReportCard,
    ShareListingCard
  },
  data: () => ({
    accountCompany: false,
    tab: null,
    verify: false,
    plant: false,
    report: false,
    share: false,
    treeSelected: null,
    listingSelected: null,

    addhidden: false,
    drawer: null,
        items: [
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
    openLink (listing){
      window.location.href = 'https://vc.eos.io';
    },
    listingReport (listing) {
      this.listingSelected = listing;
      this.report = true;
    },
    listingShare (listing) {
      this.listingSelected = listing;
      this.share = true;
    },
    isNotification (){
      return !this.accountCompany; 
    },
    canAddListing (){
      return this.accountCompany; 
    },
    getMode(){
      return this.accountCompany ? "Company" : "Coder";
    },
    getModeSwitchTo(){
      return !this.accountCompany ? "Company" : "Coder";
    },
    mylistingsCount(){
      return 0;
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
