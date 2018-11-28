<template>
  <v-navigation-drawer permanent fixed dark app>
    <v-list class="pa-1">
      <v-list-tile avatar>
        <v-list-tile-avatar>
          <img :src="$store.state.user.picture">
        </v-list-tile-avatar>
        <v-list-tile-content>
          <v-list-tile-title>{{ $store.state.user.name }}</v-list-tile-title>
        </v-list-tile-content>
      </v-list-tile>
    </v-list>

    <v-list class="pt-0" dense>
      <v-divider></v-divider>

      <v-list-tile nuxt-link to="/">
        <v-list-tile-action>
          <v-icon>list</v-icon>
        </v-list-tile-action>
        <v-list-tile-content>
          <v-list-tile-title>Campaigns</v-list-tile-title>
        </v-list-tile-content>
      </v-list-tile>

      <v-list-tile nuxt-link to="/campaigns/create">
        <v-list-tile-action>
          <v-icon>list</v-icon>
        </v-list-tile-action>
        <v-list-tile-content>
          <v-list-tile-title>Create campaign</v-list-tile-title>
        </v-list-tile-content>
      </v-list-tile>

      <v-list-tile nuxt-link to="/submissions">
        <v-list-tile-action>
          <v-icon>bug_report</v-icon>
        </v-list-tile-action>
        <v-list-tile-content>
          <v-list-tile-title>My submissions</v-list-tile-title>
        </v-list-tile-content>
      </v-list-tile>
    </v-list>

    <v-card style="position: absolute; bottom: 0px; width: 100%">
      <v-img
        :src="require('~/assets/img/crowdos_logo.png')"
        name="welcomelogo"
        height="40px"
        contain
      />
      <v-card-text>
        <p class="text-xs-center">by team TokenTree</p>
      </v-card-text>
      <v-img :src="require('~/assets/tokentree.png')" name="tokentreelogo" contain/>
    </v-card>
  </v-navigation-drawer>
</template>
