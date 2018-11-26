<template>
<v-card>
        <v-toolbar dark>
          
          <v-toolbar-side-icon icon nuxt-link to="/myreports"> <!--** AE: need a back action --> 
            <v-icon 
                dark
              >
               clear
            </v-icon>

          </v-toolbar-side-icon>
          <v-toolbar-title>
          
          <v-card-title class="title font-weight-regular">Report History</v-card-title>

          </v-toolbar-title>
          <v-spacer></v-spacer>

      </v-toolbar>
        <v-container
          id="scroll-target"
          style="max-height:700px"
          class="scroll-y"
          fluid

        >
                <v-card
            class="mb-5"
            color="grey lighten-1"
            height="200px"
          >
          <p>Listing Widget</p>
          </v-card>
  <v-timeline align-top>
    <v-timeline-item
      v-for="(item, i) in items"
      :color="item.color"
      :icon="item.icon"
      :key="i"
      fill-dot
    >
      <v-card
        :color="item.color"
        dark
      >
        <v-card-title class="title">{{item.title}}</v-card-title>
        <v-card-text class="white text--primary">
            <div class="text-uppercase font-weight-light">12th February 2015</div>
          <p>
              {{item.text}}
          </p>
        </v-card-text>
      </v-card>
    </v-timeline-item>
  </v-timeline>

        <v-card
            class="mb-5"
            color="grey lighten-1"
            height="200px"
          >
          <p>Actions (if any)</p>
          </v-card>

        </v-container>
        </v-card>
</template>


<script>
  export default {
    data: () => ({
      items: [
        {
            title: "Reported",
            text: "Integrity issue on Smart Contract X",
          color: 'red lighten-2',
          icon: 'bug_report'
        },
        {
            title: "Rejected",
            text: "Not an issue",
          color: 'purple darken-1',
          icon: 'delete_forever'
        },
        {
             title: "Challenged",
            text: "Sent to community",
          color: 'green darken-1',
          icon: 'group_work'
        },
        {
            title: "Awaiting Votes",
            text: "Met quarum",
          color: 'indigo',
          icon: 'gavel'
        },
        {
            title: "Resolution",
            text: "Your favour",
          color: 'indigo',
          icon: 'thumb_up'
        },
                {
            title: "Bounty Awarded!",
            text: "Your favour",
          color: 'indigo',
          icon: 'money'
        }
      ]
    })
  }
</script>