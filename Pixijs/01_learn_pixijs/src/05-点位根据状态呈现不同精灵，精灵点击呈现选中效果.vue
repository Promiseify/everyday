<template>
  <div id="app">
    <div class="pixi" ref="pixi"></div>
  </div>
</template>

<script>
import forbid from '@/assets/img/forbid.png';
import location from '@/assets/img/location.png';
import fav3 from '@/assets/img/fav3.jpg';
import { Application, Assets, Container, Graphics, Sprite, Texture } from 'pixi.js';

// 加载图片
await Assets.load(forbid);
await Assets.load(location);
// await Assets.load(fav3);
const forbidTexture = new Texture.from(forbid);
const locationTexture = new Texture.from(location);
// const textureFav3 = new Texture.from(fav3);

export default {
  name: 'App',
  data() {
    return {
      // 横坐标格子数量
      PTw: 30,
      PTh: 30,
      PTx: 20,
      PTy: 10,
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
      // 存储所有矩形的数组
      const PTs = [];
      // 构造网格区域
      for (let i = 0; i < this.PTx * this.PTy; i++) {
        const x = (i % this.PTx) * (this.PTw + this.PTgap);
        const y = Math.floor(i / this.PTx) * (this.PTh + this.PTgap);
        const PT = new Graphics()
          .rect(x, y, this.PTw, this.PTh)
          .stroke({ width: 5, color: '0xFFFFFF', alpha: 1 })
          .fill(0xa0a8a8);

        PT.interactive = true;
        PT.positionData = { x, y }
        container.addChild(PT);
        PTs.push(PT);
      }

      for (let i = 0; i < this.PTx * this.PTy; i++) {
        let texture = forbidTexture

        if (i % this.PTx == 0) {
          texture = forbidTexture
        } else if (i % this.PTx == 1) {
          texture = locationTexture
        } else {
          texture = Texture.EMPTY;
        }

        // 根据状态生成图片
        const forbidSprite = new Sprite(texture);
        forbidSprite.width = Math.min(this.PTw, this.PTh) - this.PTgap;
        forbidSprite.height = Math.min(this.PTw, this.PTh) - this.PTgap;
        forbidSprite.x = (i % this.PTx) * (this.PTw + this.PTgap) + this.PTw / 2 - forbidSprite.width / 2;
        forbidSprite.y = Math.floor(i / this.PTx) * (this.PTh + this.PTgap) + this.PTh / 2 - forbidSprite.height / 2;

        forbidSprite.interactive = true;
        forbidSprite.buttonMode = true;

        // 添加点击事件处理程序
        forbidSprite.on('click', () => {
          // 切换选中状态
          forbidSprite.selected = !forbidSprite.selected;

          // 更新举行的边框颜色
          const PT = PTs[i];
          const { x, y } = PT.positionData;

          PT.clear();
          if (forbidSprite.selected) {
            PT.rect(x, y, this.PTw, this.PTh)
              .stroke({ width: 5, color: '0xFFFFFF', alpha: 1 })
              .fill(0xa0a8a8);

            PT.stroke({ width: 2, color: '0xFF0000' })
          } else {
            PT.rect(x, y, this.PTw, this.PTh)
              .stroke({ width: 5, color: '0xFFFFFF', alpha: 1 })
              .fill(0xa0a8a8);
          }
        });
        container.addChild(forbidSprite);
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
