<template>
  <v-card>
    <v-toolbar dark>
          
          <v-toolbar-side-icon > <!--** AE: need a back action --> 
            <v-icon 
                dark
              >
               arrow_back
            </v-icon>

          </v-toolbar-side-icon>
          <v-img 
            :src="require('~/assets/img/crowdos_logo.png')" 
            name="welcomelogo"
            height="25px" 
            width="100"
            contain
          ></v-img>
           <v-spacer></v-spacer>
          <v-toolbar-title>
           
          
          <v-card-title class="title font-weight-regular">Reports</v-card-title>

          </v-toolbar-title>
          <v-spacer></v-spacer>

      </v-toolbar>
    <v-container
        id="scroll-target"
        style="max-height:700px"
        class="scroll-y"
        fluid

    >


    <v-layout row>
        <v-flex xs12 sm6 offset-sm3>

            <v-list two-line>
            <template v-for="(item, index) in items">
                <v-list-tile
                :key="item.title"
                avatar
                ripple
                @click="toggle(index)"
                >
                <v-list-tile-content>
                     
                    <v-list-tile-title style = "height: 25px;">

                        <v-chip small label :color=item.type.color text-color="white">{{item.type.name}}</v-chip>
                        {{ item.title }}
                        <v-chip small label outline>{{item.score}}</v-chip>
                         
                    </v-list-tile-title>
                    <v-list-tile-sub-title class="text--primary">
                        {{ item.headline }}
                    </v-list-tile-sub-title>
                    <v-list-tile-sub-title>{{ item.subtitle }}</v-list-tile-sub-title>
                </v-list-tile-content>

                <v-list-tile-action>
                    <v-list-tile-action-text>{{ item.action }}</v-list-tile-action-text>
                    <v-icon
                    v-if="selected.indexOf(index) < 0"
                    color="grey lighten-1"
                    >
                    star_border
                    </v-icon>

                    <v-icon
                    v-else
                    color="yellow darken-2"
                    >
                    star
                    </v-icon>
                    
                </v-list-tile-action>
                <v-list-tile-action>
                    <v-icon                    
                    >
                    delete_outline
                    </v-icon>
                    
                </v-list-tile-action>
                             

                </v-list-tile>
                <v-divider
                v-if="index + 1 < items.length"
                :key="index"
                ></v-divider>
            </template>
            </v-list>
        
        </v-flex>
    </v-layout>

    </v-container>
  </v-card>
</template>

<script>

var HACKTYPES = {
  PEN : {value: 0, name: "Pen", color: "red"}, 
  INT: {value: 1, name: "Int", color: "orange"}, 
  SEC : {value: 2, name: "Sec", color: "blue"},
  IMP : {value: 3, name: "Imp", color: "green"},
};

    const HackTypes = Object.freeze({
        PEN: Symbol("red"),
        INT: Symbol("orange"),
        SEC: Symbol("blue"),
        IMP: Symbol("green")
    });

  export default {
    data () {
      return {
        selected: [2,6],
        items: [
          {
            action: '15 min',
            headline: 'Brunch this weekend?',
            title: 'Ali Connors',
            subtitle: "I'll be in your neighborhood doing errands this weekend. Do you want to hang out?",
            type: HACKTYPES.PEN,
            score: "5/10"
          },
          {
            action: '2 hr',
            headline: 'Summer BBQ',
            title: 'me, Scrott, Jennifer',
            subtitle: "Wish I could come, but I'm out of town this weekend.",
            type: HACKTYPES.INT,
            score: "7/8"
          },
          {
            action: '6 hr',
            headline: 'Oui oui',
            title: 'Sandra Adams',
            subtitle: 'Do you have Paris recommendations? Have you ever been?',
            type: HACKTYPES.PEN,
            score: "4/29"
          },
          {
            action: '12 hr',
            headline: 'Birthday gift',
            title: 'Trevor Hansen',
            subtitle: 'Have any ideas about what we should get Heidi for her birthday?',
            type: HACKTYPES.IMP,
            score: "9/12"
          },
          {
            action: '18hr',
            headline: 'Recipe to try',
            title: 'Britta Holt',
            subtitle: 'We should eat this: Grate, Squash, Corn, and tomatillo Tacos.',
            type: HACKTYPES.SEC,
            score: "18/23"
          }
        ]
      }
    },

    methods: {
      toggle (index) {
        const i = this.selected.indexOf(index)

        if (i > -1) {
          this.selected.splice(i, 1)
        } else {
          this.selected.push(index)
        }
      }
    }
  }
</script>