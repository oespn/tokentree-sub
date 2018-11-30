<template>
  <v-card v-if="campaign">
    <v-card-text>
      <v-layout row>
        <v-avatar class="mr-2">
          <v-img :src="campaign.picture"/>
        </v-avatar>
        <header>
          <h1 class="headline">{{ campaign.title }}</h1>
          <CampaignDetails :campaign="campaign"/>
        </header>
        <v-spacer/>
        <span class="text-xs-right">
          <span class="headline">{{ campaign.bounty }} EOS</span>
          <br>
          <span class="subheading">
            <USDValue :value="campaign.bounty"/>
          </span>
        </span>
      </v-layout>
    </v-card-text>
    <v-divider/>
    <v-card-text>
      <h2 class="subheading">Description</h2>
      <Markdown :value="campaign.description"></Markdown>
    </v-card-text>
  </v-card>
</template>

<script>
import { mapState, mapActions, mapGetters } from "vuex";
import CampaignDetails from "~/components/campaigns/Details";
import USDValue from "~/components/USDValue";
import Markdown from "~/components/Markdown";
export default {
  components: {
    CampaignDetails,
    USDValue,
    Markdown
  },
  computed: {
    ...mapGetters({
      campaigns: "campaigns/all"
    }),
    campaign() {
      return this.campaigns.filter(x => x.id === this.$route.params.id)[0];
    }
  },
  methods: mapActions({
    fetchCampaign: "campaigns/fetch"
  }),
  mounted() {
    this.fetchCampaign(this.$route.params.id);
  }
};
</script>
