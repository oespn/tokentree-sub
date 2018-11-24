<template>
  <v-card>
    <v-layout>
      <v-flex xs5>
        <v-card-media
          :src="listing.picture"
          height="125px">
        </v-card-media>
      </v-flex>
      <v-flex xs7>
        <v-layout column justify-space-between fill-height>
          <v-card-title>{{ listing.companyname }}'s listing <v-icon>chevron_right</v-icon> $ {{ listing.bounty }}</v-card-title>
          <v-card-actions>
            <v-spacer></v-spacer>
            <v-btn nuxt-link :to="`/listings/${listing.id}`" color="primary" outline depressed>
              CHECK
              <v-icon>chevron_right</v-icon>
            </v-btn>
          </v-card-actions>
        </v-layout>
      </v-flex>
    </v-layout>
  </v-card>
</template>

<script>
export default {
  props: {
    listing: {
      type: Object,
      required: false
    }
  }
}
</script>
