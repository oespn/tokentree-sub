<template>
  <GmapMap
    :center="center"
    :zoom="10">
    <GmapMarker
      v-for="tree in trees" :key="tree.id"
      :position="{ lat: tree.lat, lng: tree.lng }"
      clickable
      @click="$emit('selected', tree)">
    </GmapMarker>
  </GmapMap>
</template>

<script>
export default {
  props: {
    trees: {
      type: Array,
      required: true
    },
    center: {
      type: Object,
      required: true
    }
  }
}
</script>

<style>
.vue-map-container {
  height: 100vh;
  height: 100%;
  width: 100vw;
  width: 100%;
}
</style>