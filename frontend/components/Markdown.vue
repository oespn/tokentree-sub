<template>
  <div v-html="text"></div>
</template>

<script>
import marked from "marked";
export default {
  props: {
    value: {
      type: String,
      required: true
    }
  },
  computed: {
    text () {
      return marked(this.value)
    }
  }
}
</script>
