<template>
  <div class="container">
    <div class="pixi-container">
      <div class="pixi" ref="pixi"></div>
    </div>
  </div>
</template>

<script>
import { data as JsonData } from '@/assets/data/WarehouseLocation0.json';
import forbid from '@/assets/img/forbid.png';
import location from '@/assets/img/location.png';
import channel from '@/assets/img/channel.jpg';

import { Application, Assets, Container, Graphics, Sprite, Texture } from 'pixi.js';

// 加载图片
await Assets.load(forbid);
await Assets.load(location);
await Assets.load(channel);
const forbidTexture = new Texture.from(forbid);
const locationTexture = new Texture.from(location);
const channelTexture = new Texture.from(channel);

export default {
  name: 'App',
  data() {
    return {
      // 横坐标格子数量
      PTw: 30,
      PTh: 30,
      PTx: 30,
      PTy: 20,
      PTgap: 3,
      PTNums: JsonData.length,
      selectedPT: null
    }
  },
  mounted() {
    this.initPixi();
  },
  methods: {
    async initPixi() {
      // 1.生成底图
      // 计算 rowNo、colNo 最大值
      const maxRow = Math.max(...JsonData.map(item => item.rowNo));
      const maxCol = Math.max(...JsonData.map(item => item.colNo));

      this.PTx = maxCol;
      this.PTy = maxRow;

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

      // 2.对canvas的移动进行监听操作
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


      // 3.生成灰色网格图
      const container = new Container();
      container.x = app.screen.width / 2;
      container.y = app.screen.height / 2;

      // 容器加入舞台
      app.stage.addChild(container);
      // 存储所有矩形的数组
      const PTs = [];
      let PTStartX = 0, PTStartY = 0;
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

        PT.on('pointerdown', (event) => {
          PTStartX = event.clientX;
          PTStartY = event.clientY;
        });

        // 添加点击事件处理程序
        PT.on('pointerup', (event) => {
          // 判断是否是移动
          const endX = event.clientX;
          const endY = event.clientY;
          const distance = Math.sqrt((endX - PTStartX) ** 2 + (endY - PTStartY) ** 2);
          if (distance > 3) return;

          // 开始对点击事件处理
          const clickPT = event.target;
          if (this.selectedPT && this.selectedPT.selected) {
            const { x, y } = this.selectedPT.positionData;
            this.selectedPT.clear();
            this.selectedPT.rect(x, y, this.PTw, this.PTh)
              .stroke({ width: 5, color: '0xFFFFFF', alpha: 1 })
              .fill(0xa0a8a8);
            this.selectedPT.selected = false;
          }

          // 更新矩形的边框颜色
          const { x, y } = clickPT.positionData;
          clickPT.selected = true;
          clickPT.clear();
          clickPT.rect(x, y, this.PTw, this.PTh)
            .stroke({ width: 5, color: '0xFFFFFF', alpha: 1 })
            .fill(0xa0a8a8);
          clickPT.stroke({ width: 2, color: '0xFF0000' })

          // 缓存选中的PT
          this.selectedPT = clickPT;
        });
      }

      // 4.初步根据状态生成不同的纹理贴图
      for (let i = 0; i < this.PTNums; i++) {
        let texture = Texture.EMPTY

        const data = JsonData[i];
        if (data.deepNo == 0) {
          texture = channelTexture
        }

        if (data.status == 1) {
          texture = forbidTexture
        }

        const sprite = new Sprite(texture);
        // 根据状态生成图片
        sprite.width = Math.min(this.PTw, this.PTh);
        sprite.height = Math.min(this.PTw, this.PTh);
        sprite.x = (data.colNo - 1) * (this.PTw + this.PTgap) + this.PTw / 2 - sprite.width / 2;
        sprite.y = (data.rowNo - 1) * (this.PTh + this.PTgap) + this.PTh / 2 - sprite.height / 2;

        sprite.pointerEvents = false;
        if (data.deepNo == 0) {
          sprite.pointerEvents = true;
        }

        container.addChild(sprite);
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
  width: 90vw;
  height: 90vh;
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
