import Vuex from "vuex";
import Firebase from "firebase/app";
import campaigns from "./campaigns";

require("firebase/firestore");

const firebaseApp = Firebase.initializeApp({
  apiKey: process.env.FIREBASE_API_KEY,
  authDomain: process.env.FIREBASE_AUTH_DOMAIN,
  projectId: process.env.FIREBASE_PROJECT_ID
});

const firestore = firebaseApp.firestore();
firestore.settings({ timestampsInSnapshots: true });

export default () =>
  new Vuex.Store({
    state: {
      db: firestore,
      user: {
        picture: "https://randomuser.me/api/portraits/men/85.jpg",
        name: "John Leider"
      }
    },
    modules: {
      campaigns
    }
  });
