<template>
  <div class="Login">
    <h1>you should login here</h1>
    <h1>{{ count }}</h1>
  </div>
</template>

<script>
import { useStore } from 'vuex'

export default {
  setup() {
    const store = useStore()
    store.commit('increment', 10)
    const count = store.getters.tenTimes;
    return {
      count
    }
  }
}
</script>