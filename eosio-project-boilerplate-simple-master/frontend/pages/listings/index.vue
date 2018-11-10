<template>
  <v-layout justify-center align-center fill-height column>
    <v-flex xs12 md8 lg6>
      <v-card class="mb-3">
        <v-card-title >Listing (by Company)</v-card-title>
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
          <v-text-field v-model="health" placeholder="health"/>
          <v-text-field v-model="comment" placeholder="comment"/>
        </v-card-text>
        <v-divider/>
        <v-card-actions>
          <v-spacer></v-spacer>
          <v-btn @click="validateVote">Validate Vote</v-btn>
        </v-card-actions>
      </v-card>
    </v-flex>
  </v-layout>
</template>




<script>
//import eos from "~/lib/eos"


export default {
  data: () => ({
      title: null,
      description: null,
    offer: null,
    expires: null,
    vote: true,
    comment: ""
    
  }),
  methods: {
    /*postListing(){        
        //console.log(this.lat, this.lng);
        eos.contract('testacc').then(acc => acc.addoffer("acc", this.lat, this.radius.number(), "test", this.offer, this.expires.toISOString() ));
        //eos.contract('testacc').then(acc => acc.get)
        this.plant_lat = this.lat;
        this.plant_lng = this.lng;
        console.log("survived");
    },  
    postCheck(){        
        var now = new Date();
        eos.contract('testacc').then(acc => acc.plant("acc", this.lat, this.lat, now.toISOString() ));
        console.log("planted tree");
      //postOffer: {
        //lat,lng,radius,desc,tokens    
      //}
    },
    getVotes(){
      //eos.contract('testacc').then(acc => acc.plant("acc", this.lat, this.lat, now.toISOString() ));
      
    },
    validateVote(){   
        var now = new Date();     
        eos.contract('testacc').then(acc => acc.validate("acc", this.lat, now.toISOString(), comment,  health ));
        console.log("validated tree");
      //postOffer: {
        //lat,lng,radius,desc,tokens    
      //}
    }*/  
  }
}
</script>


<style scoped>
  .v-card__title { background-color: #b3d4fc; }
</style>
  