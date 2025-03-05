<template>
  <div id="app">
    <div class="pixi" ref="pixi"></div>
  </div>
</template>

<script>
import fav1 from '@/assets/img/fav1.jpg';
import fav2 from '@/assets/img/fav2.jpg';
import fav3 from '@/assets/img/fav3.jpg';
import { Application, Assets, Container, Graphics, Sprite, Texture } from 'pixi.js';

// 加载图片
// await Assets.load(fav1);
// await Assets.load(fav2);
// await Assets.load(fav3);
// const textureFav1 = new Texture.from(fav1);
// const textureFav2 = new Texture.from(fav2);
// const textureFav3 = new Texture.from(fav3);

export default {
  name: 'App',
  data() {
    return {
      // 横坐标格子数量
      PTw: 50,
      PTh: 50,
      PTx: 5,
      PTy: 5,
      PTgap: 3
    }
  },
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

      const container = new Container();
      container.x = app.screen.width / 2;
      container.y = app.screen.height / 2;

      // 容器加入舞台
      app.stage.addChild(container);

      // 构造网格区域
      for (let i = 0; i < this.PTx * this.PTy; i++) {
        const PT = new Graphics()
          .rect((i % this.PTx) * (this.PTw + this.PTgap), Math.floor(i / this.PTx) * (this.PTh + this.PTgap), this.PTw, this.PTh)
          .stroke({ width: 5, color: '0xFFFFFF', alpha: 1 })
          .fill(0xa0a8a8)
          .on('click', () => {
            PT.stroke({ width: 2, color: '0xFF0000' });
          });

        PT.interactive = true;
        container.addChild(PT);
      }

      container.pivot.set(container.width / 2, container.height / 2)
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
