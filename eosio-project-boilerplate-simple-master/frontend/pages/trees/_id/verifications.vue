<template>
  <v-layout column>
    <v-toolbar>
      <v-btn icon nuxt-link :to="`/trees/${tree.id}`">
        <v-icon>keyboard_backspace</v-icon>
      </v-btn>
      <v-toolbar-title>{{ tree.planter }}'s tree</v-toolbar-title>
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
    tree () { return this.map[this.$route.params.id] },
    verifications () {
      return this.tree.verifications
    }
  }
}
</script>
