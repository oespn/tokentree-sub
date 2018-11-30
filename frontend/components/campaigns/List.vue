<template>
  <v-card v-if="campaigns.length">
    <v-list two-line>
      <v-list-tile
        avatar
        v-for="campaign in campaigns"
        :key="campaign.id"
        :campaign="campaign"
        nuxt
        :to="`/campaigns/${campaign.id}`"
      >
        <v-list-tile-avatar>
          <img :src="campaign.picture">
        </v-list-tile-avatar>

        <v-list-tile-content>
          <v-list-tile-title v-html="campaign.title"></v-list-tile-title>
          <v-list-tile-sub-title>
            <CampaignDetails :campaign="campaign"/>
          </v-list-tile-sub-title>
        </v-list-tile-content>

        <v-list-tile-action>
          {{ campaign.bounty }} EOS
          <v-list-tile-action-text><USDValue :value="campaign.bounty" /></v-list-tile-action-text>
        </v-list-tile-action>
      </v-list-tile>
    </v-list>
  </v-card>
</template>

<script>
import CampaignDetails from "~/components/campaigns/Details";
import USDValue from "~/components/USDValue";
export default {
  components: { CampaignDetails, USDValue },
  props: {
    campaigns: {
      type: Array,
      required: true
    }
  }
};
</script>
