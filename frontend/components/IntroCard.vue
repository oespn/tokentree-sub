<template>
  <v-card v-if="!$store.state.company" color="blue-grey darken-2" class="white--text">
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
</template>
