<template>
  <v-layout column>
    <IntroCard class="mb-3"/>
    <CampaignCard
      class="mb-3"
      v-for="campaign in campaigns"
      :key="campaign.id"
      :campaign="campaign"
    />
    <v-btn fixed color="error" dark fab bottom right nuxt to="/campaigns/create">
      <v-icon>add</v-icon>
    </v-btn>
  </v-layout>
</template>

<script>
import { mapState, mapActions, mapGetters } from "vuex";
import CampaignCard from "~/components/campaigns/Card";
import IntroCard from "~/components/IntroCard";
export default {
  components: {
    IntroCard,
    CampaignCard
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
