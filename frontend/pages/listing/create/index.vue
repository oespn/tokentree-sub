<template>
<v-card>
        <v-toolbar dark>
          
          <v-toolbar-side-icon icon nuxt-link to="/"> <!--** AE: need a back action --> 
            <v-icon 
                dark
              >
               clear
            </v-icon>

          </v-toolbar-side-icon>
          <v-toolbar-title>
          
          <v-card-title class="title font-weight-regular">New Bounty Listing</v-card-title>

          </v-toolbar-title>
          <v-spacer></v-spacer>

      </v-toolbar>
        <v-container
          id="scroll-target"
          style="max-height:700px"
          class="scroll-y"
          fluid

        >
<v-stepper v-model="e1" vertical>
  
        <v-stepper-step :complete="e1 > 1" editable step="1">
            Step 1
            <small>What is the bounty?</small>
        </v-stepper-step>

                <v-stepper-content step="1">

          
            <v-form ref="form" class="form-page" v-model="valid" lazy-validation>
                <v-text-field
                v-model="title"
                :rules="nameRules"
                :counter="150"
                label="Title"
                required
                ></v-text-field>
                <v-textarea
                auto-grow
                v-model="description"
                :counter="250"
                
                label="Description"
                required
                ></v-textarea>
                <v-select
                v-model="select"
                :items="items"
                :rules="[v => !!v || 'Hack type is required']"
                label="Hack Type"
                required
                ></v-select>
                <v-text-field
                v-model="target"
                placeholder="http://"
                label="Source code / Target URL"
                required
                ></v-text-field>
                <v-text-field
                  v-model.number="bounty"
                  box
                  label="Bounty EOS"
                  type="number"
                ></v-text-field>
            </v-form>

  
          <v-btn
            color="primary"
            @click="e1 = 2"
          >
            Continue
          </v-btn>
  
          <v-btn flat>Cancel</v-btn>
        </v-stepper-content>
  

  
        <v-stepper-step :complete="e1 > 2" step="2">Step 2
          <small>Conditions &amp; stake</small>
        </v-stepper-step>
        <v-stepper-content step="2">
          <v-card
            class="mb-5"
          >
          <v-form ref="form" class="form-page" v-model="valid" lazy-validation>
                <v-text-field
                  v-model.number="maxchecks"
                  box
                  label="Max checks"
                  type="number"
                ></v-text-field>
                 <v-menu
                    :close-on-content-click="false"
                    v-model="menu2"
                    :nudge-right="40"
                    lazy
                    transition="scale-transition"
                    offset-y
                    full-width
                    min-width="290px"
                  >
                  <v-text-field
                    slot="activator"
                    v-model="expiry"
                    label="Expires"
                    prepend-icon="event"
                    readonly
                  ></v-text-field>
                  <v-date-picker v-model="expiry" @input="expiryShowing = true"></v-date-picker>
                 </v-menu>
                <v-textarea
                auto-grow
                v-model="conditions"
                :counter="1000"
                
                label="Conditions"
                required
                > Default conditions for [hack type] will appear here </v-textarea>


                <v-text-field
                v-model="email"
                :rules="emailRules"
                label="Confirm security contact E-mail"
                required
                ></v-text-field>

                <h4>crowdOS cares about coders' time</h4>
                <p>All bounties are subject to our <a href="">fairness conditions</a></p>
                <v-checkbox
                v-model="checkbox"
                :rules="[v => !!v || 'You must agree to continue!']"
                label="Do you accept?"
                required
                ></v-checkbox>

            </v-form>
          
          </v-card>
  
          <v-btn
            color="pink"
            @click="e1 = 3"
            dark
          >
            Stake Bounty
          </v-btn>
        </v-stepper-content>

  
        <v-stepper-step step="3">Step 3
          <small>Share</small>
        </v-stepper-step>

        <v-stepper-content step="3">
          <v-card
            class="mb-5"
            color="grey lighten-1"
            height="200px"
          >
          <p>Just listed! a hot bounty on @crowdOS. Check it out 500 EOS up for grabs if you can find an issue. </p>
          </v-card>

  
          <v-btn flat>Done</v-btn>
        </v-stepper-content>
  
      <v-stepper-items>

  
  
  
      </v-stepper-items>
    </v-stepper>



        </v-container>
</v-card>

</template>


<script>
  //import axios from 'axios'

  export default {
    //** AE: not sure how to get this to be called
    // https://snipcart.com/blog/vuejs-transitions-animations
    transition (to, from) {
      if (!from) return 'slide-left'
      return +to.query.page < +from.query.page ? 'slide-right' : 'slide-left'
    },
    data: () => ({
      e1: 0,
      valid: true,
      title: '',
      description: '',
      conditions: '',
      bounty: null,
      expiry: null,
      expiryShowing: false,
      type: '',
      target: '',
      nameRules: [
        v => !!v || 'Name is required',
        v => (v && v.length <= 10) || 'Name must be less than 10 characters'
      ],
      email: '',
      emailRules: [
        v => !!v || 'E-mail is required',
        v => /.+@.+/.test(v) || 'E-mail must be valid'
      ],
      select: null,
      items: [
        'Smart contract integrity',
        'Security vulnerability',
        'Penteration breach',
        'Source code improvement'
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
      clear () {
        this.$refs.form.reset()
      }
    }
  }
</script>

<style scoped>
.form-page-x {
  position: absolute;
  z-index: 1;
  padding: .7em;
  width: 100%;
  top: 0;
  right: 0;
  top: 0;
}
</style>