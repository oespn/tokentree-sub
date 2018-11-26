<!-- AE:*** this need to be given the _id on a param and dispayed -->

<template>
<v-card>
        <v-toolbar dark>
          
          <v-toolbar-side-icon icon nuxt-link to="/reports"> <!--** AE: need a back action --> 
            <v-icon 
                dark
              >
               clear
            </v-icon>

          </v-toolbar-side-icon>
          <v-toolbar-title>
          
          <v-card-title class="title font-weight-regular">Review</v-card-title>

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
            <small>Review issue</small>
        </v-stepper-step>

                <v-stepper-content step="1">

          
            <v-form ref="form" class="form-page" v-model="valid" lazy-validation>
                
                <p>Reported by [John Leider] on <p>
                <h3>EOS</h3>
                <h4>Smart Contract</h4>
                
                <p>[ ISSUE REPORTED BOX ] 

                <p>{{radioissue}}</p>
                <v-radio-group v-model="radioissue">
      <div slot="label">Is this an <strong>Integrity issue</strong>? Reply with</div>
      <v-radio value="no">
        <div slot="label">No, we do not deem the report to be a <strong class="success--text">safe</strong></div>
      </v-radio>
      <v-radio value="yes">
        <div slot="label">Yes, thankyou for reporting.  We are awarding the <strong class="error--text">issue bounty</strong></div>
      </v-radio>
    </v-radio-group>

                <v-card v-show="radioissue=='yes'">
                  <p>Awarding the bounty will close this bounty listing. The widget will remain active.</p>
                  

                  <v-checkbox
                  v-model="checkbox"
                  :rules="[v => !!v || 'You must agree to continue!']"
                  label="Yes, I understand"
                  required
                  ></v-checkbox>
                </v-card>
                
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
          <small>Correspondence &amp; release</small>
        </v-stepper-step>
        <v-stepper-content step="2">
          <v-card
            class="mb-5"
          >
          <v-form ref="form" class="form-page" v-model="valid" lazy-validation>
                
              <v-textarea v-show="radioissue=='yes'"
                auto-grow
                v-model="description"
                :counter="4000"
                
                label="Additional notes for email to [John]"
                required
              ></v-textarea>
                
        
                
                <p>Bounty to release</p>
                <v-text-field
                  v-model.number="stake"
                  box
                  label="Staking"
                  type="number"
                  disabled
                ></v-text-field>

                <p>Plus Jackpot</p>
                <v-text-field
                  v-model.number="jackpot"
                  box
                  label="Staked by community Safe votes"
                  type="number"
                  disabled
                ></v-text-field>
                
            </v-form>
          
          </v-card>
  
          <v-btn
            color="pink"
            @click="e1 = 3"
          >
            RELESE BOUNTY &amp; JACKPOT
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
          <p>We just awarded a 500EOS bounty plus 325 Jackpot.
            Earn tokens on @crowdOS by checking our code. 
            [tweeted as @EOSio]  
          </p> 
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
      radioissue: null,
      stake: 500,
      jackpot: 325,
      
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