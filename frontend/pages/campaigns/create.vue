<template>
  <CreateCampaign :campaign="campaign"></CreateCampaign>
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
  })
};
</script>