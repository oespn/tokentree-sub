<template>
  <v-bottom-sheet :value="value" @input="x => this.$emit('input', x)">
    <v-list>
      <v-subheader>Verify a tree</v-subheader>
      <v-list-tile
        v-for="tree in trees" :key="tree.id"
        nuxt-link :to="`/trees/${tree.id}`"
        @click="sheet = false" avatar>
        <v-list-tile-avatar>
          <v-icon class="grey lighten-1 white--text">nature_people</v-icon>
        </v-list-tile-avatar>
        <v-list-tile-content>
          <v-list-tile-title>{{ user(tree) }}'s tree</v-list-tile-title>
          <v-list-tile-sub-title>{{ date(tree) }} days ago</v-list-tile-sub-title>
        </v-list-tile-content>
        <v-list-tile-action>
          {{ tree.distance }} km
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