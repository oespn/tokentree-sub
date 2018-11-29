<!-- AE:*** this need to be given the _id on a param and dispayed -->

<template>
  <v-stepper v-model="e1" vertical>
    <v-stepper-step :complete="e1 > 1" editable step="1">
      Step 1
      <small>Confirm selection</small>
    </v-stepper-step>

    <v-stepper-content step="1">
      <v-form ref="form" class="form-page" v-model="valid" lazy-validation>
        <p>Reporting as [John Leider] on</p>
        <p></p>
        <h3>EOS</h3>
        <h4>Smart Contract</h4>

        <p>{{radioissue}}</p>
        <v-radio-group v-model="radioissue">
          <div slot="label">
            Are there any
            <strong>Integrity issues</strong> to report?
          </div>
          <v-radio value="no">
            <div slot="label">
              No, vote as
              <strong class="success--text">safe</strong>
              <v-icon class="success--text">check</v-icon>
            </div>
          </v-radio>
          <v-radio value="yes">
            <div slot="label">
              Yes, I want to report an
              <strong class="error--text">issue</strong>
              <v-icon class="error--text">bug_report</v-icon>
            </div>
          </v-radio>
        </v-radio-group>

        <v-card v-show="radioissue=='yes'">
          <p>
            I have read &amp; understand what is considered a
            <strong>reportable issue</strong> for this bounty.
          </p>

          <v-checkbox
            v-model="checkbox"
            :rules="[v => !!v || 'You must agree to continue!']"
            label="Yes, this is reportable"
            required
          ></v-checkbox>
        </v-card>
      </v-form>

      <v-btn color="primary" @click="e1 = 2">Continue</v-btn>

      <v-btn flat>Cancel</v-btn>
    </v-stepper-content>

    <v-stepper-step :complete="e1 > 2" step="2">
      Step 2
      <small>Details and staking</small>
    </v-stepper-step>
    <v-stepper-content step="2">
      <v-card class="mb-5">
        <v-form ref="form" class="form-page" v-model="valid" lazy-validation>
          <v-textarea
            v-show="radioissue=='yes'"
            auto-grow
            v-model="description"
            :counter="4000"
            label="Describe the issue"
            required
          ></v-textarea>

          <v-text-field
            v-model="target"
            placeholder="https://"
            label="Source code Pull Request or Secret gist (optional)"
          ></v-text-field>

          <p>Required stake to vote</p>
          <v-text-field v-model.number="stake" box label="Staking" type="number" disabled></v-text-field>
        </v-form>
      </v-card>

      <v-btn color="pink" @click="e1 = 3" dark>Stake Vote</v-btn>
    </v-stepper-content>

    <v-stepper-step step="3">
      Step 3
      <small>Share rules</small>
    </v-stepper-step>

    <v-stepper-content step="3">
      <v-card class="mb-5" color="grey lighten-1" height="200px">
        <p v-show="radioissue=='yes'">
          Please respect the companies' security needs and keep this issue confidential.
          crowdOS Shield will ensure you are paid even if the company does not pay up.
          in this case the vote goes out to the community. All decision are final.
        </p>
        <p v-show="radioissue=='no'">
          I just checked @EOSio repo and voted it to be safe!
          Earn tokens on @crowdOS by having your say.
        </p>
      </v-card>

      <v-btn flat>Done</v-btn>
    </v-stepper-content>

    <v-stepper-items></v-stepper-items>
  </v-stepper>
</template>


<script>
//import axios from 'axios'

export default {
  middleware: ["auth"],
  //** AE: not sure how to get this to be called
  // https://snipcart.com/blog/vuejs-transitions-animations
  transition(to, from) {
    if (!from) return "slide-left";
    return +to.query.page < +from.query.page ? "slide-right" : "slide-left";
  },
  data: () => ({
    e1: 0,
    valid: true,
    radioissue: null,
    stake: 1,
    title: "",
    description: "",
    conditions: "",
    bounty: null,
    expiry: null,
    expiryShowing: false,
    type: "",
    target: "",
    nameRules: [
      v => !!v || "Name is required",
      v => (v && v.length <= 10) || "Name must be less than 10 characters"
    ],
    email: "",
    emailRules: [
      v => !!v || "E-mail is required",
      v => /.+@.+/.test(v) || "E-mail must be valid"
    ],
    select: null,
    items: [
      "Smart contract integrity",
      "Security vulnerability",
      "Penteration breach",
      "Source code improvement"
    ],
    checkbox: false
  }),

  methods: {
    /*submit () {
        if (this.$refs.form.validate()) {
          // Native form submission is not yet supported
          axios.post('/api/submit', {
            name: this.name,
            email: this.email,
            select: this.select,
            checkbox: this.checkbox
          })
        }
      },*/
    clear() {
      this.$refs.form.reset();
    }
  }
};
</script>

<style scoped>
.form-page-x {
  position: absolute;
  z-index: 1;
  padding: 0.7em;
  width: 100%;
  top: 0;
  right: 0;
  top: 0;
}
</style>