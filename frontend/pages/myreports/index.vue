<template>
  <v-card>
    <v-toolbar dark>
          
          <v-toolbar-side-icon icon nuxt-link to="/"> <!--** AE: need a back action --> 
            <v-icon 
                dark
              >
               arrow_back
            </v-icon>

          </v-toolbar-side-icon>
          <v-toolbar-title>
           
          
          <v-card-title class="title font-weight-regular">My Reports</v-card-title>

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
            <v-subheader>
                Pending
            </v-subheader>
            <v-list two-line>
            <template v-for="(item, index) in items_pending">
                <v-list-tile
                :key="item.title"
                avatar
                ripple
                @click="toggle(index)"
                nuxt-link to="/reports/status"
                style = "height: 80px;"
                >
                <v-list-tile-content >
                     
                    <v-list-tile-title style = "height: 28px;">

                        <v-chip small label :color=item.type.color text-color="white">{{item.type.name}}</v-chip>
                        {{ item.company }}
                      
                         
                         <v-chip small color="yellow darken-2" outline>{{item.bounty}} EOS</v-chip>
                         <v-chip small label>{{item.score}}</v-chip>
                    </v-list-tile-title>
                    <v-list-tile-sub-title class="text--primary">
                        {{ item.title }}
                    </v-list-tile-sub-title>
                    <v-list-tile-sub-title>{{ item.subtitle }}</v-list-tile-sub-title>
                </v-list-tile-content>
                <v-list-tile-action>
                    <v-list-tile-action-text>{{ item.action }}</v-list-tile-action-text>
                </v-list-tile-action>
                
            
                             

                </v-list-tile>
                <v-divider
                v-if="index + 1 < items_pending.length"
                :key="index"
                ></v-divider>
            </template>
            </v-list>

            <v-subheader>
                Rejected &nbsp;
                <small class="font-weight-light">&nbsp; You can challenge rejections.  No reports have been rejected</small>
            </v-subheader>

            <v-subheader>
                Won
            </v-subheader>
            <v-list two-line>
            <template v-for="(item, index) in items_won">
                <v-list-tile
                :key="item.title"
                avatar
                ripple
                @click="toggle(index)"
                nuxt-link to="/reports/status"
                style = "height: 80px;"
                >
                <v-list-tile-content >
                     
                    <v-list-tile-title style = "height: 28px;">

                        <v-chip small label :color=item.type.color text-color="white">{{item.type.name}}</v-chip>
                        {{ item.company }}
                      
                         
                         <v-chip small color="yellow darken-1" >{{item.bounty}} EOS</v-chip>
                         <v-chip small color="yellow lighten-1" >{{item.jackpot}} EOS
                             <v-icon right>flare</v-icon>
                         </v-chip>
                         
                    </v-list-tile-title>
                    <v-list-tile-sub-title class="text--primary">
                        {{ item.title }}
                    </v-list-tile-sub-title>
                    <v-list-tile-sub-title>{{ item.subtitle }}</v-list-tile-sub-title>
                </v-list-tile-content>
                <v-list-tile-action>
                    <v-list-tile-action-text>{{ item.action }}</v-list-tile-action-text>
                </v-list-tile-action>
                
            
                             

                </v-list-tile>
                <v-divider
                v-if="index + 1 < items_won.length"
                :key="index"
                ></v-divider>
            </template>
            </v-list>


 <v-expansion-panel popout>
     <v-expansion-panel-content>
 
          <div slot="header">
            <v-list-tile-title>Closed</v-list-tile-title>
          </div>

            <v-list two-line>
            <template v-for="(item, index) in items_closed">
                <v-list-tile
                :key="item.title"
                avatar
                ripple
                nuxt-link to="/reports/status"
                @click="toggle(index)"
                style = "height: 80px;"
                >
                <v-list-tile-content >
                     
                    <v-list-tile-title style = "height: 28px;">

                        <v-chip small label :color=item.type.color text-color="white">{{item.type.name}}</v-chip>
                        {{ item.company }}
                      
                         
                         <v-chip small color="grey darken-2" outline>{{item.bounty}} EOS</v-chip>
                         
                    </v-list-tile-title>
                    <v-list-tile-sub-title class="text--primary">
                        {{ item.title }}
                    </v-list-tile-sub-title>
                    <v-list-tile-sub-title>{{ item.subtitle }}</v-list-tile-sub-title>
                </v-list-tile-content>
                <v-list-tile-action>
                    <v-list-tile-action-text>{{ item.action }}</v-list-tile-action-text>
                </v-list-tile-action>
                             

                </v-list-tile>
                <v-divider
                v-if="index + 1 < items_closed.length"
                :key="index"
                ></v-divider>
            </template>
            </v-list>
    </v-expansion-panel-content>
</v-expansion-panel>
 
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
        //status: [2,6],
        items_pending: [
          {
            action: '15 min',
            company: 'Atlassian',
            title: 'Jira API Release 2.9',
            subtitle: "I'll be in your neighborhood doing errands this weekend. Do you want to hang out?",
            type: HACKTYPES.PEN,
            score: "5/1000",
            bounty: "100"
          },
          {
            action: '2 hr',
            company: 'EOS.IO',
            title: 'Smart Contract',
            subtitle: "Wish I could come, but I'm out of town this weekend.",
            type: HACKTYPES.INT,
            score: "7/800",
            bounty: "500"
          }],
        items_won: [  
          
          {
            action: '6 hr',
            company: 'AirBnB',
            title: 'Developer API 2.6',
            subtitle: 'Do you have Paris recommendations? Have you ever been?',
            type: HACKTYPES.PEN,
            score: "4/290",
            bounty: "250",
            jackpot: "122"
          }],
        items_closed: [  
          {
            action: '12 hr',
            company: 'Uber',
            title: 'Developer Platform API',
            subtitle: 'Have any ideas about what we should get Heidi for her birthday?',
            type: HACKTYPES.IMP,
            score: "9/120",
            bounty: "600"
          },
          {
            action: '18hr',
            company: 'Booking.com',
            title: 'Payments API',
            subtitle: 'We should eat this: Grate, Squash, Corn, and tomatillo Tacos.',
            type: HACKTYPES.SEC,
            score: "18/250",
            bounty: "750"
          },
          {
            action: 'Friday',
            company: 'EOS.IO',
            title: 'Smart Contract',
            subtitle: "Wish I could come, but I'm out of town this weekend.",
            type: HACKTYPES.INT,
            score: "7/800",
            bounty: "500"
          }
        ]
      }
    },

    methods: {
      
      
    }
  }
</script>

<style>

.v-expansion-panel__header{
    padding-left:4px;
}
</style>