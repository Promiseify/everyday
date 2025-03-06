<template>
  <div class="container">
    <div class="pixi-container">
      <div class="pixi" ref="pixi"></div>
    </div>
  </div>
</template>

<script>
import forbid from '@/assets/img/forbid.png';
import location from '@/assets/img/location.png';
import { Application, Assets, Container, Graphics, Sprite, Texture } from 'pixi.js';

// 加载图片
await Assets.load(forbid);
await Assets.load(location);
const forbidTexture = new Texture.from(forbid);
const locationTexture = new Texture.from(location);

export default {
  name: 'App',
  data() {
    return {
      // 横坐标格子数量
      PTw: 30,
      PTh: 30,
      PTx: 30,
      PTy: 20,
      PTgap: 3
    }
  },
  mounted() {
    this.initPixi();
  },
  methods: {
    async initPixi() {
      const canvasWidth = this.PTx * (this.PTw + this.PTgap) + 30;
      const canvasHeight = this.PTy * (this.PTh + this.PTgap) + 30;

      const app = new Application();

      await app.init({
        width: canvasWidth,
        height: canvasHeight,
        backgroundColor: 0xbdbebd,
        resolution: 1,
        antialias: true
      });

      this.$refs.pixi.appendChild(app.canvas);

      let isDragging = false;
      let startX, startY;

      const onMouseDown = (event) => {
        isDragging = true;
        startX = event.clientX;
        startY = event.clientY;
        this.$refs.pixi.style.cursor = 'grabbing';
      };

      const onMouseMove = (event) => {
        if (!isDragging) return;
        const dx = event.clientX - startX;
        const dy = event.clientY - startY;

        // 获取当前canvas的位置
        const currentLeft = parseInt(app.canvas.style.left || 0);
        const currentTop = parseInt(app.canvas.style.top || 0);

        // 计算新的位置
        let newLeft = currentLeft + dx;
        let newTop = currentTop + dy;

        // 获取pixi容器的尺寸
        const pixiRect = this.$refs.pixi.getBoundingClientRect();
        const canvasRect = app.canvas.getBoundingClientRect();

        // 检查边界
        if (newLeft > 0) newLeft = 0;
        if (newTop > 0) newTop = 0;
        if (newLeft < pixiRect.width - canvasRect.width) newLeft = pixiRect.width - canvasRect.width;
        if (newTop < pixiRect.height - canvasRect.height) newTop = pixiRect.height - canvasRect.height;

        // 更新canvas的位置
        app.canvas.style.left = `${newLeft}px`;
        app.canvas.style.top = `${newTop}px`;

        startX = event.clientX;
        startY = event.clientY;
      };

      const onMouseUp = () => {
        isDragging = false;
        this.$refs.pixi.style.cursor = 'default';
      };

      this.$refs.pixi.addEventListener('mousedown', onMouseDown);
      window.addEventListener('mousemove', onMouseMove);
      window.addEventListener('mouseup', onMouseUp);


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
        PT.selected = false;
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
        forbidSprite.on('click', (event) => {
          const endX = event.clientX;
          const endY = event.clientY;
          const distance = Math.sqrt((endX - startX) ** 2 + (endY - startY) ** 2);
          if (distance > 3) return;
          PTs.forEach((PT) => {
            if (PT.selected) {
              const { x, y } = PT.positionData;
              PT.clear();
              PT.rect(x, y, this.PTw, this.PTh)
                .stroke({ width: 5, color: '0xFFFFFF', alpha: 1 })
                .fill(0xa0a8a8);
            }
          })

          // 切换选中状态
          forbidSprite.selected = !forbidSprite.selected;
          // 更新矩形的边框颜色
          const PT = PTs[i];
          const { x, y } = PT.positionData;
          PT.selected = forbidSprite.selected;
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
.container {
  display: flex;
  justify-content: center;
  align-items: center;
  height: 100vh;
  background-color: #FFFFFF;
}

.pixi-container {
  width: 60vw;
  height: 60vh;
}

.pixi {
  position: relative;
  width: 100%;
  height: 100%;
  overflow: hidden;
  /* 鼠标样式 */
  /* cursor: grab; */
}

canvas {
  position: absolute;
  top: 0;
  left: 0;
}
</style>
