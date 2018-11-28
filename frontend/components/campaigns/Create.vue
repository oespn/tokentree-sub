<template>
  <v-form ref="form">
    <v-stepper v-model="step" vertical>
      <v-stepper-step :complete="step > 1" editable :step="1">
        Step 1
        <small>What is the bounty?</small>
      </v-stepper-step>

      <v-stepper-content :step="1">
        <v-layout row wrap>
          <v-flex lg6>
            <v-text-field
              box
              v-model="campaign.title"
              :rules="rules.name"
              :counter="150"
              label="Title"
              required
            ></v-text-field>
          </v-flex>
          <v-flex lg6>
            <v-select
              box
              v-model="campaign.type"
              :items="types"
              :rules="rules.type"
              label="Hack Type"
              required
            ></v-select>
          </v-flex>
        </v-layout>
        <v-textarea
          box
          auto-grow
          v-model="campaign.description"
          :counter="250"
          label="Description"
          required
        ></v-textarea>
        <v-text-field
          box
          v-model="campaign.target"
          placeholder="http://"
          label="Source code / Target URL"
          required
        ></v-text-field>
        <v-text-field box v-model.number="campaign.bounty" label="Bounty (EOS)" type="number"></v-text-field>
        <v-btn color="primary" @click="step = 2">Continue</v-btn>
      </v-stepper-content>

      <v-stepper-step :complete="step > 2" :step="2">
        Step 2
        <small>Conditions &amp; stake</small>
      </v-stepper-step>
      <v-stepper-content :step="2" pa1>
        <v-layout row wrap>
          <v-flex lg6>
            <v-text-field
              box
              v-model.number="campaign.maxChecks"
              label="Max checks"
              type="number"
              hint="Maximum number of participation, let empty for no limit"
            ></v-text-field>
          </v-flex>
          <v-flex lg6>
            <v-menu lazy offset-y full-width min-width="290px">
              <v-text-field box slot="activator" v-model="campaign.expiry" label="Expires" readonly></v-text-field>
              <v-date-picker v-model="campaign.expiry"></v-date-picker>
            </v-menu>
          </v-flex>
        </v-layout>
        <v-textarea
          box
          auto-grow
          v-model="campaign.conditions"
          :counter="1000"
          label="Conditions"
          required
        >Default conditions for [hack type] will appear here</v-textarea>

        <v-text-field
          box
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
        <v-checkbox v-model="campaign.terms" :rules="rules.terms" label="Do you accept?" required></v-checkbox>

        <v-btn color="primary" @click="submit()" dark>Submit</v-btn>
      </v-stepper-content>
    </v-stepper>
  </v-form>
</template>


<script>
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
      name: [
        v => !!v || "Name is required",
        v => (v && v.length <= 10) || "Name must be less than 10 characters"
      ],
      email: [
        v => !!v || "E-mail is required",
        v => /.+@.+/.test(v) || "E-mail must be valid"
      ],
      type: [v => !!v || "Hack type is required"],
      terms: [v => !!v || "You must agree to continue!"]
    }),
    types: () => [
      "Smart contract integrity",
      "Security vulnerability",
      "Penteration breach",
      "Source code improvement"
    ]
  },
  methods: {
    ...mapActions({
      create: "campaigns/create"
    }),
    submit() {
      if (!this.$refs.form.validate()) {
        this.step = 1;
        return;
      }
      this.create({ campaign: this.campaign });
    }
  }
};
</script>
