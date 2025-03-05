<template>
  <div id="app">
    <div class="pixi" ref="pixi"></div>
  </div>
</template>

<script>
import { Application, Graphics, Texture } from 'pixi.js';

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

      // 创建矩形
      const rectangle = new Graphics()
        .rect(0, 0, 200, 100)
        .fill({ texture: Texture.WHITE, width: 10, color: '0xFF0000' })
        .stroke({ width: 2, color: 'white' });

      rectangle.position.set(200, 100)
      // rectangle.x = 200;
      // rectangle.y = 100;
      // rectangle.rotation = 0.5;
      // rectangle.pivot.set(100, 50);

      app.stage.addChild(rectangle);

      // 创建一个圆形
      const circle = new Graphics()
        .circle(50, 50, 50)
        .fill(0x00ff00);

      app.stage.addChild(circle);

      // 绘制圆角矩形
      const roundedRectangle = new Graphics()
        .roundRect(0, 0, 200, 100, 20)
        .fill(0x0000ff);

      roundedRectangle.position.set(500, 100);
      app.stage.addChild(roundedRectangle);

      // 绘制圆角矩形
      const ellipse = new Graphics()
        .ellipse(0, 0, 100, 50)
        .fill(0x00ffff);

      ellipse.position.set(900, 150);
      app.stage.addChild(ellipse);

      // 绘制多边形
      const polygon = new Graphics()
        .poly([0, 0, 100, 0, 100, 100, 0, 100])
        .fill(0xfff000);
      polygon.position.set(1100, 100);
      app.stage.addChild(polygon);
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
