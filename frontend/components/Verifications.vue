<template>
  <v-bottom-sheet :value="value" @input="x => this.$emit('input', x)">
    <v-list>
      <v-subheader>You have been asked to vote on an issue</v-subheader>
      <v-list-tile
        v-for="tree in trees" :key="tree.id"
        nuxt-link :to="`/trees/${tree.id}`"
        @click="sheet = false" avatar>
        <v-list-tile-avatar>
          <v-icon class="grey lighten-1 white--text">how_to_vote</v-icon>
        </v-list-tile-avatar>
        <v-list-tile-content>
          <v-list-tile-title>{{ user(tree) }}'s report</v-list-tile-title>
          <v-list-tile-sub-title>{{ date(tree) }} days ago</v-list-tile-sub-title>
        </v-list-tile-content>
        <v-list-tile-action>
          {{ tree.distance }} votes
        </v-list-tile-action>
      </v-list-tile>
    </v-list>
  </v-bottom-sheet>
</template>

<script>
export default {
  props: {
    trees: {
      type: Array,
      required: true
    },
    value: {
      type: Boolean,
      default: false
    },
  },
  data: () => ({
    sheet: false
  }),
  methods: {
    date: tree => parseInt(Math.random() * 100) / 1,
    user: tree => tree.planter
  }
}
</script>