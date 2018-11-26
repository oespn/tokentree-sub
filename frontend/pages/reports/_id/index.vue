<template>
  <v-layout column>
    <v-toolbar dark>
      <v-btn icon nuxt-link to="/reports">
        <v-icon dark>keyboard_backspace</v-icon>
      </v-btn>
      <v-toolbar-title>{{ report.planter }}'s report</v-toolbar-title>
    </v-toolbar>
    <img :src="report.picture" height="250px"/>
    <v-list two-line>
      <v-list-tile
        v-for="(menu, index) in menus" :key="index"
        nuxt-link :to="menu.action && menu.action.to" :href="menu.action && menu.action.href">
        <v-list-tile-action>
          <v-icon>{{ menu.icon }}</v-icon>
        </v-list-tile-action>
        <v-list-tile-content>
          <v-list-tile-title>{{ menu.title }}</v-list-tile-title>
          <v-list-tile-sub-title>{{ menu.subtitle }}</v-list-tile-sub-title>
        </v-list-tile-content>
        <v-list-tile-action v-if="menu.action">
          <v-icon>{{ menu.action.icon }}</v-icon>
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
    menus () {
      const sum = this.report.verifications.reduce((prev, { health }) => prev + health, 0)
      const avg = this.report.verifications.length
        ? parseInt((sum / this.report.verifications.length) * 100) / 100
        : null
      return [
        { icon: 'person', title: this.report.planter, subtitle: 'Reported by' },
        { icon: 'event', title: this.report.plantedAt, subtitle: 'Reported date' },
        { icon: 'money', title: '1000 EOS' , subtitle: 'bounty staked' },
        { icon: 'location_on', title: 'Hong Kong', subtitle: 'Origin', action: {
          icon: 'near_me',
          href: `https://maps.google.com?saddr=Current+Location&daddr=${this.report.lat},${this.report.lng}`
        } },
        { icon: 'verified_user', title: `${this.report.verifications.length} verification(s)`, subtitle: 'Number of verifications', action: {
          icon: 'chevron_right',
          to: `/reports/${this.report.id}/verifications`
        } }
      ]
    }
  }
}
</script>
