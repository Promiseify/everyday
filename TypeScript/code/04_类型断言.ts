// 类型断言
const imgEl = document.querySelector(".img") as HTMLImageElement;
imgEl.src = "http://xx";
imgEl.alt = "测试";

// 非空类型断言
const info = {
  friend: {
    name: "ao"
  }
}

info.friend!.name = "why";
console.log(info);

export {}