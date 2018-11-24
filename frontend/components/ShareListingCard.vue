<template>
    <v-dialog
      v-model="listing"
      max-width="290"
    >
        <v-card>

    
        <v-img
          :src="listing.picture"
          aspect-ratio="2.75"
        ></v-img>

        <v-card-title primary-title>
          <div>
            <h3 class="headline mb-0">{{listing.title}}</h3>
            <div>I found this bounty on crowdos.app/url. #eso offering $500 for bugs.</div>
          </div>
        </v-card-title>

        <v-card-actions>
          <v-btn flat color="blue">Tweet! <v-icon>send</v-icon></v-btn>

        </v-card-actions>




        </v-card>
    </v-dialog>
</template>

<script>
export default {
  props: {
    listing: {
      type: Object,
      required: false
    }
  },
  dialog: true
}
</script>
