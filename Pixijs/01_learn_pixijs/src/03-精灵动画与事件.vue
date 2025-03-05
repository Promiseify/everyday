<template>
  <div id="app">
    <div class="pixi" ref="pixi"></div>
  </div>
</template>

<script>
import logo from '@/assets/logo.png';
import { Application, Assets, Graphics, Sprite, Texture } from 'pixi.js';
import { reactive } from 'vue';

export default {
  name: 'App',
  mounted() {
    this.initPixi();
  },
  methods: {
    async initPixi() {
      const app = new Application();

      await app.init({
        width: window.innerWidth,
        height: window.innerHeight,
        backgroundColor: 0x1099bb,
        resolution: window.devicePixelRatio || 1,
        antialias: true
      });

      this.$refs.pixi.appendChild(app.canvas);

      await Assets.load(logo)
      const texture = new Texture.from(logo);
      const sprite = new Sprite(texture);
      sprite.width = 50;
      sprite.height = 50;
      // sprite.scale.set(2, 2);
      // sprite.position.set(100, 100);

      sprite.anchor.set(0.5, 0.5);
      sprite.x = app.screen.width / 2;
      sprite.y = app.screen.height / 2;

      app.stage.addChild(sprite);
      app.ticker.add((delta) => {
        sprite.rotation += 0.01 * delta.speed;
      })

      // 给精灵添加交互事件
      sprite.interactive = true;
      sprite.on("click", () => {
        console.log("精灵得到了点击");
      })

      const rectangle = new Graphics()
        .rect(0, 0, 100, 100)
        .fill(0xff0000);

      app.stage.addChild(rectangle);
      rectangle.interactive = true;
      rectangle.on("click", () => {
        rectangle.clear().rect(0, 0, 100, 100).fill(0x00ff00);
        rectangle.texture = texture;
      })
    }
  }
}
</script>

<style>
canvas {
  position: fixed;
  left: 0;
  top: 0;
  width: 100vw;
  height: 100vh;
}
</style>
