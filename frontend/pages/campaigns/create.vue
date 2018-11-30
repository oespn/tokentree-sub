<template>
  <CreateCampaign :campaign="campaign" @created="onCreate"></CreateCampaign>
</template>

<script>
import CreateCampaign from "~/components/campaigns/Create";
export default {
  components: {
    CreateCampaign
  },
  middleware: ["auth"],
  data: () => ({
    campaign: {}
  }),
  methods: {
    onCreate(campaign) {
      this.$router.push(`/campaigns/${campaign.id}`)
    }
  }
};
</script>