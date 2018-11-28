<template>
  <v-toolbar app dark>
    <v-toolbar-title>
      <v-img
        :src="require('~/assets/img/crowdos_logo.png')"
        name="welcomelogo"
        height="25px"
        width="100"
        contain
      />
    </v-toolbar-title>

    <v-spacer></v-spacer>

    <v-toolbar-items>
      <v-btn icon>
        <v-icon>search</v-icon>
      </v-btn>
      <v-menu>
        <v-btn icon slot="activator">
          <v-icon>notifications</v-icon>
        </v-btn>
        <Notifications/>
      </v-menu>
    </v-toolbar-items>

    <v-tabs v-if="$store.state.company" slot="extension" v-model="tab" grow dark align-with-title>
      <v-tabs-slider color="green"></v-tabs-slider>
      <v-tab>All</v-tab>
      <v-tab>Mine</v-tab>
    </v-tabs>
  </v-toolbar>
</template>

<script>
import Notifications from "~/components/Notifications";
export default {
  components: {
    Notifications
  }
};
</script>
