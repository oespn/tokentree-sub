<template>
  <v-card color="cyan darken-2" class="white--text">
    <v-layout>
      <v-flex xs4>
        <v-chip small label color="success" text-color="white">TRENDING</v-chip>
        <v-img :src="issue.picture" height="80px" name="item1" contain/>
      </v-flex>
      <v-flex xs8>
        <v-card-title primary-title>
          <div>
            <div class="headline">{{ issue.company }}</div>
            <div>{{ issue.title }}</div>
            <div>
              <small>{{ issue.totalCheck }} checks, {{ issue.totalIssues }} issues reported.</small>
            </div>
            <v-item-group multiple>
              <v-item v-for="reporter in issue.reporters" :key="reporter.id">
                <v-chip
                  slot-scope="{ active, toggle }"
                  :selected="active"
                  @click="toggle"
                  style="height:24px;width:24px;margin-left:-8px;"
                >
                  <v-avatar>
                    <img style="width:24px;height:24px;" :src="reporter.picture">
                  </v-avatar>
                </v-chip>
              </v-item>
            </v-item-group>
          </div>
        </v-card-title>
      </v-flex>
    </v-layout>
    <v-divider light></v-divider>
    <v-card-actions class="pa-3">
      $USD {{ issue.reward }}
      <v-spacer></v-spacer>
      <v-spacer></v-spacer>
      <v-btn flat dark>
        <v-icon>launch</v-icon>Check
      </v-btn>
      <v-spacer></v-spacer>
      <v-btn nuxt-link to="/submissions/create" flat dark>
        <v-icon>bug_report</v-icon>
        <v-icon>check</v-icon>Report
      </v-btn>

      <v-spacer></v-spacer>
      <v-btn icon dark>
        <v-icon>share</v-icon>
      </v-btn>
    </v-card-actions>
  </v-card>
</template>

<script>
export default {
  props: {
    issue: {
      type: Object,
      required: true
    }
  }
};
</script>
