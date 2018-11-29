const LOGIN_PATH = "/login";

export default function({ store, redirect, route }) {
  if (route.path === LOGIN_PATH) {
    return;
  }
  if (!store.state.db.app.auth().currentUser) {
    return redirect(LOGIN_PATH, { redirect: route.path });
  }
}
