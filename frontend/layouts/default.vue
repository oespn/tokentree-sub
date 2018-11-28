<template>
  <v-app>
    <Sidebar/>
    <Toolbar/>
    <v-content>
      <v-container fluid>
        <nuxt/>
      </v-container>
    </v-content>
  </v-app>
</template>

<script>
import Sidebar from "~/components/Sidebar";
import Toolbar from "~/components/Toolbar";
export default {
  components: {
    Sidebar,
    Toolbar
  }
};
</script>


<style lang="stylus">
@import '~vuetify/src/stylus/main';
</style>
