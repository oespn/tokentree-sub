<template>
  <v-app>
    <Sidebar :user="user"/>
    <Toolbar :user="user"/>
    <v-content>
      <v-container fluid>
        <nuxt/>
      </v-container>
    </v-content>
  </v-app>
</template>

<script>
import { mapGetters } from "vuex";
import Sidebar from "~/components/Sidebar";
import Toolbar from "~/components/Toolbar";
export default {
  components: {
    Sidebar,
    Toolbar
  },
  computed: mapGetters({
    user: "session/user"
  })
};
</script>


<style lang="stylus">
@import '~vuetify/src/stylus/main';
</style>
