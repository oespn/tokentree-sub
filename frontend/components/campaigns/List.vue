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
            <CampaignStatus :campaign="campaign"/>--
            type:
            <strong>{{ campaign.type }}</strong>
            <span v-if="campaign.submissions">
              -- participants:
              <strong>{{ campaign.submissions }}</strong>
            </span>
            <span v-if="campaign.expiry">
              -- expires:
              <strong>{{ campaign.expiry }}</strong>
            </span>
          </v-list-tile-sub-title>
        </v-list-tile-content>

        <v-list-tile-action>
          {{ campaign.bounty }} EOS
          <v-list-tile-action-text>~{{ USDValue(campaign) }}USD</v-list-tile-action-text>
        </v-list-tile-action>
      </v-list-tile>
    </v-list>
  </v-card>
</template>

<script>
import CampaignStatus from "~/components/campaigns/Status";
import { mapGetters } from "vuex";
export default {
  components: { CampaignStatus },
  props: {
    campaigns: {
      type: Array,
      required: true
    }
  },
  computed: mapGetters({
    ratios: "exchange/ratios"
  }),
  methods: {
    USDValue(campaign) {
      return parseInt(campaign.bounty * this.ratios["eos-usd"], 10);
    }
  }
};
</script>
