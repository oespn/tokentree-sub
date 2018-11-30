<template>
  <span :class="statusColor">{{ statusText }}</span>
</template>

<script>
export default {
  props: {
    campaign: {
      type: Object,
      required: true
    }
  },
  computed: {
    status() {
      if (this.campaign.closedAt) {
        return "closed";
      }
      return "open";
    },
    statusText() {
      return {
        closed: "Closed",
        open: "Ready to hack"
      }[this.status];
    },
    statusColor() {
      return {
        closed: "error",
        open: "success"
      }[this.status] + '--text';
    }
  }
};
</script>
