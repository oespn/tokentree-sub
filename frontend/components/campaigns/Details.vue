<template>
  <v-layout row justify-start>
    <CampaignStatus :campaign="campaign"/>
    <span class="separator"></span>
    type:&nbsp;
    <strong>{{ campaign.type }}</strong>

    <template v-if="campaign.submissions">
      <span class="separator"></span>
      participants:&nbsp;
      <strong>{{ campaign.submissions }}</strong>
    </template>

    <template v-if="campaign.expiry">
      <span class="separator"></span>
      expires:&nbsp;
      <strong>{{ campaign.expiry }}</strong>
    </template>

    <span class="separator"></span>
    <a :href="campaign.target" target="_blank" rel="no-follow">Link</a>

    <template v-if="campaign.website">
      <span class="separator"></span>
      <a :href="campaign.website" target="_blank" rel="no-follow">{{ campaign.website }}</a>
    </template>
  </v-layout>
</template>

<script>
import CampaignStatus from "~/components/campaigns/Status";
export default {
  components: { CampaignStatus },
  props: {
    campaign: {
      type: Object,
      required: true
    }
  }
};
</script>

<style scoped>
.separator {
  margin-left: 0.5em;
  margin-right: 0.5em;
}

.separator::before {
  content: "●";
  color: rgba(0, 0, 0, 0.15);
}
</style>
