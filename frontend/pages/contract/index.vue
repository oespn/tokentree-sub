<template>
  <v-layout justify-center align-center fill-height column>
    <v-flex xs12 md8 lg6>
      <v-card class="mb-3">
        <img src="~assets/tokentree.png" width="400"/>
        <v-card-title >Offer (by Sponsor)</v-card-title>
        <v-divider/>
        <v-card-text>
          <v-flex xs12>
            <v-text-field xs6 v-model="lat" placeholder="Latitude" />
            <v-text-field xs6 v-model="lng" placeholder="Longitude"/>
          </v-flex>
          <v-text-field v-model="radius" placeholder="Radius (metres)"/>
          <v-text-field v-model="offer" placeholder="Offer Tokens"/>
          <v-text-field v-model="expires" placeholder="Expires DateTime"/>
        </v-card-text>
        <v-divider/>
        <v-card-actions>
          <v-spacer></v-spacer>
          <v-btn @click="postOffer">Post Offer</v-btn>
        </v-card-actions>
      </v-card>
      <v-card>
        <v-card-title >Plant a tree (as User)</v-card-title>
        <v-card-text>
          <p>Once only</p>
          <v-text-field v-model="plant_lat" placeholder="latitude" />
          <v-text-field v-model="plant_lng" placeholder="longitude"/>
        </v-card-text>
        <v-divider/>
        <v-card-actions>
          <v-spacer></v-spacer>
          <v-btn @click="plantTree">Plant tree</v-btn>
        </v-card-actions>
      </v-card>
      <v-card>
        <v-card-title >Verify tree (as User.Validator)</v-card-title>
        <v-card-text>
          <p>Can be called many times by same or various</p>
          <v-text-field v-model="validator_lat" placeholder="latitude" />
          <v-text-field v-model="validator_lng" placeholder="longitude"/>
          <v-text-field v-model="health" placeholder="health"/>
          <v-text-field v-model="comment" placeholder="comment"/>
        </v-card-text>
        <v-divider/>
        <v-card-actions>
          <v-spacer></v-spacer>
          <v-btn @click="validateTree">Validate tree</v-btn>
        </v-card-actions>
      </v-card>


      <v-card>
        <v-card-title >Payout Contract (as User.Validator)</v-card-title>
        <v-card-text>
          <p>Validators and the Planter receives funds</p>

        </v-card-text>
        <v-divider/>
        <v-card-actions>
          <v-spacer></v-spacer>
          <v-btn @click="payout">Payout</v-btn>
        </v-card-actions>
      </v-card>

    </v-flex>
  </v-layout>
</template>




<script>
import eos from "~/lib/eos"
import moment from "moment"

var now = new Date();
var dateExpires = new Date(now.getFullYear(), now.getMonth()+3, now.getDate());

var account = 'atokentree';
var useraccount = 'alice';

export default {
  data: () => ({
    lat: 150.678,
    lng: -28.345,
    radius: 500,
    offer: 150,
    expires: dateExpires,
    plant_lat: null,
    plant_lng: null,
    validator_lat: null,
    validator_lng: null,
    health: 3,
    comment: ""
    
  }),
  methods: {

    postOffer(){        
        console.log(this.lat, this.lng);

        eos.transaction(
        {

          actions: [
            {
              account: account,
              name: 'addoffer',
              authorization: [{
                actor: useraccount,
                permission: 'active'
              }],
              data: {
                username: useraccount, // Sponsor
                geo: this.lat,
                radius: this.radius,
                description: "Test",
                offervalue: this.offer ,
                days: 90
              }
            }
          ]
        }
        // options -- example: {broadcast: false}
        )

        //eos.contract(account).then(acc => acc.addoffer("acc", this.lat, this.radius.number(), "test", this.offer )); //, this.expires.toISOString() ));
        //eos.contract('testacc').then(acc => acc.get)
        this.plant_lat = this.lat;
        this.plant_lng = this.lng;
        console.log("survived offer creation.  Set the plant details for speed in demo.");
    },  
    plantTree(){        
        var now = new Date();
        //** for demo: using Lat as an index */
      eos.transaction(
        {

          actions: [
            {
              account: account,
              name: 'plant',
              authorization: [{
                actor: useraccount,
                permission: 'active'
              }],
              data: {
                username: useraccount, // planter
                geo: this.lat,
                treepatchkey: this.lat
              }
            }
          ]
        }
        // options -- example: {broadcast: false}
        )
        //eos.contract(account).then(acc => acc.plant("acc", this.lat, this.lat ));
        console.log("planted tree");
      //postOffer: {
        //lat,lng,radius,desc,tokens    
      //}
    },
    getTrees(){
      //eos.contract('testacc').then(acc => acc.plant("acc", this.lat, this.lat, now.toISOString() ));
      
    },
    validateTree(){   
      
        eos.transaction(
        {

          actions: [
            {
              account: account,
              name: 'validate',
              authorization: [{
                actor: useraccount,
                permission: 'active'
              }],
              data: {
                username: useraccount, // planter
                treepatchkey: this.lat,
                comment: this.comment,
                health: Number(this.health)
              }
            }
          ]
        }
        // options -- example: {broadcast: false}
        )

        //eos.contract(account).then(acc => acc.validate("acc", this.lat, comment,  health ));
        console.log("validated tree");
      //postOffer: {
        //lat,lng,radius,desc,tokens    
      //}
    },
    payout(){
      //payout
      eos.transaction(
        {

          actions: [
            {
              account: account,
              name: 'payout',
              authorization: [{
                actor: useraccount,
                permission: 'active'
              }],
              data: {
                username: useraccount, // planter
                treepatchkey: this.lat
              }
            }
          ]
        }
        // options -- example: {broadcast: false}
        )
    console.log("payout success!");
    }  
  }
}
</script>


<style scoped>
  .v-card__title { background-color: #b3d4fc; }
</style>
  