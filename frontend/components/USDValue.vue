<template>
  <span>~${{ usd }}</span>
</template>

<script>
import { mapGetters } from "vuex";
export default {
  props: {
    value: {
      type: Number,
      required: true
    }
  },
  computed: {
    ...mapGetters({
      ratios: "exchange/ratios"
    }),
    usd() {
      return parseInt(this.value * this.ratios["eos-usd"], 10);
    }
  }
};
</script>
