<template>
  <v-layout justify-center align-center fill-height column>
    <v-flex xs12 md8 lg6>
      <v-card class="mb-3">
        <img src="~assets/tokentree.png" width="400"/>
        <v-card-title >Offer (by Sponsor)</v-card-title>
        <v-divider/>
        <v-card-text>
          <v-text-field v-model="title" placeholder="Title"/>
          <v-text-field v-model="description" placeholder="Description"/>
          <v-text-field v-model="target" placeholder="Target"/>
          <v-text-field v-model="offer" placeholder="Offer Tokens"/>
          <v-text-field v-model="expires" placeholder="Expires DateTime"/>
        </v-card-text>
        <v-divider/>
        <v-card-actions>
          <v-spacer></v-spacer>
          <v-btn @click="postListing">Post Listing</v-btn>
        </v-card-actions>
      </v-card>
      <v-card>
        <v-card-title >Record a Vote (a check by User)</v-card-title>
        <v-card-text>
          <p>Once only</p>
          <v-text-field v-model="listingKey" placeholder="listing key" />
          <v-text-field v-model="vote" placeholder="true = pass / false = fail"/>
          <v-text-field v-model="comment" placeholder="If false => description of issue"/>
        </v-card-text>
        <v-divider/>
        <v-card-actions>
          <v-spacer></v-spacer>
          <v-btn @click="postCheck">Record check</v-btn>
        </v-card-actions>
      </v-card>
      <v-card>
        <v-card-title >Verification vote on fail</v-card-title>
        <v-card-text>
          <p>Can be called once only for each user <br/> and must have been a voter</p>
          <v-text-field v-model="validator_lat" placeholder="latitude" />
          <v-text-field v-model="validator_lng" placeholder="longitude"/>
          <v-text-field v-model="health" placeholder="health"/>
          <v-text-field v-model="comment" placeholder="comment"/>
        </v-card-text>
        <v-divider/>
        <v-card-actions>
          <v-spacer></v-spacer>
          <v-btn @click="validateVote">Validate Vote</v-btn>
        </v-card-actions>
      </v-card>


      <v-card>
        <v-card-title >Payout Contract (as System OR Creator)</v-card-title>
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
      title: null,
      description: null,
    radius: 500,
    offer: 150,
    expires: dateExpires,
    vote_key: null,

    validator_lat: null,

    health: 3,
    comment: ""
    
  }),
  methods: {

    postListing(){        
        //** implement scatter here */
        eos.transaction(
        {

          actions: [
            {
              account: account,
              name: 'addlisting',
              authorization: [{
                actor: useraccount,
                permission: 'active'
              }],
              data: {
                username: useraccount, // Company 
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
        this.vote_key = this.key;

        console.log("survived offer creation.  Set the plant details for speed in demo.");
    },  
    postCheck(){        
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
    },
    getVotes(){
      //eos.contract('testacc').then(acc => acc.plant("acc", this.lat, this.lat, now.toISOString() ));
      
    },
    validateVote(){   
      
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
  