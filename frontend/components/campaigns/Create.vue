<template>
  <v-container>
    <v-card>
      <v-card-title>
        <h1>Create a campaign</h1>
      </v-card-title>
      <v-divider/>
      <v-form ref="form">
        <v-stepper class="elevation-0" v-model="step" vertical>
          <v-stepper-step :complete="step > 1" editable :step="1">
            Step 1
            <small>Campaign information?</small>
          </v-stepper-step>
          <v-stepper-content :step="1">
            <v-text-field
              @change="fetchInfoFromGithub"
              v-model="campaign.target"
              label="Github URL"
              required
            ></v-text-field>
            <v-btn color="primary" @click="fetchInfoFromGithub">Next</v-btn>
          </v-stepper-content>

          <v-stepper-step :complete="step > 2" editable :step="2">
            Step 2
            <small>Description of the campaign?</small>
          </v-stepper-step>
          <v-stepper-content :step="2">
            <v-layout row wrap>
              <v-flex lg6>
                <v-text-field
                  v-model="campaign.title"
                  :rules="rules.name"
                  :counter="150"
                  label="Title"
                  required
                ></v-text-field>
              </v-flex>
              <v-flex lg6>
                <v-select
                  v-model="campaign.type"
                  :items="types"
                  :rules="rules.type"
                  label="Campaign type"
                  required
                ></v-select>
              </v-flex>
            </v-layout>
            <v-textarea auto-grow v-model="campaign.description" label="Description" required></v-textarea>
            <v-btn color="primary" @click="step += 1">Next</v-btn>
          </v-stepper-content>

          <v-stepper-step :complete="step > 3" editable :step="3">
            Step 3
            <small>Conditions?</small>
          </v-stepper-step>
          <v-stepper-content :step="3">
            <v-layout row wrap>
              <v-flex lg6>
                <v-text-field
                  v-model.number="campaign.maxChecks"
                  label="Max checks"
                  type="number"
                  hint="Maximum number of participation, let empty for no limit"
                ></v-text-field>
              </v-flex>
              <v-flex lg6>
                <v-menu lazy offset-y full-width min-width="290px">
                  <v-text-field slot="activator" v-model="campaign.expiry" label="Expires" readonly></v-text-field>
                  <v-date-picker v-model="campaign.expiry"></v-date-picker>
                </v-menu>
              </v-flex>
            </v-layout>
            <v-textarea
              auto-grow
              v-model="campaign.conditions"
              :counter="1000"
              label="Conditions"
              required
            >Default conditions for [hack type] will appear here</v-textarea>
            <v-btn color="primary" @click="step += 1">Next</v-btn>
          </v-stepper-content>

          <v-stepper-step :complete="step > 4" editable :step="4">
            Step 4
            <small>Reward?</small>
          </v-stepper-step>
          <v-stepper-content :step="4">
            <v-text-field v-model.number="campaign.bounty" label="Bounty (EOS)" type="number"></v-text-field>

            <v-text-field
              v-model="campaign.email"
              :rules="rules.email"
              label="Confirm security contact E-mail"
              required
            ></v-text-field>

            <h4>crowdOS cares about coders' time</h4>
            <p>
              All bounties are subject to our
              <a href="/TODO">fairness conditions</a>
            </p>
            <v-checkbox
              v-model="campaign.terms"
              :rules="rules.terms"
              label="Do you accept?"
              required
            ></v-checkbox>
            <v-btn color="primary" @click="submit">Submit</v-btn>
          </v-stepper-content>
        </v-stepper>
      </v-form>
    </v-card>
  </v-container>
</template>


<script>
import axios from "axios";
import { mapActions } from "vuex";
export default {
  props: {
    campaign: {
      type: Object,
      required: true
    }
  },
  data: () => ({
    step: 1
  }),
  computed: {
    rules: () => ({
      name: [v => !!v || "Name is required"],
      email: [
        v => !!v || "E-mail is required",
        v => /.+@.+/.test(v) || "E-mail must be valid"
      ],
      type: [v => !!v || "Campaign type is required"],
      terms: [v => !!v || "You must agree to continue!"]
    }),
    types: () => [
      // "Smart contract integrity",
      // "Security vulnerability",
      // "Penteration breach",
      // "Source code improvement"
      "Bug",
      "Feature",
      "Improvement",
      "Security",
      "Documentation",
      "Design",
      "Code review",
      "Other"
    ]
  },
  methods: {
    ...mapActions({
      create: "campaigns/create"
    }),
    async fetchInfoFromGithub() {
      if (!this.campaign.target) {
        return;
      }
      const issueApi = this.campaign.target.replace(
        "https://github.com",
        "https://api.github.com/repos"
      );
      const issue = (await axios.get(issueApi)).data;
      const repo = (await axios.get(issue.repository_url)).data;
      this.campaign.description = issue.body;
      this.campaign.title = issue.title;
      const labels = issue.labels.map(x => x.name.toLowerCase());
      debugger
      this.campaign.type = this.types.filter(
        x => labels.indexOf(x.toLowerCase()) >= 0
      )[0];
      this.campaign.picture = repo.owner.avatar_url
      this.campaign.website = repo.homepage
      this.step = 2;
    },
    submit() {
      if (!this.$refs.form.validate()) {
        return;
      }
      this.create({ campaign: this.campaign });
    }
  }
};
</script>
