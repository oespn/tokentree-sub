<template>
  <v-layout column>
    <IntroCard class="mb-3"/>
    <CampaignList :campaigns="campaigns"/>
    <v-btn fixed color="error" dark fab bottom right nuxt to="/campaigns/create">
      <v-icon>add</v-icon>
    </v-btn>
  </v-layout>
</template>

<script>
import { mapState, mapActions, mapGetters } from "vuex";
import CampaignList from "~/components/campaigns/List";
import IntroCard from "~/components/IntroCard";
export default {
  components: {
    IntroCard,
    CampaignList
  },
  computed: mapGetters({
    campaigns: "campaigns/all"
  }),
  methods: mapActions({
    fetchAllCampaigns: "campaigns/fetchAll"
  }),
  mounted() {
    this.fetchAllCampaigns();
  }
};
</script>
