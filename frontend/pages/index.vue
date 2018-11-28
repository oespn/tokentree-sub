<template>
  <v-layout column>
    <IntroCard class="mb-3"/>
    <IssueCard class="mb-3" v-for="issue in issues" :key="issue.id" :issue="issue"/>
    <v-btn fixed color="error" dark fab bottom right nuxt to="/campaigns/create">
      <v-icon>add</v-icon>
    </v-btn>
  </v-layout>
</template>

<script>
import { mapGetters, mapMutations } from "vuex";
import IssueCard from "~/components/IssueCard";
import IntroCard from "~/components/IntroCard";
export default {
  components: {
    IntroCard,
    IssueCard
  },
  computed: {
    issues() {
      return [
        {
          id: 1,
          picture: "https://lunardigitalassets.com/uploads/2018/05/eos.png",
          company: "Block.one EOS",
          title: "ERC-20 ICO Smart Contract",
          totalCheck: 89,
          totalIssues: 0,
          reporters: [
            { id: 1, picture: "https://randomuser.me/api/portraits/men/35.jpg" }
          ],
          reward: 5250
        }
      ];
    }
  }
};
</script>
