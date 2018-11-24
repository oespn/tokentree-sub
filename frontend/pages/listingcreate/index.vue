<template>

<v-stepper v-model="e1" vertical>
  
        <v-stepper-step :complete="e1 > 1" editable step="1">
            Step 1
            <small>Summarize if needed</small>
        </v-stepper-step>

                <v-stepper-content step="1">
          <v-card
            class="mb-5"
            
          >
          
            <v-form ref="form" class="form-page" v-model="valid" lazy-validation>
                <v-text-field
                v-model="name"
                :rules="nameRules"
                :counter="10"
                label="Name"
                required
                ></v-text-field>
                <v-text-field
                v-model="email"
                :rules="emailRules"
                label="E-mail"
                required
                ></v-text-field>
                <v-select
                v-model="select"
                :items="items"
                :rules="[v => !!v || 'Item is required']"
                label="Item"
                required
                ></v-select>
                <v-checkbox
                v-model="checkbox"
                :rules="[v => !!v || 'You must agree to continue!']"
                label="Do you agree?"
                required
                ></v-checkbox>

                <!--v-btn
                :disabled="!valid"
                @click="submit"
                >
                submit
                </v-btn>
                <v-btn @click="clear">clear</v-btn>
                -->
            </v-form>
                    
          
          
          </v-card>
  
          <v-btn
            color="primary"
            @click="e1 = 2"
          >
            Continue
          </v-btn>
  
          <v-btn flat>Cancel</v-btn>
        </v-stepper-content>
  
        <v-divider></v-divider>
  
        <v-stepper-step :complete="e1 > 2" step="2">Step 2</v-stepper-step>
        <v-stepper-content step="2">
          <v-card
            class="mb-5"
            color="grey lighten-1"
            height="200px"
          ></v-card>
  
          <v-btn
            color="primary"
            @click="e1 = 3"
          >
            Continue
          </v-btn>
  
          <v-btn flat>Cancel</v-btn>
        </v-stepper-content>
        <v-divider></v-divider>
  
        <v-stepper-step step="3">Step 3</v-stepper-step>

        <v-stepper-content step="3">
          <v-card
            class="mb-5"
            color="grey lighten-1"
            height="200px"
          ></v-card>
  
          <v-btn
            color="primary"
            @click="e1 = 1"
          >
            Continue
          </v-btn>
  
          <v-btn flat>Cancel</v-btn>
        </v-stepper-content>
  
      <v-stepper-items>

  
  
  
      </v-stepper-items>
    </v-stepper>







</template>


<script>
  //import axios from 'axios'

  export default {
    data: () => ({
      e1: 0,
      valid: true,
      name: '',
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
        'Item 1',
        'Item 2',
        'Item 3',
        'Item 4'
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