<template>
  <v-layout column fill-height align-center justify-center>
    <v-card>
      <v-card-title>Login</v-card-title>
      <v-card-text>
        <v-btn @click="connect()">Connect with Github</v-btn>
      </v-card-text>
    </v-card>
  </v-layout>
</template>

<script>
import { mapActions, mapGetters } from "vuex";
export default {
  computed: mapGetters({
    user: "session/user"
  }),
  methods: mapActions({
    connect: "session/signUserInGithub"
  }),
  watch: {
    user() {
      this.$router.push(this.$route.query.redirect || "/");
    }
  }
};
</script>
