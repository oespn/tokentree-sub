<template>
  <v-layout column>
    <v-toolbar dark>
      <v-btn icon nuxt-link :to="`/reports/${report.id}`">
        <v-icon dark>keyboard_backspace</v-icon>
      </v-btn>
      <v-toolbar-title>{{ report.planter }}'s report</v-toolbar-title>
    </v-toolbar>
    <v-list two-line>
      <v-list-tile
        v-for="(verification, index) in verifications" :key="index">
        <v-list-tile-content>
          <v-list-tile-title>{{ verification.verifier }}</v-list-tile-title>
          <v-list-tile-sub-title>{{ verification.comment }}</v-list-tile-sub-title>
        </v-list-tile-content>
        <v-list-tile-action>
          <v-list-tile-action-text>{{ verification.verifiedAt }}</v-list-tile-action-text>
          <span>{{ verification.health }}%</span>
        </v-list-tile-action>
      </v-list-tile>
    </v-list>
  </v-layout>
</template>

<script>
import { mapGetters } from 'vuex';
export default {
  computed: {
    ...mapGetters({
      map: 'treesMap'
    }),
    report () { return this.map[this.$route.params.id] },
    verifications () {
      return this.report.verifications
    }
  }
}
</script>
