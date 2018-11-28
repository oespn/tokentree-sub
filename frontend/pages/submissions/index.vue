<template>
  <v-card>
    <v-layout column>
      <v-tabs>
        <v-tab>Pending</v-tab>
        <v-tab>Challenged</v-tab>
        <v-tab>Bounties Awarded</v-tab>
        <v-tab>Dismissed</v-tab>
      </v-tabs>
      <v-divider></v-divider>

      <v-list two-line>
        <template v-for="(item, index) in items">
          <v-list-tile
            :key="item.title"
            avatar
            ripple
            nuxt-link
            :to="'reports/review/'"
            @click="toggle(index)"
            style="height: 86px;"
          >
            <v-list-tile-avatar>
              <img :src="item.avatar">
            </v-list-tile-avatar>
            <v-list-tile-content>
              <v-list-tile-title style="height: 34px;">
                {{ item.title }}
                <v-chip small label outline>{{item.score}}</v-chip>
              </v-list-tile-title>
              <v-list-tile-sub-title class="text--primary" style="height: 34px;">
                <v-chip small label :color="item.type.color" text-color="white">{{item.type.name}}</v-chip>
                {{ item.headline }}
              </v-list-tile-sub-title>
              <v-list-tile-sub-title>{{ item.subtitle }}</v-list-tile-sub-title>
            </v-list-tile-content>

            <v-list-tile-action>
              <v-list-tile-action-text>{{ item.action }}</v-list-tile-action-text>
              <v-icon v-if="selected.indexOf(index) < 0" color="grey lighten-1">label_outlined</v-icon>

              <v-icon v-else color="yellow darken-2">label</v-icon>
            </v-list-tile-action>
          </v-list-tile>
          <v-divider v-if="index + 1 < items.length" :key="index"></v-divider>
        </template>
      </v-list>
    </v-layout>
  </v-card>
</template>

<script>
var HACKTYPES = {
  PEN: { value: 0, name: "Pen", color: "red" },
  INT: { value: 1, name: "Int", color: "orange" },
  SEC: { value: 2, name: "Sec", color: "blue" },
  IMP: { value: 3, name: "Imp", color: "green" }
};

const HackTypes = Object.freeze({
  PEN: Symbol("red"),
  INT: Symbol("orange"),
  SEC: Symbol("blue"),
  IMP: Symbol("green")
});

export default {
  data() {
    return {
      selected: [2, 6],
      items: [
        {
          id: "aeu3ohi4u2g5iug212345",
          avatar: "https://cdn.vuetifyjs.com/images/lists/1.jpg",
          action: "15 min",
          headline: "Brunch this weekend?",
          title: "Ali Connors",
          subtitle:
            "I'll be in your neighborhood doing errands this weekend. Do you want to hang out?",
          type: HACKTYPES.PEN,
          score: "5/10"
        },
        {
          id: "4342abc23",
          avatar: "https://cdn.vuetifyjs.com/images/lists/2.jpg",
          action: "2 hr",
          headline: "Summer BBQ",
          title: "me, Scrott, Jennifer",
          subtitle: "Wish I could come, but I'm out of town this weekend.",
          type: HACKTYPES.INT,
          score: "7/8"
        },
        {
          id: "4342abc23",

          avatar: "https://cdn.vuetifyjs.com/images/lists/3.jpg",
          action: "6 hr",
          headline: "Oui oui",
          title: "Sandra Adams",
          subtitle: "Do you have Paris recommendations? Have you ever been?",
          type: HACKTYPES.PEN,
          score: "4/29"
        },
        {
          id: "4342abc23",

          avatar: "https://cdn.vuetifyjs.com/images/lists/4.jpg",
          action: "12 hr",
          headline: "Birthday gift",
          title: "Trevor Hansen",
          subtitle:
            "Have any ideas about what we should get Heidi for her birthday?",
          type: HACKTYPES.IMP,
          score: "9/12"
        }
      ],
      items_challenged: [
        {
          id: "aeu3ohi4u2g5iug212345",

          avatar: "https://randomuser.me/api/portraits/men/85.jpg",
          action: "18hr",
          headline: "Recipe to try",
          title: "John Holt",
          subtitle:
            "We should eat this: Grate, Squash, Corn, and tomatillo Tacos.",
          type: HACKTYPES.SEC,
          score: "18/23"
        }
      ],
      items_closed: [
        {
          id: "4342abc23",

          avatar: "https://cdn.vuetifyjs.com/images/lists/6.jpg",
          action: "6 hr",
          headline: "Oui oui",
          title: "Sandra Adams",
          subtitle: "Do you have Paris recommendations? Have you ever been?",
          type: HACKTYPES.PEN,
          score: "4/29"
        },
        {
          id: "4342abc23",
          action: "12 hr",
          headline: "Birthday gift",
          title: "Trevor Hansen",
          subtitle:
            "Have any ideas about what we should get Heidi for her birthday?",
          type: HACKTYPES.IMP,
          score: "9/12"
        },
        {
          id: "4342abc23",
          action: "18hr",
          headline: "Recipe to try",
          title: "Britta Holt",
          subtitle:
            "We should eat this: Grate, Squash, Corn, and tomatillo Tacos.",
          type: HACKTYPES.SEC,
          score: "18/23"
        }
      ]
    };
  },

  methods: {
    toggle(index) {
      const i = this.selected.indexOf(index);

      if (i > -1) {
        this.selected.splice(i, 1);
      } else {
        this.selected.push(index);
      }
    }
  }
};
</script>