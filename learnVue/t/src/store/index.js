import { createStore } from 'vuex'

export default createStore({
  state: {
    count: 233,
  },
  getters: {
    tenTimes: (state) => {
      return state.count * 10
    },
  },
  mutations: {
    increment (state, payload) {
      state.count += payload
    }
  },
  actions: {
  },
  modules: {
  }
})
