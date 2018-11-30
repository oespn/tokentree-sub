import Vuex from "vuex";
import Firebase from "firebase/app";
import session from "./session";
import campaigns from "./campaigns";
import exchange from "./exchange";

import "firebase/auth";
import "firebase/firestore";

const firebaseApp = Firebase.initializeApp({
  apiKey: process.env.FIREBASE_API_KEY,
  authDomain: process.env.FIREBASE_AUTH_DOMAIN,
  databaseURL: process.env.FIREBASE_DATABASE_URL,
  projectId: process.env.FIREBASE_PROJECT_ID,
  storageBucket: process.env.FIREBASE_STORAGE_BUCKET,
  messagingSenderId: process.env.FIREBASE_MESSAGING_SENDER_ID
});

const firestore = firebaseApp.firestore();
firestore.settings({ timestampsInSnapshots: true });

const initStore = async store => {
  store.dispatch("exchange/fetchAll")
  setInterval(() => store.dispatch("exchange/fetchAll"), 30 * 60 * 1000) // every 30mn
};

export default () => {
  const store = new Vuex.Store({
    state: {
      db: firestore
    },
    modules: {
      session,
      campaigns,
      exchange
    }
  });
  firebaseApp
    .auth()
    .onAuthStateChanged(user =>
      user
        ? store.dispatch("session/autoSignIn", user.toJSON())
        : store.dispatch("session/logout")
    );
  initStore(store);
  return store;
};
